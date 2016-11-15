/*
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm.h>
#include <gst/gst.h>
#include <algorithm>
#include <iostream>

namespace
{

static gchar* nmspace = 0;
static gchar* defsFile = 0;
static gchar* target = 0;

static std::string pluginName;
static std::string cTypeName;
static std::string cParentTypeName;
static std::string cppTypeName;
static std::string cppParentTypeName;
static std::string castMacro;
static std::string parentInclude;
static std::string parentNameSpace;

static GType type = 0;

// To add a base class that is already wrapped to the list of wrapped base
// classes, insert it alphabetically below.
static const char *const wrappedBaseClasses[] =
{
  "GstAudioFilter",
  "GstAudioSink",
  "GstAudioSrc",
  "GstAudioBaseSink",
  "GstAudioBaseSrc",
  "GstBaseSink",
  "GstBaseSrc",
  "GstBaseTransform",
  "GstBin",
  "GstCddaParanoiaSrc",
  "GstElement",
  "GstPipeline",
  "GstPushSrc",
  "GstVideoSink"
};

static bool gst_type_is_a_pointer(GType gtype)
{
  return (g_type_is_a(gtype, G_TYPE_OBJECT) ||
    g_type_is_a(gtype, G_TYPE_BOXED));
}

static std::string to_lowercase(const std::string& str)
{
  std::string result (str.size(), '\0');
  std::transform(str.begin(), str.end(), result.begin(), &Glib::Ascii::tolower);
  return result;
}

static std::string get_cast_macro(const std::string& typeName)
{
  std::string result;

  std::string::const_iterator iter = typeName.end();

  bool prev_is_upper = false;
  bool prev_is_lower = true;  // Going backwards so last char should be lower.
  int underscore_char_count = 0; // Used to count characters between underscores.

  for(--iter; iter != typeName.begin(); --iter, ++underscore_char_count)
  {
    if(Glib::Ascii::isupper(*iter))
    {
      result.insert(0, 1, *iter);
      if(prev_is_lower && underscore_char_count > 1)
      {
        result.insert(0, 1, '_');
        underscore_char_count = 0;
      }
      prev_is_upper = true;
      prev_is_lower = false;
    }
    else
    {
      if(prev_is_upper && underscore_char_count > 1)
      {
        result.insert(0, 1, '_');
        underscore_char_count = 0;
      }
      result.insert(0, 1, Glib::Ascii::toupper(*iter));
      prev_is_upper = false;
      prev_is_lower = true;
    }
  }

  // Insert first character (not included in the for loop).
  result.insert(0, 1, Glib::Ascii::toupper(*iter));

  return result;
}

static bool is_wrapped_base_class(const std::string& cTypeName)
{
  return std::binary_search(&wrappedBaseClasses[0],
                            &wrappedBaseClasses[G_N_ELEMENTS(wrappedBaseClasses)],
                            cTypeName);
}

static bool is_plugin(const std::string& cTypeName)
{
  const std::string element = to_lowercase(cTypeName.substr(3));

  if (GstElementFactory *const fact = gst_element_factory_find(element.c_str()))
  {
    g_object_unref(fact);
    return true;
  }
  return false;
}

static std::string get_property_wrap_statements(std::string& includeMacroCalls,
                                                std::string& enumWrapStatements,
                                                std::string& enumGTypeFunctionDefinitions)
{
  std::string wrapStatements;

  //Get the list of properties:
  GParamSpec** ppParamSpec = 0;
  guint iCount = 0;
  if(G_TYPE_IS_OBJECT(type))
  {
    GObjectClass* pGClass = G_OBJECT_CLASS(g_type_class_ref(type));
    ppParamSpec = g_object_class_list_properties (pGClass, &iCount);
    g_type_class_unref(pGClass);
  }
  else if(G_TYPE_IS_INTERFACE(type))
  {
    gpointer pGInterface = g_type_default_interface_ref(type);
    if(pGInterface) //We check because this fails for G_TYPE_VOLUME, for some reason.
    {
      ppParamSpec = g_object_interface_list_properties(pGInterface, &iCount);
      g_type_default_interface_unref(pGInterface);
    }
  }

  //This extra check avoids an occasional crash, for instance for GVolume
  if(!ppParamSpec)
    iCount = 0;

  for(guint i = 0; i < iCount; i++)
  {
    GParamSpec* pParamSpec = ppParamSpec[i];
    if(pParamSpec)
    {
      GType propertyGType = pParamSpec->value_type;
      GType ownerGType = pParamSpec->owner_type;

      if(ownerGType == type)
      {
        //Name and type:
        std::string propertyName = g_param_spec_get_name(pParamSpec);
        std::string propertyCType = g_type_name(propertyGType);
        if (gst_type_is_a_pointer(propertyGType))
          propertyCType += '*';

        if((G_TYPE_IS_ENUM(propertyGType) || G_TYPE_IS_FLAGS(propertyGType)))
        {
          std::string enumPrefix = propertyCType.substr(0, 3);
          std::string propertyCppType = propertyCType.substr(3);

          enumWrapStatements +=
            "_WRAP_PLUGIN_ENUM(" + enumPrefix + ',' + propertyCppType + ')';
          enumGTypeFunctionDefinitions +=
            "_PLUGIN_ENUM_GET_TYPE_FUNC(" + propertyCType + ')';
        }

        wrapStatements += "  _WRAP_PROPERTY(\"" + propertyName
          + "\", _TRANSLATE(" + propertyCType + ", `return'))\n";

        includeMacroCalls += "_TRANSLATION_INCLUDE(" + propertyCType + ")dnl\n";
      }
    }
  }

  g_free(ppParamSpec);
  return wrapStatements;
}

static std::string get_method_name(const std::string& signalName)
{
  std::string result = signalName;
  std::replace(result.begin(), result.end(), '-', '_');
  return result;
}

static std::string get_c_enum_definition_macro(GType enumGType,
                                               std::string& enumCType)
{
  std::string result;

  if(G_TYPE_IS_ENUM(enumGType))
  {
    GEnumClass* enumClass = G_ENUM_CLASS(g_type_class_ref(enumGType));
    if(enumClass)
    {
      result += "_C_ENUM_DEFINITION(" + enumCType + ',';
      for(guint i = 0; i < enumClass->n_values; i++)
      {
        std::stringstream stream;
        result += std::string(enumClass->values[i].value_nick) + ',';
        stream << enumClass->values[i].value;
        result += stream.str();
        if(i < enumClass->n_values - 1)
          result += ',';
      }
      result += ')';
    }
    g_type_class_unref(enumClass);
  }
  else
  {
    GFlagsClass* flagsClass = G_FLAGS_CLASS(g_type_class_ref(enumGType));
    if(flagsClass)
    {
      result += "_C_ENUM_DEFINITION(" + enumCType + ',';
      for(guint i = 0; i < flagsClass->n_values; i++)
      {
        std::stringstream stream;
        result += std::string(flagsClass->values[i].value_nick) + ',';
        stream << flagsClass->values[i].value;
        result += stream.str();
        if(i < flagsClass->n_values - 1)
          result += ',';
      }
      result += ')';
    }
    g_type_class_unref(flagsClass);
  }
  return result;
}

static std::string get_signal_wrap_statements(std::string& includeMacroCalls,
                                              std::string& cEnumDefinitions,
                                              std::string& enumWrapStatements,
                                              std::string& actionSignalsMethodDeclarations,
                                              std::string& enumGTypeFunctionDefinitions,
                                              std::string& actionSignalsMethodDefinitions)
{
  std::string wrapStatements;

  gpointer gclass_ref = 0;
  gpointer ginterface_ref = 0;

  if(G_TYPE_IS_OBJECT(type))
    gclass_ref = g_type_class_ref(type); //Ensures that class_init() is called.
  else if(G_TYPE_IS_INTERFACE(type))
    ginterface_ref = g_type_default_interface_ref(type); //install signals.

  //Get the list of signals:
  guint iCount = 0;
  guint* pIDs = g_signal_list_ids(type, &iCount);

  //Loop through the list of signals:
  if(pIDs)
  {
    for(guint i = 0; i < iCount; i++)
    {
      std::string convertMacros;
      std::string wrapStatement;
      std::string pluginEnumsTranslationMacros;

      std::string actionSignalMethodDeclaration;
      std::string actionSignalReturnDeclaration;
      std::string actionSignalReturnStatement;
      std::string actionSignalEmitSignalStatement;
      std::string actionSignalMethodDefinition;

      guint signal_id = pIDs[i];

      //Name:
      std::string signalName = g_signal_name(signal_id);
      std::string signalMethodName = get_method_name(signalName);

      //Other information about the signal:
      GSignalQuery signalQuery = { 0, 0, 0, GSignalFlags(0), 0, 0, 0, };
      g_signal_query(signal_id, &signalQuery);

      //Return type:
      GType returnGType = signalQuery.return_type & ~G_SIGNAL_TYPE_STATIC_SCOPE;

      std::string returnCType = g_type_name(returnGType);
      if (gst_type_is_a_pointer(returnGType))
        returnCType += '*';

      std::string returnCTypeTranslation = "_TRANSLATE("  + returnCType +
        ", `return')";

      // Start building action signal method declaration, definition and
      // emit statement if dealing with an action signal.
      if(signalQuery.signal_flags & G_SIGNAL_ACTION)
      {
        // Start the method declaration with a Doxygen comment about its
        // purpose.
        actionSignalMethodDeclaration = "  /** This is a convenience method "
          "for the action signal\n   * signal_" + signalMethodName + "().\n"
          "   */\n";

        // Append the actual method declaration.
        actionSignalMethodDeclaration += "  " + returnCTypeTranslation + ' ' +
          signalMethodName + '(';

        // Start the method definition.
        actionSignalMethodDefinition = returnCTypeTranslation + ' ' +
          cppTypeName + "::" + signalMethodName + '(';

        // Start the g_signal_emit() statement that will go in the method
        // body.
        actionSignalEmitSignalStatement =
          "  g_signal_emit_by_name(gobj(), \"" + signalName + "\"";

        // Generate return declaration and return statement if not a void
        // return.
        if (returnCType != "void")
        {
          actionSignalReturnDeclaration = "  " + returnCType + " result;\n";
          actionSignalReturnStatement = (std::string)"  return " +
            "_CONVERT(``" + returnCType + "'', _LQ()" +
            returnCTypeTranslation + "_RQ(), ``" + "result'');\n";
        }

        // Insert a newline above the action signal wrapping statements to
        // separte it since it will have a Doxygen comment.
        convertMacros += '\n';
      }

      // Check for an enum first and attempt to generate _WRAP_ENUM() and
      // _TRANSLATION() macros if it is not wrapped (see plugingen_base.m4
      // file for docs).
      if(G_TYPE_IS_ENUM(returnGType) || G_TYPE_IS_FLAGS(returnGType))
      {
        std::string enumPrefix = returnCType.substr(0, 3);
        std::string enumCppType = returnCType.substr(3);

        enumWrapStatements += "_WRAP_PLUGIN_ENUM(" + enumPrefix + ','
          + enumCppType + ')';

        enumGTypeFunctionDefinitions +=
          "_PLUGIN_ENUM_GET_TYPE_FUNC(" + returnCType + ')';

        cEnumDefinitions += get_c_enum_definition_macro(returnGType,
          returnCType);

        // Define a translation for the plug-in enum in case the enum is
        // used in an action signal method.  These translations will be
        // prepended to the action signals method definitions in the ccg file.
        pluginEnumsTranslationMacros += "_TRANSLATION(`" + returnCType +
          "', `" + enumPrefix + "::" + enumCppType + "', `" + enumPrefix +
          "::" + enumCppType + "')";
      }
      else if(gst_type_is_a_pointer(returnGType))
      {
        // Boxed type returns for signals need special conversions because
        // when unwrapping them, gobj_copy() should be used instead of just
        // gobj() to guard against losing the original with a temporary
        // wrapper.
        if(g_type_is_a(returnGType, G_TYPE_BOXED))
        {
          G_GNUC_BEGIN_IGNORE_DEPRECATIONS // temporary disable deprecations because of G_TYPE_VALUE_ARRAY
          // Unwrapping conversion:
          std::string access_operator = (returnGType != G_TYPE_ARRAY &&
                                         returnGType != G_TYPE_VALUE_ARRAY &&
                                         returnGType != GST_TYPE_TAG_LIST &&
                                         returnGType != GST_TYPE_STRUCTURE) ? "->" : ".";
          G_GNUC_END_IGNORE_DEPRECATIONS
          // For GValueArray and TagList, RefPtr is not generated, and we need to use '.' operator.
          convertMacros += "#m4 _CONVERSION(_LQ()" + returnCTypeTranslation +
            "_RQ(), ``" + returnCType + "'', ``($3)" + access_operator + "gobj_copy()'')\n";

          // Also include a wrapping conversion:

          if(returnGType == GST_TYPE_TAG_LIST)
          {
            // Dealing with a GstTagList* return which has a special
            // Glib::wrap() because of the conflict with the Glib::wrap() for
            // GstStructure* (GstTagList is infact a GstStructure).
            convertMacros += "#m4 _CONVERSION(``" + returnCType + "'', _LQ()" +
              returnCTypeTranslation + "_RQ(), ``Glib::wrap_taglist($3)'')\n";
          }
          else
          {
            // Dealing with a regular boxed type return.
            convertMacros += "#m4 _CONVERSION(``" + returnCType + "'', "
              "_LQ()" + returnCTypeTranslation + "_RQ(), ``Glib::wrap($3)'')\n";
          }
        }
        else
        {
          // Dealing with a RefPtr<> return so include a wrapping conversion
          // just so these conversions can be automatic for plug-ins and not
          // needed in the global convert file.  (An unwrapping conversion will
          // already probably be included in the global convert file).
          convertMacros += "#m4 _CONVERSION(``" + returnCType +
            "'', _LQ()" + returnCTypeTranslation + "_RQ(), " +
            "``Glib::wrap($3)'')\n";
        }
      }

      includeMacroCalls += "_TRANSLATION_INCLUDE(" + returnCType + ")dnl\n";

      // Start the wrap statement with a comment about action signals if
      // dealing with an action signal.
      if(signalQuery.signal_flags & G_SIGNAL_ACTION)
      {
        wrapStatement =
          "  /** This is an action signal which is designed to be used "
          "as a method.  To \n   * do that, use its convenience method, " +
          signalMethodName + "().\n   */\n";
      }

      wrapStatement += "  _WRAP_SIGNAL(" + returnCTypeTranslation + ' ' +
        signalMethodName + '(';

      //Loop through the list of parameters:
      const GType* pParameters = signalQuery.param_types;
      if(pParameters)
      {
        for(unsigned i = 0; i < signalQuery.n_params; i++)
        {
          GType paramGType = pParameters[i] & ~G_SIGNAL_TYPE_STATIC_SCOPE;

          //Parameter name:
          //TODO: How can we get the real parameter name?
          gchar* pchNum = g_strdup_printf("arg%u", i);
          std::string paramName = std::string(pchNum);
          g_free(pchNum);

          std::string paramCType = g_type_name(paramGType);
          if (gst_type_is_a_pointer(paramGType))
            paramCType += '*';

          std::string paramCTypeTranslation = "_TRANSLATE(" + paramCType +
            ",`param')";

          includeMacroCalls += "_TRANSLATION_INCLUDE(" + paramCType + ")dnl\n";

          // Continue building action signal method declaration, definition
          // and emit statement if it is an action signal.
          if(signalQuery.signal_flags & G_SIGNAL_ACTION)
          {
            actionSignalMethodDeclaration += paramCTypeTranslation + ' ' +
              paramName;

            actionSignalMethodDefinition += paramCTypeTranslation + ' ' +
              paramName;

            actionSignalEmitSignalStatement += ", _CONVERT(_LQ()" +
              paramCTypeTranslation + "_RQ(), ``" + paramCType + "'', ``" +
              paramName + "'')";
          }

          // Include wrapping conversions for signal parameters.  (Unwrapping
          // conversions will already probably be defined in the global
          // convert file).  Also try to wrap plug-in specific enums:

          if(G_TYPE_IS_ENUM(paramGType) || G_TYPE_IS_FLAGS(paramGType))
          {
            // Check for an enum first and attempt to generate _WRAP_ENUM() and
            // _TRANSLATION() macros and other necessary code if it is not
            // wrapped (see plugingen_base.m4 file for docs).
            std::string enumPrefix = paramCType.substr(0, 3);
            std::string enumCppType = paramCType.substr(3);

            enumWrapStatements += "_WRAP_PLUGIN_ENUM(" + enumPrefix + ',' +
              enumCppType + ')';

            enumGTypeFunctionDefinitions +=
              "_PLUGIN_ENUM_GET_TYPE_FUNC(" + paramCType + ')';

            cEnumDefinitions +=
              get_c_enum_definition_macro(paramGType, paramCType);

            // Define a translation for the plug-in enum in case the enum is
            // used in an action signal method.  These translations will be
            // prepended to the action signals method definitions in the
            // ccg file.
            pluginEnumsTranslationMacros += "_TRANSLATION(`" + paramCType +
              "', `" + enumPrefix + "::" + enumCppType + "', `" + enumPrefix +
              "::" + enumCppType + "')";
          }
          if(gst_type_is_a_pointer(paramGType))
          {
            if(paramGType == GST_TYPE_TAG_LIST)
            {
              // Dealing with a GstTagList* which has a special Glib::wrap()
              // because of the conflict with the Glib::wrap() for
              // GstStructure* (GstTagList is in fact a GstStructure).
              convertMacros += "#m4 _CONVERSION(``" + paramCType + "'', "
                "_LQ()" + paramCTypeTranslation + "_RQ(), "
                "``Glib::wrap_taglist($3, true)'')\n";
            }
            else
            {
              // Dealing with reference counted parameter or a boxed type.
              convertMacros += "#m4 _CONVERSION(``" + paramCType +
                "'', _LQ()" + paramCTypeTranslation + "_RQ(), " +
                "``Glib::wrap($3, true)'')\n";
            }
          }

          wrapStatement += paramCTypeTranslation + ' ' + paramName;

          if(i < signalQuery.n_params - 1)
          {
            wrapStatement += ", ";

            // Append commas to action signal method declaration and
            // definition if it is an action signal.  The emit statement
            // pre-pends the commas so adding commas to it is not done here.
            if(signalQuery.signal_flags & G_SIGNAL_ACTION)
            {
              actionSignalMethodDeclaration += ", ";
              actionSignalMethodDefinition += ", ";
            }
          }
        }
      }

      wrapStatement += "), \"" + signalName + "\", no_default_handler)\n";

      // Finish off the action signal declaration and definition if this
      // is an action signal.
      if(signalQuery.signal_flags & G_SIGNAL_ACTION)
      {
        // Close off the method declaration.
        actionSignalMethodDeclaration += ");\n\n";

        // Append a return location if the signal return is not void.
        if(returnCType != "void")
          actionSignalEmitSignalStatement += ", &result";

        // Close off the emit statement.
        actionSignalEmitSignalStatement += ", static_cast<void*>(0));\n";

        // Generate the method  definition.
        actionSignalMethodDefinition += ")\n"
          "{\n" +
          actionSignalReturnDeclaration +
          actionSignalEmitSignalStatement +
          actionSignalReturnStatement +
          "}\n\n";

        // Append and extra end of line to separate the wrap statement from
        // the rest since it has a Doxygen comment block (that's how the wrap
        // statement was started if this is an action signal).
        wrapStatement += '\n';
      }

      wrapStatements += convertMacros + wrapStatement;
      actionSignalsMethodDeclarations += actionSignalMethodDeclaration;
      actionSignalsMethodDefinitions +=  pluginEnumsTranslationMacros +
        actionSignalMethodDefinition;
    }
  }

  g_free(pIDs);

  if(gclass_ref)
    g_type_class_unref(gclass_ref);
  else if(ginterface_ref)
    g_type_default_interface_unref(ginterface_ref);

  return wrapStatements;
}

