/* $Id: generate_plugin_gmmproc_file.cc 740 2008-10-15 15:58:17Z jaalburqu $ */

/* generate_plugin_gmmproc_file.cc
 *
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include "gst_type_is_a_pointer.h"

#include <gst/gst.h>
#include <glibmm.h>
#include <iostream>

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

// To add an enum that is already wrapped to the list of wrapped enum, add
// alphabetically below and increment WRAPPED_ENUMS_SIZE.
static const int WRAPPED_ENUMS_SIZE = 41;
static const char* wrappedEnums[WRAPPED_ENUMS_SIZE] =
{
  "GstActivateMode",
  "GstAssocFlags",
  "GstBufferCopyFlags",
  "GstBufferFlag",
  "GstBufferingMode",
  "GstBusFlags",
  "GstBusSyncReply",
  "GstClockEntryType",
  "GstClockFlags",
  "GstClockReturn",
  "GstColorBalanceType",
  "GstElementFlags",
  "GstEventType",
  "GstEventTypeFlags",
  "GstFlowReturn",
  "GstFormat",
  "GstIndexCertainty",
  "GstIndexEntryType",
  "GstIndexFlags",
  "GstIndexLookupMethod",
  "GstIndexResolverMethod",
  "GstIteratorItem",
  "GstIteratorResult",
  "GstMessageType",
  "GstMiniObjectFlags",
  "GstPadDirection",
  "GstPadFlags",
  "GstPadLinkReturn",
  "GstPadPresence",
  "GstPadTemplateFlags",
  "GstQueryType",
  "GstRank",
  "GstSeekFlags",
  "GstSeekType",
  "GstState",
  "GstStateChange",
  "GstStateChangeReturn",
  "GstTagFlag",
  "GstTagMergeMode",
  "GstTaskState",
  "GstURIType"
};

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

Glib::ustring get_cast_macro(const Glib::ustring& typeName)
{
  Glib::ustring result;

  Glib::ustring::const_iterator iter = typeName.begin();

  if (iter != typeName.end())
    result.push_back(*iter);

  int encountered_upper = 1; // The first char (above) should be upper

  for (++iter; iter != typeName.end(); ++iter)
  {
    if (g_unichar_isupper(*iter))
    {
      if (!encountered_upper || encountered_upper > 1)
        result.push_back('_');
      ++encountered_upper;
    }
    else
      encountered_upper = 0;

    result.push_back(g_unichar_toupper(*iter));
  }

  return result;
}

bool is_wrapped_enum(const Glib::ustring& cTypeName)
{
  for (int i = 0; i < WRAPPED_ENUMS_SIZE &&
    cTypeName.compare(wrappedEnums[i]) >= 0; i++)
  {
    if (cTypeName.compare(wrappedEnums[i]) == 0)
      return true;
  }

  return false;
}

bool is_wrapped_base_class(const Glib::ustring& cTypeName)
{
  for (int i = 0; i < WRAPPED_BASE_CLASSES_SIZE &&
    cTypeName.compare(wrappedBaseClasses[i]) >= 0; i++)
  {
    if (cTypeName.compare(wrappedBaseClasses[i]) == 0)
      return true;
  }

  return false;
}

bool is_plugin(const Glib::ustring& cTypeName)
{
  GstElementFactory* fact = gst_element_factory_find(
    cTypeName.substr(3).lowercase().c_str());

  bool const result = (fact != 0);

  if (fact)
    g_object_unref(fact);

  return result;
}

void get_property_wrap_statements(Glib::ustring& wrapStatements,
  Glib::ustring& includeMacroCalls, Glib::ustring& enumWrapStatements,
  Glib::ustring& enumGTypeFunctionDefinitions)
{
  //Get the list of properties:
  GParamSpec** ppParamSpec = 0;
  guint iCount = 0;
  if(G_TYPE_IS_OBJECT(type))
  {
    GObjectClass* pGClass = G_OBJECT_CLASS(g_type_class_ref(type));
    ppParamSpec = g_object_class_list_properties (pGClass, &iCount);
    g_type_class_unref(pGClass);
  }
  else if (G_TYPE_IS_INTERFACE(type))
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

      if (ownerGType == type)
      {
        //Name and type:
        Glib::ustring propertyName = g_param_spec_get_name(pParamSpec);

        Glib::ustring  propertyCType = g_type_name(propertyGType) +
          (Glib::ustring) (gst_type_is_a_pointer(propertyGType) ?  "*" : "");

        bool enumIsWrapped = false;

        if ((G_TYPE_IS_ENUM(propertyGType) || G_TYPE_IS_FLAGS(propertyGType)) &&
          !(enumIsWrapped = is_wrapped_enum(propertyCType)))
        {
          Glib::ustring propertyCppType = propertyCType.substr(3);

          enumWrapStatements += "_WRAP_ENUM(" + propertyCType.substr(3) + ", " +
            propertyCType + ")\n";
          enumWrapStatements += "_CCONVERSION(`" + propertyCType + "',`" +
            propertyCppType + "',`" + propertyCppType + "')dnl\n";

          Glib::ustring enumGetTypeFunctionName =
            get_cast_macro(propertyCType).lowercase() + "_get_type";

          enumGTypeFunctionDefinitions +=
            "extern \"C\" GType " + enumGetTypeFunctionName + "()\n" +
            "{\n" +
            "  return g_type_from_name(\"" + propertyCType + "\");\n" +
            "}\n\n";
        }

        wrapStatements += "  _WRAP_PROPERTY(\"" + propertyName + "\", " +
          "_CCONVERT(" + propertyCType + ", `ret'))\n";

        if (!G_TYPE_IS_ENUM(propertyGType) || enumIsWrapped)
          includeMacroCalls += "_CCONVERSION_INCLUDE(" + propertyCType + ")dnl\n";
      }
    }
  }

  g_free(ppParamSpec);
}

Glib::ustring get_method_name(const Glib::ustring& signalName)
{
  Glib::ustring result;

  for (Glib::ustring::const_iterator iter = signalName.begin();
    iter != signalName.end(); ++iter)
  {
    if ((*iter) == '-')
    {
      result.push_back('_');
    }
    else
      result.push_back(*iter);
  }

  return result;
}

void get_signal_wrap_statements(Glib::ustring& wrapStatements,
  Glib::ustring& includeMacroCalls, Glib::ustring& cClassSignalDeclarations)
{
  gpointer gclass_ref = 0;
  gpointer ginterface_ref = 0;

  if(G_TYPE_IS_OBJECT(type))
    gclass_ref = g_type_class_ref(type); //Ensures that class_init() is called.
  else if(G_TYPE_IS_INTERFACE(type))
    ginterface_ref = g_type_default_interface_ref(type); //install signals.

  //Get the list of signals:
  guint iCount = 0;
  guint* pIDs = g_signal_list_ids (type, &iCount);

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

      includeMacroCalls += "_CCONVERSION_INCLUDE(" + returnCType + ")dnl\n";

      wrapStatement = "  _WRAP_SIGNAL(_CCONVERT("  + returnCType +
        ", `ret') " + signalMethodName + "(";

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

          includeMacroCalls += "_CCONVERSION_INCLUDE(" + paramCType + ")dnl\n";

          if (gst_type_is_a_pointer(paramGType))
          {
            convertMacros += "#m4 _CONVERSION(``" + paramCType +
              "'', _LQ()_CCONVERT(" + paramCType + ",`param')_RQ(), ";
            convertMacros += g_type_is_a(paramGType, GST_TYPE_MINI_OBJECT) ?
              "``Gst::wrap($3, true)'')\n" : "``Glib::wrap($3, true)'')\n";
          }

          wrapStatement += "_CCONVERT(" + paramCType + ", `param') " +
            paramName;

          cClassSignalDeclarations += ", " + paramCType + " " + paramName;

          if (i < signalQuery.n_params - 1)
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
}

void get_interface_macros(Glib::ustring& interfaceMacros,
  Glib::ustring& includeMacroCalls,
  Glib::ustring& cppExtends)
{
  guint n_interfaces = 0;
  GType* interfaces = g_type_interfaces(type, &n_interfaces);

  for (int i = 0; i < n_interfaces; i++)
  {
      Glib::ustring  interfaceCType = g_type_name(interfaces[i]) +
        (Glib::ustring) "*";

      cppExtends += "public _CCONVERT(`" + interfaceCType + "',`type')";

      if (i < n_interfaces - 1)
        cppExtends += ", ";

      interfaceMacros += "  _IMPLEMENTS_INTERFACE(_CCONVERT(`" +
              interfaceCType + "',`type'))\n";

      //TODO: The following is to include the interface headers that the
      //plug-in implements.  Uncomment after the rest of the interfaces have
      //been wrapped.
      //includeMacroCalls += "_CCONVERSION_INCLUDE(" + interfaceCType + ")dnl\n";
  }

  g_free(interfaces);
}

void generate_hg_file(const Glib::ustring& includeMacroCalls,
  const Glib::ustring& enumWrapStatements,
  const Glib::ustring& cppExtends,
  const Glib::ustring& interfaceMacros,
  const Glib::ustring& propertyWrapStatements,
  const Glib::ustring& signalWrapStatements)
{
  std::cout << "include(ctocpp_base.m4)dnl" << std::endl;
  std::cout << "changecom()dnl" << std::endl;
  std::cout << "#include <" << parentInclude << "/" <<
    cppParentTypeName.lowercase() << ".h>" << std::endl;

  std::cout << includeMacroCalls;

  std::cout << "_DEFS(" << target << "," << defsFile << ")" << std::endl <<
    std::endl;

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << "{" << std::endl << std::endl;

  std::cout << enumWrapStatements << std::endl;

  std::cout << "/** " << nmspace << "::" << cppTypeName << " — " << pluginName << " plugin." << std::endl;
  std::cout << " * Please include <" << target << "/" <<
    cppTypeName.lowercase() << ".h> to use.  Please note that, though\n"
    " * using the underlying GObject is fine, using its C <B>type</B> is not\n"
    " * guaranteed to be API stable across releases because it is not "
    "guaranteed to\n * always remain the same.  Also, not all plug-ins are "
    "available on all systems\n * and the ones that aren't available are not "
    "included in the build." << std::endl;
  std::cout << " *" << std::endl;
  std::cout << " * @ingroup " << nmspace << "Plugins" << std::endl;
  std::cout << " */" << std::endl;
  std::cout << "class " << cppTypeName << std::endl;
  std::cout << ": public " << parentNameSpace << "::" << cppParentTypeName;

  //TODO: The following  is to have the plug-in class extend the interfaces
  //that it implements.  Include after the rest of the interfaces have been
  //wrapped.
  //if (!cppExtends.empty())
  //  std::cout << ", " << cppExtends;
  
  std::cout << std::endl;

  std::cout << "{" << std::endl;
  std::cout << "  _CLASS_GOBJECT(" << cppTypeName << ", " << cTypeName <<
    ", " << castMacro << ", " << parentNameSpace << "::" <<
    cppParentTypeName << ", " << cParentTypeName << ")" << std::endl;

  //TODO: The following is to include the _IMPLEMENT_INTERFACE() macros in the
  //plug-in class definition.  Uncomment after the rest of the interfaces have
  //been wrapped.
  //std::cout << interfaceMacros << std::endl;

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
  std::cout << "  _WRAP_CREATE(const Glib::ustring& name)" << std::endl <<
    std::endl;

  std::cout << propertyWrapStatements;

  std::cout << std::endl << signalWrapStatements;

  std::cout << "};" << std::endl;

  std::cout << std::endl << "} //namespace " << nmspace << std::endl;
}

