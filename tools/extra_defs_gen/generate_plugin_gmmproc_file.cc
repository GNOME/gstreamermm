/* $Id: generate_plugin_gmmproc_file.cc 740 2008-10-15 15:58:17Z jaalburqu $ */

/* generate_plugin_gmmproc_file.cc
 *
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

#include <gst/gst.h>
#include <glibmm.h>
#include <iostream>
#include <sstream>

static gchar* nmspace = 0;
static gchar* defsFile = 0;
static gchar* target = 0;

static Glib::ustring pluginName;
static Glib::ustring cTypeName;
static Glib::ustring cParentTypeName;
static Glib::ustring cppTypeName;
static Glib::ustring cppParentTypeName;
static Glib::ustring castMacro;
static Glib::ustring parentInclude;
static Glib::ustring parentNameSpace;

GType type = 0;

// To add a base class that is already wrapped to the list of wrapped base
// classes, add alphabetically below and increment WRAPPED_BASE_CLASSES_SIZE.
static const int WRAPPED_BASE_CLASSES_SIZE = 14;
static const char* wrappedBaseClasses[WRAPPED_BASE_CLASSES_SIZE] =
{
  "GstAudioFilter",
  "GstAudioSink",
  "GstAudioSrc",
  "GstBaseAudioSink",
  "GstBaseAudioSrc",
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

bool gst_type_is_a_pointer(GType gtype)
{
  return (g_type_is_a(gtype, G_TYPE_OBJECT) ||
    g_type_is_a(gtype, G_TYPE_BOXED) ||
    g_type_is_a(gtype, GST_TYPE_MINI_OBJECT));
}

Glib::ustring get_cast_macro(const Glib::ustring& typeName)
{
  Glib::ustring result;

  Glib::ustring::const_iterator iter = typeName.end();

  bool prev_is_upper = false;
  bool prev_is_lower = true;  // Going backwards so last char should be lower.
  int underscore_char_count = 0; // Used to count characters between underscores.

  for(--iter; iter != typeName.begin(); --iter, ++underscore_char_count)
  {
    if(g_unichar_isupper(*iter))
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
      result.insert(0, 1, g_unichar_toupper(*iter));
      prev_is_upper = false;
      prev_is_lower = true;
    }
  }

  // Insert first character (not included in the for loop).
  result.insert(0, 1, g_unichar_toupper(*iter));

  return result;
}

bool is_wrapped_base_class(const Glib::ustring& cTypeName)
{
  for(int i = 0; i < WRAPPED_BASE_CLASSES_SIZE &&
    cTypeName.compare(wrappedBaseClasses[i]) >= 0; i++)
  {
    if(cTypeName.compare(wrappedBaseClasses[i]) == 0)
      return true;
  }

  return false;
}

bool is_plugin(const Glib::ustring& cTypeName)
{
  GstElementFactory* fact = gst_element_factory_find(
    cTypeName.substr(3).lowercase().c_str());

  bool const result = (fact != 0);

  if(fact)
    g_object_unref(fact);

  return result;
}

Glib::ustring get_property_wrap_statements(Glib::ustring& includeMacroCalls,
  Glib::ustring& enumWrapStatements,
  Glib::ustring& enumGTypeFunctionDefinitions)
{
  Glib::ustring wrapStatements;

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
        Glib::ustring propertyName = g_param_spec_get_name(pParamSpec);

        Glib::ustring  propertyCType = g_type_name(propertyGType) +
          (Glib::ustring) (gst_type_is_a_pointer(propertyGType) ?  "*" : "");

        if((G_TYPE_IS_ENUM(propertyGType) || G_TYPE_IS_FLAGS(propertyGType)))
        {
          Glib::ustring enumPrefix = propertyCType.substr(0, 3);
          Glib::ustring propertyCppType = propertyCType.substr(3);

          enumWrapStatements += "_WRAP_PLUGIN_ENUM(" + enumPrefix + "," +
            propertyCppType + ")";

          Glib::ustring enumGetTypeFunctionName =
            get_cast_macro(propertyCType).lowercase() + "_get_type";

          enumGTypeFunctionDefinitions +=
            "_PLUGIN_ENUM_GET_TYPE_FUNC(" + propertyCType + ")";
        }

        wrapStatements += "  _WRAP_PROPERTY(\"" + propertyName + "\", " +
          "_TRANSLATE(" + propertyCType + ", `return'))\n";

        includeMacroCalls += "_TRANSLATION_INCLUDE(" + propertyCType + ")dnl\n";
      }
    }
  }

  g_free(ppParamSpec);
  return wrapStatements;
}

Glib::ustring get_method_name(const Glib::ustring& signalName)
{
  Glib::ustring result;

  for(Glib::ustring::const_iterator iter = signalName.begin();
    iter != signalName.end(); ++iter)
  {
    if((*iter) == '-')
    {
      result.push_back('_');
    }
    else
      result.push_back(*iter);
  }

  return result;
}

Glib::ustring get_c_enum_definition_macro(GType enumGType,
  Glib::ustring& enumCType)
{
  Glib::ustring result;

  if((G_TYPE_IS_ENUM(enumGType)))
  {
    GEnumClass* enumClass = G_ENUM_CLASS(g_type_class_ref(enumGType));
    if(enumClass)
    {
      result += "_C_ENUM_DEFINITION(" + enumCType + ",";
      for(guint i = 0; i < enumClass->n_values; i++)
      {
        std::stringstream stream;
        result += (Glib::ustring) enumClass->values[i].value_nick + ",";
        stream << enumClass->values[i].value;
        result += stream.str();
        if(i < enumClass->n_values - 1)
          result += ",";
      }
      result += ")";
    }
    g_type_class_unref(enumClass);
  }
  else
  {
    GFlagsClass* flagsClass = G_FLAGS_CLASS(g_type_class_ref(enumGType));
    if(flagsClass)
    {
      result += "_C_ENUM_DEFINITION(" + enumCType + ",";
      for(guint i = 0; i < flagsClass->n_values; i++)
      {
        std::stringstream stream;
        result += (Glib::ustring) flagsClass->values[i].value_nick + ",";
        stream << flagsClass->values[i].value;
        result += stream.str();
        if(i < flagsClass->n_values - 1)
          result += ",";
      }
      result += ")";
    }
    g_type_class_unref(flagsClass);
  }
  return result;
}

Glib::ustring get_signal_wrap_statements(Glib::ustring& includeMacroCalls,
  Glib::ustring& cEnumDefinitions, Glib::ustring& enumWrapStatements,
  Glib::ustring& cClassSignalDeclarations,
  Glib::ustring& enumGTypeFunctionDefinitions)
{
  Glib::ustring wrapStatements;

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
      Glib::ustring convertMacros;
      Glib::ustring wrapStatement;

      guint signal_id = pIDs[i];

      //Name:
      Glib::ustring signalName = g_signal_name(signal_id);
      Glib::ustring signalMethodName = get_method_name(signalName);

      //Other information about the signal:
      GSignalQuery signalQuery = { 0, 0, 0, GSignalFlags(0), 0, 0, 0, };
      g_signal_query(signal_id, &signalQuery);

      //Return type:
      GType returnGType = signalQuery.return_type & ~G_SIGNAL_TYPE_STATIC_SCOPE;

      Glib::ustring  returnCType = g_type_name(returnGType) +
        (Glib::ustring) (gst_type_is_a_pointer(returnGType) ?  "*" : "");

      if((G_TYPE_IS_ENUM(returnGType) || G_TYPE_IS_FLAGS(returnGType)))
      // Check for an enum first and attempt to generate _WRAP_ENUM() and
      // _TRANSLATION() macros if it is not wrapped (see plugingen_base.m4
      // file for docs).
      {
        Glib::ustring enumPrefix = returnCType.substr(0, 3);
        Glib::ustring returnCppType = returnCType.substr(3);

        enumWrapStatements += "_WRAP_PLUGIN_ENUM(" + enumPrefix + "," +
          returnCppType + ")";

        Glib::ustring enumGetTypeFunctionName =
          get_cast_macro(returnCType).lowercase() + "_get_type";

        enumGTypeFunctionDefinitions +=
          "_PLUGIN_ENUM_GET_TYPE_FUNC(" + returnCType + ")";

        cEnumDefinitions += get_c_enum_definition_macro(returnGType,
          returnCType);
      }
      else if(gst_type_is_a_pointer(returnGType))
      {
        if(g_type_is_a(returnGType, G_TYPE_BOXED))
        // Boxed type returns for signals need special conversions because
        // when unwrapping them, gobj_copy() should be used instead of just
        // gobj() to guard against losing the original with a temporary
        // wrapper.
        {
          // Unwrapping conversion:
          convertMacros += "#m4 _CONVERSION(_LQ()_TRANSLATE(" + returnCType +
            ",`type')_RQ(), ``" + returnCType + "'', ";
          convertMacros +=  "``($3).gobj_copy()'')\n";

          // Also include a wrapping conversion:

          if(returnGType == GST_TYPE_TAG_LIST)
          // Dealing with a GstTagList* return which has a special Glib::wrap()
          // because of the conflict with the Glib::wrap() for GstStructure*
          // (GstTagList is infact a GstStructure).
          {
            convertMacros += "#m4 _CONVERSION(``" + returnCType +
              "'', _LQ()_TRANSLATE(" + returnCType + ",`return')_RQ(), ";
            convertMacros +=  "``Glib::wrap($3, 0)'')\n";
          }
          else
          // Dealing with a regular boxed type return.
          {
            convertMacros += "#m4 _CONVERSION(``" + returnCType +
              "'', _LQ()_TRANSLATE(" + returnCType + ",`return')_RQ(), ";
            convertMacros +=  "``Glib::wrap($3)'')\n";
          }
        }
        else
        // Dealing with a RefPtr<> return so include a wrapping conversion
        // just so these conversions can be automatic for plug-ins and not
        // needed in the global convert file.  (An unwrapping conversion will
        // already probably be included in the global convert file).
        {
          convertMacros += "#m4 _CONVERSION(``" + returnCType +
            "'', _LQ()_TRANSLATE(" + returnCType + ",`return')_RQ(), ";
          convertMacros += g_type_is_a(returnGType, GST_TYPE_MINI_OBJECT) ?
            "``Gst::wrap($3)'')\n" : "``Glib::wrap($3)'')\n";
        }
      }

      includeMacroCalls += "_TRANSLATION_INCLUDE(" + returnCType + ")dnl\n";

      wrapStatement = "  _WRAP_SIGNAL(_TRANSLATE("  + returnCType +
        ", `return') " + signalMethodName + "(";

      cClassSignalDeclarations += "  " + returnCType + " (*" +
        signalMethodName + ") (" + cTypeName + "* element";

      //Loop through the list of parameters:
      const GType* pParameters = signalQuery.param_types;
      if(pParameters)
      {
        for(unsigned i = 0; i < signalQuery.n_params; i++)
        {
          GType paramGType = pParameters[i] & ~G_SIGNAL_TYPE_STATIC_SCOPE;

          //Parameter name:
          //TODO: How can we get the real parameter name?
          gchar* pchNum = g_strdup_printf("%d", i);
          Glib::ustring paramName = "arg" + std::string(pchNum);
          g_free(pchNum);
          pchNum = 0;

          Glib::ustring  paramCType = g_type_name(paramGType) +
            (Glib::ustring) (gst_type_is_a_pointer(paramGType) ?  "*" : "");

          includeMacroCalls += "_TRANSLATION_INCLUDE(" + paramCType + ")dnl\n";

          // Include wrapping conversions for signal parameters.  (Unwrapping
          // conversions will already probably be defined in the global
          // convert file).  Also try to wrap plug-in specific enums:

          if((G_TYPE_IS_ENUM(paramGType) || G_TYPE_IS_FLAGS(paramGType)))
          // Check for an enum first and attempt to generate _WRAP_ENUM() and
          // _TRANSLATION() macros and other necessary code if it is not
          // wrapped (see plugingen_base.m4 file for docs).
          {
            Glib::ustring enumPrefix = paramCType.substr(0, 3);
            Glib::ustring paramCppType = paramCType.substr(3);

            enumWrapStatements += "_WRAP_PLUGIN_ENUM(" + enumPrefix + "," +
              paramCppType + ")";

            Glib::ustring enumGetTypeFunctionName =
              get_cast_macro(paramCType).lowercase() + "_get_type";

            enumGTypeFunctionDefinitions +=
              "_PLUGIN_ENUM_GET_TYPE_FUNC(" + paramCType + ")";

            cEnumDefinitions += get_c_enum_definition_macro(paramGType,
              paramCType);
          }
          if(gst_type_is_a_pointer(paramGType))
          {
            if(paramGType == GST_TYPE_TAG_LIST)
            // Dealing with a GstTagList* which has a special Glib::wrap()
            // because of the conflict with the Glib::wrap() for GstStructure*
            // (GstTagList is in fact a GstStructure).
            {
              convertMacros += "#m4 _CONVERSION(``" + paramCType +
                "'', _LQ()_TRANSLATE(" + paramCType + ",`param')_RQ(), ";
              convertMacros +=  "``Glib::wrap($3, 0, true)'')\n";
            }
            else
            // Dealing with reference counted parameter or a boxed type.
            {
              convertMacros += "#m4 _CONVERSION(``" + paramCType +
                "'', _LQ()_TRANSLATE(" + paramCType + ",`param')_RQ(), ";
              convertMacros += g_type_is_a(paramGType, GST_TYPE_MINI_OBJECT) ?
                "``Gst::wrap($3, true)'')\n" : "``Glib::wrap($3, true)'')\n";
            }
          }

          wrapStatement += "_TRANSLATE(" + paramCType + ", `param') " +
            paramName;

          cClassSignalDeclarations += ", " + paramCType + " " + paramName;

          if(i < signalQuery.n_params - 1)
            wrapStatement += ", ";
        }
      }
      wrapStatement += "), \"" + signalName + "\")\n";

      wrapStatements += convertMacros + wrapStatement;

      cClassSignalDeclarations += ");\n";
    }
  }

  g_free(pIDs);

  if(gclass_ref)
    g_type_class_unref(gclass_ref); //to match the g_type_class_ref() above.
  else if(ginterface_ref)
    g_type_default_interface_unref(ginterface_ref); // for interface ref above.

  return wrapStatements;
}

Glib::ustring get_interface_macros(Glib::ustring& includeMacroCalls,
  Glib::ustring& cppExtends)
{
  Glib::ustring interfaceMacros;

  guint n_interfaces = 0;
  GType* interfaces = g_type_interfaces(type, &n_interfaces);

  GType parent_type = g_type_parent(type);

  for(guint i = 0; i < n_interfaces; i++)
  {
    if(!g_type_is_a(parent_type, interfaces[i]))
    {
      Glib::ustring  interfaceCType = g_type_name(interfaces[i]) +
        (Glib::ustring) "*";

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

void generate_hg_file(const Glib::ustring& includeMacroCalls,
  const Glib::ustring& cEnumDefinitions,
  const Glib::ustring& enumWrapStatements,
  const Glib::ustring& cppExtends,
  const Glib::ustring& interfaceMacros,
  const Glib::ustring& propertyWrapStatements,
  const Glib::ustring& signalWrapStatements)
{
  std::cout << "// Generated by run_generate_plugin_gmmproc_file. Don't edit this file." << std::endl << std::endl;
  std::cout << "include(plugingen_base.m4)dnl" << std::endl;
  std::cout << "changecom()dnl" << std::endl;
  std::cout << "#include <" << parentInclude << "/" <<
    cppParentTypeName.lowercase() << ".h>" << std::endl;

  std::cout << includeMacroCalls;

  std::cout << "_DEFS(" << target << "," << defsFile << ")" << std::endl <<
    std::endl;

  if(!cEnumDefinitions.empty())
  {
    std::cout << "// Plug-in C enums used in signals:" << std::endl;
    std::cout << cEnumDefinitions;
  }

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << "{" << std::endl << std::endl;

  if(!enumWrapStatements.empty())
    std::cout << enumWrapStatements;

  std::cout << "/** " << nmspace << "::" << cppTypeName << " - " << pluginName << " plugin." << std::endl;
  std::cout << " * Please note that, though using the underlying GObject is "
    "fine, using its C\n * <B>type</B> is not guaranteed to be API stable "
    "across releases because it is\n * not guaranteed to always remain the "
    "same.  Also, not all plug-ins are\n * available on all systems so care "
    "must be taken that they exist before they\n * are used, otherwise there "
    "will be errors and possibly a crash." << std::endl;
  std::cout << " *" << std::endl;
  std::cout << " * @ingroup " << nmspace << "Plugins" << std::endl;
  std::cout << " */" << std::endl;
  std::cout << "class " << cppTypeName << std::endl;
  std::cout << ": public " << parentNameSpace << "::" << cppParentTypeName;

  if(!cppExtends.empty())
    std::cout << ", " << cppExtends;
  
  std::cout << std::endl;

  std::cout << "{" << std::endl;
  std::cout << "  _CLASS_GOBJECT(" << cppTypeName << ", " << cTypeName <<
    ", " << castMacro << ", " << parentNameSpace << "::" <<
    cppParentTypeName << ", " << cParentTypeName << ")" << std::endl;

  if(!interfaceMacros.empty())
    std::cout << interfaceMacros << std::endl;

  std::cout << "  _IS_GSTREAMERMM_PLUGIN" << std::endl << std::endl;

  std::cout << "protected:" << std::endl;
  std::cout << "  " << cppTypeName << "();" << std::endl;
  std::cout << "  " << cppTypeName << "(const Glib::ustring& name);" << std::endl << std::endl;

  std::cout << "public:" << std::endl;
  std::cout << "/** Creates a new " << pluginName << " plugin with a unique name." << std::endl;
  std::cout << " */" << std::endl;
  std::cout << "  _WRAP_CREATE()" << std::endl << std::endl;

  std::cout << "/** Creates a new " << pluginName << " plugin with the given name." << std::endl;
  std::cout << " */" << std::endl;
  std::cout << "  _WRAP_CREATE(const Glib::ustring& name)" << std::endl;

  if(!propertyWrapStatements.empty())
    std::cout << std::endl << propertyWrapStatements;

  if(!signalWrapStatements.empty())
    std::cout << std::endl << signalWrapStatements;

  std::cout << "};" << std::endl;

  std::cout << std::endl << "} //namespace " << nmspace << std::endl;
}