static std::string get_interface_macros(std::string& includeMacroCalls,
                                        std::string& cppExtends)
{
  std::string interfaceMacros;

  guint n_interfaces = 0;
  GType* interfaces = g_type_interfaces(type, &n_interfaces);

  GType parent_type = g_type_parent(type);

  for(guint i = 0; i < n_interfaces; i++)
  {
    if(!g_type_is_a(parent_type, interfaces[i]))
    {
      std::string interfaceCType = std::string(g_type_name(interfaces[i])) + '*';

      cppExtends += "public _TRANSLATE(`" + interfaceCType + "',`type')";

      if(i < n_interfaces - 1)
        cppExtends += ", ";

      interfaceMacros += "  _IMPLEMENTS_INTERFACE(_TRANSLATE(`" +
        interfaceCType + "',`type'))\n";

      includeMacroCalls += "_TRANSLATION_INCLUDE(" + interfaceCType + ")dnl\n";
    }
  }

  g_free(interfaces);
  return interfaceMacros;
}

static void generate_hg_file(const std::string& includeMacroCalls,
                             const std::string& cEnumDefinitions,
                             const std::string& enumWrapStatements,
                             const std::string& cppExtends,
                             const std::string& interfaceMacros,
                             const std::string& actionSignalsMethodDeclarations,
                             const std::string& propertyWrapStatements,
                             const std::string& signalWrapStatements)
{
  std::cout << "// Generated by generate_plugin_gmmproc_file. Don't edit this file." << std::endl << std::endl;
  std::cout << "include(plugingen_base.m4)dnl" << std::endl;
  std::cout << "changecom()dnl" << std::endl;
  std::cout << "#include <" << parentInclude << '/' <<
    to_lowercase(cppParentTypeName) << ".h>" << std::endl;

  std::cout << includeMacroCalls;

  std::cout << "_DEFS(" << target << ',' << defsFile << ')' << std::endl <<
    std::endl;

  std::cout << "_CONFIGINCLUDE(gstreamermmconfig.h)" << std::endl;
  std::cout << "_IS_DEPRECATED" << std::endl << std::endl;

  if(!cEnumDefinitions.empty())
  {
    std::cout << "// Plug-in C enums used in signals:" << std::endl;
    std::cout << cEnumDefinitions;
  }

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << '{' << std::endl << std::endl;

  if(!enumWrapStatements.empty())
    std::cout << enumWrapStatements;

  std::cout << "/** A Wrapper for the " << pluginName << " plugin." << std::endl;
  std::cout << " * Please note that not all plug-ins are available on all "
    "systems so care\n * must be taken that they exist before they are used "
    "otherwise there will\n * be errors and possibly a crash." << std::endl;
  std::cout << " *" << std::endl;
  std::cout << " * @ingroup " << nmspace << "Plugins" << std::endl;
  std::cout << " * @deprecated Plugins API is deprecated, and should not be used in a new code." << std::endl;
  std::cout << " */" << std::endl;
  std::cout << "class " << cppTypeName << std::endl;
  std::cout << ": public " << parentNameSpace << "::" << cppParentTypeName;

  if(!cppExtends.empty())
    std::cout << ", " << cppExtends;
  
  std::cout << std::endl;

  std::cout << '{' << std::endl;
  std::cout << "  _CLASS_GOBJECT(" << cppTypeName << ", " << cTypeName <<
    ", " << castMacro << "_GSTREAMERMM, " << parentNameSpace << "::" <<
    cppParentTypeName << ", " << cParentTypeName << ')' << std::endl;

  if(!interfaceMacros.empty())
    std::cout << interfaceMacros << std::endl;

  std::cout << "  _IS_GSTREAMERMM_PLUGIN" << std::endl;

  std::cout << "protected:" << std::endl;
  std::cout << "  " << cppTypeName << "();" << std::endl;
  std::cout << "  explicit " << cppTypeName << "(const Glib::ustring& name);" << std::endl << std::endl;

  std::cout << "public:" << std::endl;
  std::cout << "  /** Creates a new " << pluginName << " plugin with a unique name." << std::endl;
  std::cout << "   */" << std::endl;
  std::cout << "  _WRAP_CREATE()" << std::endl << std::endl;

  std::cout << "  /** Creates a new " << pluginName << " plugin with the given name." << std::endl;
  std::cout << "   */" << std::endl;
  std::cout << "  _WRAP_CREATE(const Glib::ustring& name)" << std::endl;

  if(!actionSignalsMethodDeclarations.empty())
    std::cout << std::endl << actionSignalsMethodDeclarations;

  if(!propertyWrapStatements.empty())
    std::cout << std::endl << propertyWrapStatements;

  if(!signalWrapStatements.empty())
    std::cout << std::endl << signalWrapStatements;

  std::cout << "};" << std::endl;

  std::cout << std::endl << "} // namespace " << nmspace << std::endl;
}