void generate_ccg_file(const Glib::ustring& enumGTypeFunctionDefinitions,
  const Glib::ustring& cClassSignalDeclarations)
{
  std::cout << "_PINCLUDE(" << parentInclude << "/private/" <<
    cppParentTypeName.lowercase() << "_p.h)" << std::endl << std::endl;

  //Only output ObjectClass with signal declarations if there are signals:
  if (!cClassSignalDeclarations.empty())
  {
    std::cout << "struct _" << cTypeName << "Class" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "  " << cParentTypeName << "Class parent_class;" << std::endl;
    std::cout << cClassSignalDeclarations;
    std::cout << "};" << std::endl << std::endl;
  }

  Glib::ustring getTypeName = castMacro.lowercase() + "_get_type";

  std::cout << "extern \"C\" GType " << getTypeName << "();" << std::endl;
  std::cout << "GType " << getTypeName << "()" << std::endl;
  std::cout << "{" << std::endl;
  std::cout << "  static GType type = 0;" << std::endl;
  std::cout << "  GstElementFactory* factory = 0;" << std::endl;
  std::cout << "  GstPluginFeature* feature = 0;" << std::endl << std::endl;

  std::cout << "  if (!type)" << std::endl; std::cout << "  {" << std::endl;
  std::cout << "    factory = gst_element_factory_find(\"" << pluginName << "\");" << std::endl;

  std::cout << "    // Make sure that the feature is actually loaded:" << std::endl;
  std::cout << "    if (factory)" << std::endl;
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
  std::cout << "}" << std::endl << std::endl;

  std::cout << enumGTypeFunctionDefinitions;

  std::cout << "namespace " << nmspace << std::endl;
  std::cout << "{" << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName << "()" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", NULL)" << std::endl;
  std::cout << "{" << std::endl;
  std::cout << "  //The floating reference is convenience for C," << std::endl;
  std::cout << " //but is useless and difficult for us:" << std::endl;
  std::cout << " gst_object_ref(gobj());" << std::endl;
  std::cout << " gst_object_sink(gobj());" << std::endl;
  std::cout << "}" << std::endl << std::endl;

  std::cout << cppTypeName << "::" << cppTypeName << "(const Glib::ustring& name)" << std::endl;
  std::cout << ": _CONSTRUCT(\"name\", name.c_str())" << std::endl;
  std::cout << "{" << std::endl;
  std::cout << "  //The floating reference is convenience for C," << std::endl;
  std::cout << " //but is useless and difficult for us:" << std::endl;
  std::cout << " gst_object_ref(gobj());" << std::endl;
  std::cout << " gst_object_sink(gobj());" << std::endl;
  std::cout << "}" << std::endl << std::endl;

  std::cout << std::endl << "}" << std::endl;
}