void generate_ccg_file(const Glib::ustring& enumGTypeFunctionDefinitions,
  const Glib::ustring& cClassSignalDeclarations)
{
  std::cout << "include(plugingen_base.m4)dnl" << std::endl;
  std::cout << "changecom()dnl" << std::endl;
  std::cout << "_PINCLUDE(" << parentInclude << "/private/" <<
    cppParentTypeName.lowercase() << "_p.h)" << std::endl << std::endl;

  //Only output ObjectClass with signal declarations if there are signals:
  if(!cClassSignalDeclarations.empty())
  {
    std::cout << "struct _" << cTypeName << "Class" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "  " << cParentTypeName << "Class parent_class;" << std::endl;
    std::cout << cClassSignalDeclarations;
    std::cout << "};" << std::endl << std::endl;
  }

  Glib::ustring getTypeName = castMacro.lowercase() + "_get_type";

  std::cout << "extern \"C\"" << std::endl;
  std::cout << "{" << std::endl << std::endl;

  if(!enumGTypeFunctionDefinitions.empty())
    std::cout << enumGTypeFunctionDefinitions;

  std::cout << "GType " << getTypeName << "()" << std::endl;
  std::cout << "{" << std::endl;
  std::cout << "  static GType type = 0;" << std::endl;
  std::cout << "  GstElementFactory* factory = 0;" << std::endl;
  std::cout << "  GstPluginFeature* feature = 0;" << std::endl << std::endl;

  std::cout << "  if(!type)" << std::endl; std::cout << "  {" << std::endl;
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
  std::cout << "}" << std::endl;

  std::cout << std::endl << "} // extern \"C\"" << std::endl << std::endl;

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << "{" << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName << "()" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", 0)" << std::endl;
  std::cout << "{}" << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName <<
    "(const Glib::ustring& name)" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", name.c_str())" << std::endl;
  std::cout << "{}" << std::endl << std::endl;

  std::cout << "}" << std::endl;
}