static void generate_ccg_file(const std::string& enumGTypeFunctionDefinitions,
  const std::string& actionSignalsMethodDefinitions)
{
  std::cout << "// Generated by generate_plugin_gmmproc_file. Don't edit this file." << std::endl << std::endl;
  std::cout << "include(plugingen_base.m4)dnl" << std::endl;
  std::cout << "changecom()dnl" << std::endl;
  std::cout << "_PINCLUDE(" << parentInclude << "/private/" <<
    to_lowercase(cppParentTypeName) << "_p.h)" << std::endl << std::endl;

  std::string getTypeName = to_lowercase(castMacro) + "_gstreamermm_get_type";

  std::cout << "extern \"C\"" << std::endl;
  std::cout << '{' << std::endl << std::endl;

  if(!enumGTypeFunctionDefinitions.empty())
    std::cout << enumGTypeFunctionDefinitions;

  std::cout << "GType " << getTypeName << "()" << std::endl;
  std::cout << '{' << std::endl;
  std::cout << "  static GType type = 0;" << std::endl;
  std::cout << "  GstElementFactory* factory = 0;" << std::endl;
  std::cout << "  GstPluginFeature* feature = 0;" << std::endl << std::endl;

  std::cout << "  if(!type)" << std::endl;
  std::cout << "  {" << std::endl;
  std::cout << "    factory = gst_element_factory_find(\"" << pluginName << "\");" << std::endl;

  std::cout << "    // Make sure that the feature is actually loaded:" << std::endl;
  std::cout << "    if(factory)" << std::endl;
  std::cout << "    {" << std::endl;
  std::cout << "      feature =" << std::endl;
  std::cout << "        gst_plugin_feature_load(GST_PLUGIN_FEATURE(factory));" << std::endl << std::endl;

  std::cout << "      g_object_unref(factory);" << std::endl;
  std::cout << "      factory = GST_ELEMENT_FACTORY(feature);" << std::endl;
  std::cout << "      type = gst_element_factory_get_element_type(factory);" << std::endl;
  std::cout << "      g_object_unref(factory);" << std::endl;
  std::cout << "    }" << std::endl;
  std::cout << "  }" << std::endl << std::endl;

  std::cout << "  return type;" << std::endl;
  std::cout << '}' << std::endl;

  std::cout << std::endl << "} // extern \"C\"" << std::endl << std::endl;

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << '{' << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName << "()" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", static_cast<char*>(0))" << std::endl;
  std::cout << "{}" << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName <<
    "(const Glib::ustring& name)" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", name.c_str())" << std::endl;
  std::cout << "{}" << std::endl << std::endl;

  if(!actionSignalsMethodDefinitions.empty())
    std::cout << actionSignalsMethodDefinitions;

  std::cout << '}' << std::endl;
}

} // anonymous namespace