int main(int argc, char* argv[])
{
  gboolean hgFile = false;
  gboolean ccgFile = false;
  gboolean suggestHg = false;

  if (!g_thread_supported())
    g_thread_init(NULL);

  GOptionEntry optionEntries[] =
  {
    {"hg", 'h', 0, G_OPTION_ARG_NONE, &hgFile, "Generate preliminary .hg file.", NULL },
    {"ccg", 'c', 0, G_OPTION_ARG_NONE, &ccgFile, "Generate .ccg file.", NULL },
    {"suggest-hg", 's', 0, G_OPTION_ARG_NONE, &suggestHg, "If the plugin exists, output .hg filename.", NULL },
    {"namespace", 'n', 0, G_OPTION_ARG_STRING, &nmspace, "The namespace of the plugin.", "namespace" },
    {"main-defs", 'm', 0, G_OPTION_ARG_STRING, &defsFile, "The main defs file without .defs extension.", "def" },
    {"target", 't', 0, G_OPTION_ARG_STRING, &target, "The .h and .cc target directory.", "directory" },
    { NULL }
  };

  GOptionContext* gContext = g_option_context_new("<CppPluginClassName>");
  g_option_context_set_summary(gContext, "Outputs a GStreamer plugin's "
    "gmmproc files to be processed by gmmproc for\nwrapping in gstreamermm.  "
    "Use the same syntax for CppPluginClassName as in\ngst-inspect except "
    "that camel casing should be used because this will be the\nname of the "
    "C++ class.  The .hg file is a preliminary .hg file that needs to\nbe run "
    "through m4 including the ctocpp*.m4 files in the tools/m4 directory.");

  g_option_context_add_main_entries(gContext, optionEntries, NULL);
  g_option_context_add_group(gContext, gst_init_get_option_group());

  Glib::OptionContext optionContext(gContext, true);

  try
  {
    if (!optionContext.parse(argc, argv))
    {
      std::cout << "Error parsing options and initializing.  Sorry." <<
        std::endl;
      return -1;
    }
  }
  catch (Glib::OptionError& error)
  {
      std::cout << "Error parsing options and initializing GStreamer." <<
        std::endl << "Run `" << argv[0] << " -?'  for a list of options." <<
        std::endl;
      return -1;
  }

  if (argc != 2)
  {
    std::cout << "A plugin name must be supplied to generate an .hg file." <<
      std::endl << "Run `" << argv[0] << " -?'  for a list of options." <<
      std::endl;
    return -1;
  }

  cppTypeName = argv[1];
  pluginName = cppTypeName.lowercase();

  GstElementFactory* factory = 0;

  factory = gst_element_factory_find(pluginName.c_str());

  // Make sure that the feature is actually loaded:
  if (factory)
  {
    GstPluginFeature* loaded_feature =
            gst_plugin_feature_load(GST_PLUGIN_FEATURE(factory));

    g_object_unref(factory);
    factory = GST_ELEMENT_FACTORY(loaded_feature);
    type = gst_element_factory_get_element_type(factory);
  }

  if (type)
  {
    if (suggestHg)
    {
      std::cout << pluginName << ".hg" << std::endl;
      return 0;
    }

    if (!nmspace || !defsFile || !target)
    {
      std::cout << "A namespace, a default defs file and a target directory "
        "must be supplied" << std::endl << "with the --namespace, --main-defs "
        "and --target options (run with -? option for " << std::endl <<
        "details)." << std::endl;
      return -1;
    }

    cTypeName = g_type_name(type);
    cParentTypeName = g_type_name(g_type_parent(type));

    while (!cParentTypeName.empty() &&
      !is_wrapped_base_class(cParentTypeName) && !is_plugin(cParentTypeName))
    {
      cParentTypeName =
        g_type_name(g_type_parent(g_type_from_name(cParentTypeName.c_str())));
    }

    cppParentTypeName = cParentTypeName.substr(3);
    castMacro = get_cast_macro(cTypeName);

    if (cppParentTypeName.compare("BaseSrc") == 0 ||
      cppParentTypeName.compare("BaseSink") == 0 ||
      cppParentTypeName.compare("BaseTransform") == 0 ||
      cppParentTypeName.compare("PushSrc") == 0 ||
      cppParentTypeName.compare("Pipeline") == 0 ||
      cppParentTypeName.compare("Bin") == 0 ||
      cppParentTypeName.compare("Element") == 0)
    {
      parentInclude = "gstreamermm";
      parentNameSpace = "Gst";
    }
    else
    {
      parentInclude = target;
      parentNameSpace = nmspace;
    }

    if (hgFile || ccgFile)
    {
      Glib::ustring propertyWrapStatements;
      Glib::ustring includeMacroCalls;
      Glib::ustring enumWrapStatements;
      Glib::ustring signalWrapStatements;
      Glib::ustring enumGTypeFunctionDeclarations;
      Glib::ustring cClassSignalDeclarations;

      get_property_wrap_statements(propertyWrapStatements, includeMacroCalls,
        enumWrapStatements, enumGTypeFunctionDeclarations);

      get_signal_wrap_statements(signalWrapStatements, includeMacroCalls,
        cClassSignalDeclarations);

      if (hgFile)
      {
        Glib::ustring interfaceMacros;
        Glib::ustring cppExtends;

        get_interface_macros(interfaceMacros, includeMacroCalls,
          cppExtends);

        generate_hg_file(includeMacroCalls, enumWrapStatements, cppExtends,
          interfaceMacros, propertyWrapStatements, signalWrapStatements);
      }
      else
      {
        generate_ccg_file(enumGTypeFunctionDeclarations,
          cClassSignalDeclarations);
      }
    }
  }
  else
  {
    if (hgFile)
    {
      std::cout << "_DEFS(" << target << "," << defsFile << ")" <<
        std::endl << std::endl;

      std::cout << "// The build system does not have a plugin named " <<
        argv[1] << "." << std::endl;
      std::cout << "// A wrapper class for it was not generated." <<
        std::endl;
    }
  }

  if (factory)
    g_object_unref(factory);

  return 0;
}