int main(int argc, char* argv[])
{
  gboolean hgFile = false;
  gboolean ccgFile = false;
  gboolean confirmExistence = false;

  if(!g_thread_supported())
    g_thread_init(0);

  GOptionEntry optionEntries[] =
  {
    {"hg", 'h', 0, G_OPTION_ARG_NONE, &hgFile, "Generate preliminary .hg file.", 0 },
    {"ccg", 'c', 0, G_OPTION_ARG_NONE, &ccgFile, "Generate .ccg file.", 0 },
    {"confirm-existence", 'e', 0, G_OPTION_ARG_NONE, &confirmExistence, "Return success if the plugin exists, failure otherwise.", 0 },
    {"namespace", 'n', 0, G_OPTION_ARG_STRING, &nmspace, "The namespace of the plugin.", "namespace" },
    {"main-defs", 'm', 0, G_OPTION_ARG_STRING, &defsFile, "The main defs file without .defs extension.", "def" },
    {"target", 't', 0, G_OPTION_ARG_STRING, &target, "The .h and .cc target directory.", "directory" },
    { 0 }
  };

  GOptionContext* gContext =
    g_option_context_new("<plugin-name> [CppPluginClassName]");
  g_option_context_set_summary(gContext, "Outputs a GStreamer plugin's "
    "gmmproc files to be processed by gmmproc for\nwrapping in gstreamermm.  "
    "Use the same syntax for plugin-name as in gst-inspect\nand supply the "
    "desired C++ class name unless the --confirm-existence option is\nused.  "
    "The .hg file is a preliminary .hg file that needs to be run through "
    "m4\nincluding the macros in the plugingen*.m4 files.");

  g_option_context_add_main_entries(gContext, optionEntries, 0);
  g_option_context_add_group(gContext, gst_init_get_option_group());

  Glib::OptionContext optionContext(gContext, true);

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    if(!optionContext.parse(argc, argv))
#else
    std::auto_ptr<Glib::Error> error;
    if (!optionContext.parse(argc, argv, error))
#endif
    {
      std::cout << "Error parsing options and initializing.  Sorry." <<
        std::endl;
      return -1;
    }
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::OptionError& error)
  {
#else 
  if (error.get())
  {
#endif
      std::cout << "Error parsing options and initializing GStreamer." <<
        std::endl << "Run `" << argv[0] << " -?'  for a list of options." <<
        std::endl;
      return -1;
  }

  if(confirmExistence)
  {
    if(argc != 2)
    {
      std::cout << "A plugin name must be supplied to confirm plugin "
        "existence." << std::endl << "Run `" << argv[0] <<
        " -?'  for help." << std::endl;
      return -1;
    }
  }
  else if(argc != 3)
  {
    std::cout << "A plugin name and C++ class name must be supplied to "
      "generate gmmproc files." << std::endl <<
      "Run `" << argv[0] << " -?'  for help." << std::endl;
    return -1;
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
      return -1;
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
      cppParentTypeName.compare("BaseAudioSink") == 0 ||
      cppParentTypeName.compare("BaseAudioSrc") == 0 ||
      cppParentTypeName.compare("BaseSink") == 0 ||
      cppParentTypeName.compare("BaseSrc") == 0 ||
      cppParentTypeName.compare("BaseTransform") == 0 ||
      cppParentTypeName.compare("Bin") == 0 ||
      cppParentTypeName.compare("CddaBaseSrc") == 0 ||
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
      Glib::ustring includeMacroCalls;
      Glib::ustring cEnumDefinitions;
      Glib::ustring enumWrapStatements;
      Glib::ustring propertyWrapStatements;
      Glib::ustring signalWrapStatements;
      Glib::ustring cClassSignalDeclarations;
      Glib::ustring enumGTypeFunctionDefinitions;

      propertyWrapStatements = get_property_wrap_statements(includeMacroCalls,
        enumWrapStatements, enumGTypeFunctionDefinitions);

      signalWrapStatements = get_signal_wrap_statements(includeMacroCalls,
        cEnumDefinitions, enumWrapStatements, cClassSignalDeclarations,
        enumGTypeFunctionDefinitions);

      if(hgFile)
      {
        Glib::ustring interfaceMacros;
        Glib::ustring cppExtends;

        interfaceMacros = get_interface_macros(includeMacroCalls, cppExtends);

        generate_hg_file(includeMacroCalls, cEnumDefinitions,
          enumWrapStatements, cppExtends, interfaceMacros,
          propertyWrapStatements, signalWrapStatements);
      }
      else
      {
        generate_ccg_file(enumGTypeFunctionDefinitions,
          cClassSignalDeclarations);
      }
    }
  }
  else
  {
    std::cerr << "Unrecognized Gstreamer element type." << std::endl;
   
    if(confirmExistence)
      return -1;

    if(hgFile)
    {
      std::cout << "_DEFS(" << target << "," << defsFile << ")" <<
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