int main(int argc, char** argv)
{
  gboolean hgFile = false;
  gboolean ccgFile = false;
  gboolean confirmExistence = false;

  static const GOptionEntry optionEntries[] =
  {
    {"hg", 'h', 0, G_OPTION_ARG_NONE, &hgFile, "Generate preliminary .hg file.", 0 },
    {"ccg", 'c', 0, G_OPTION_ARG_NONE, &ccgFile, "Generate preliminary .ccg file.", 0 },
    {"confirm-existence", 'e', 0, G_OPTION_ARG_NONE, &confirmExistence, "Returns success if the plugin exists.", 0 },
    {"namespace", 'n', 0, G_OPTION_ARG_STRING, &nmspace, "The namespace of the plugin.", "namespace" },
    {"main-defs", 'm', 0, G_OPTION_ARG_STRING, &defsFile, "The main defs file (no .defs extension).", "def" },
    {"target", 't', 0, G_OPTION_ARG_STRING, &target, "The .h and .cc target directory.", "directory" },
    { 0, '\0', 0, G_OPTION_ARG_NONE, 0, 0, 0 }
  };

  Glib::OptionContext optionContext("<plugin-name> [CppPluginClassName]");
  optionContext.set_summary(
    "Outputs a GStreamer plugin's gmmproc files to be processed by gmmproc "
    "for\nwrapping in gstreamermm.  Use the same syntax for the plugin name "
    "as in\ngst-inspect and supply the desired C++ class name unless "
    "the\n--confirm-existence option is used.  The generated files are "
    "preliminary\nfiles that need to be run through m4 including the macros "
    "in the\nplugingen*.m4 files to get the final .hg or .ccg file."
  );

  g_option_context_add_main_entries(optionContext.gobj(), optionEntries, 0);
  g_option_context_add_group(optionContext.gobj(), gst_init_get_option_group());

  try
  {
    if(!optionContext.parse(argc, argv))
    {
      std::cout << "Error parsing options and initializing.  Sorry." <<
        std::endl;
      return 1;
    }
  }
  catch(Glib::OptionError& error)
  {
      std::cout << "Error parsing options and initializing GStreamer." <<
        std::endl << "Run `" << argv[0] << " -?'  for a list of options." <<
        std::endl;
      return 1;
  }

  if(confirmExistence)
  {
    if(argc != 2)
    {
      std::cout << "A plugin name must be supplied to confirm plugin "
        "existence." << std::endl << "Run `" << argv[0] <<
        " -?'  for help." << std::endl;
      return 1;
    }
  }
  else if(argc != 3)
  {
    std::cout << "A plugin name and C++ class name must be supplied to "
      "generate gmmproc files." << std::endl <<
      "Run `" << argv[0] << " -?'  for help." << std::endl;
    return 1;
  }

  pluginName = argv[1];

  if(!confirmExistence)
    cppTypeName = argv[2];

  GstElementFactory* factory = 0;

  factory = gst_element_factory_find(pluginName.c_str());

  // Make sure that the feature is actually loaded:
  if(factory)
  {
    GstPluginFeature* loaded_feature =
            gst_plugin_feature_load(GST_PLUGIN_FEATURE(factory));

    g_object_unref(factory);
    factory = GST_ELEMENT_FACTORY(loaded_feature);
    type = gst_element_factory_get_element_type(factory);
  }

  if(type)
  {
    if(confirmExistence)
      return 0;

    if(!nmspace || !defsFile || !target)
    {
      std::cout << "A namespace, a default defs file and a target directory "
        "must be supplied" << std::endl << "with the --namespace, --main-defs "
        "and --target options (run with -? option for " << std::endl <<
        "details)." << std::endl;
      return 1;
    }

    cTypeName = g_type_name(type);
    cParentTypeName = g_type_name(g_type_parent(type));

    while(!cParentTypeName.empty() &&
      !is_wrapped_base_class(cParentTypeName) && !is_plugin(cParentTypeName))
    {
      cParentTypeName =
        g_type_name(g_type_parent(g_type_from_name(cParentTypeName.c_str())));
    }

    cppParentTypeName = cParentTypeName.substr(3);
    castMacro = get_cast_macro(cTypeName);

    // Check for gstreamermm base classes so that the Gst namespace and the
    // gstreamermm include directory is always used with them.
    if(
      cppParentTypeName.compare("AudioFilter") == 0 ||
      cppParentTypeName.compare("AudioSink") == 0 ||
      cppParentTypeName.compare("AudioSrc") == 0 ||
      cppParentTypeName.compare("AudioBaseSink") == 0 ||
      cppParentTypeName.compare("AudioBaseSrc") == 0 ||
      cppParentTypeName.compare("BaseSink") == 0 ||
      cppParentTypeName.compare("BaseSrc") == 0 ||
      cppParentTypeName.compare("BaseTransform") == 0 ||
      cppParentTypeName.compare("Bin") == 0 ||
      cppParentTypeName.compare("AudioCdSrc") == 0 ||
      cppParentTypeName.compare("Element") == 0 ||
      cppParentTypeName.compare("Object") == 0 ||
      cppParentTypeName.compare("Pipeline") == 0 ||
      cppParentTypeName.compare("PushSrc") == 0 ||
      cppParentTypeName.compare("VideoSink") == 0
      )
    {
      parentInclude = "gstreamermm";
      parentNameSpace = "Gst";
    }
    else
    {
      parentInclude = target;
      parentNameSpace = nmspace;
    }

    if(hgFile || ccgFile)
    {
      std::string includeMacroCalls;
      std::string cEnumDefinitions;
      std::string enumWrapStatements;
      std::string actionSignalsMethodDeclarations;
      std::string propertyWrapStatements;
      std::string signalWrapStatements;
      std::string enumGTypeFunctionDefinitions;
      std::string actionSignalsMethodDefinitions;

      propertyWrapStatements = get_property_wrap_statements(includeMacroCalls,
        enumWrapStatements, enumGTypeFunctionDefinitions);

      signalWrapStatements = get_signal_wrap_statements(includeMacroCalls,
        cEnumDefinitions, enumWrapStatements, actionSignalsMethodDeclarations,
        enumGTypeFunctionDefinitions, actionSignalsMethodDefinitions);

      if(hgFile)
      {
        std::string interfaceMacros;
        std::string cppExtends;

        interfaceMacros = get_interface_macros(includeMacroCalls, cppExtends);

        generate_hg_file(includeMacroCalls, cEnumDefinitions,
          enumWrapStatements, cppExtends, interfaceMacros,
          actionSignalsMethodDeclarations, propertyWrapStatements,
          signalWrapStatements);
      }
      else
      {
        generate_ccg_file(enumGTypeFunctionDefinitions,
          actionSignalsMethodDefinitions);
      }
    }
  }
  else
  {
    std::cerr << "Unrecognized Gstreamer element type." << std::endl;
   
    if(confirmExistence)
      return 1;

    if(hgFile)
    {
      std::cout << "_DEFS(" << target << ',' << defsFile << ')' <<
        std::endl << std::endl;

      std::cout << "// The build system does not know of a gstreamer plugin named " <<
        argv[1] << "." << std::endl;
      std::cout << "// A wrapper class for it was not generated." <<
        std::endl;
    }
  }

  if(factory)
    g_object_unref(factory);

  return 0;
}
