/* $Id: generate_extra_defs.cc 740 2008-10-15 15:58:17Z jaalburqu $ */

/* generate_extra_defs.cc
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


#include "glibmm_generate_extra_defs/generate_extra_defs.h"

#include <gst/gst.h>
#include <glibmm.h>

int main(int argc, char* argv[])
{
  gchar* nmspace;
  gchar* defsFile;
  gchar* target;

  if (!g_thread_supported())
    g_thread_init(NULL);

  GOptionEntry optionEntries[] =
  {
    {"namespace", 'n', 0, G_OPTION_ARG_STRING, &nmspace, "The namespace of the plugin", "namespace" },
    {"main-defs", 'm', 0, G_OPTION_ARG_STRING, &defsFile, "The main .defs file (used in _DEFS() directive)", "def" },
    {"target", 't', 0, G_OPTION_ARG_STRING, &target, "The target directory  of the generated .h file (used in _DEFS() directive)", "directory" },
    { NULL }
  };

  GOptionContext* gContext = g_option_context_new("<plugin name>");
  g_option_context_set_summary(gContext, "Outputs a GStreamer plugin's .hg file to be processed by gmmproc for wrapping it in gstreamermm.  Use the same syntax for the plugin name as in gst-inspect.");

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

  std::cout << "Namespace = " << nmspace << "." << std::endl;
  std::cout << "Main defs file = " << defsFile << "." << std::endl;
  std::cout << "Target directory = " << target << "." << std::endl;

  GType type = 0;
  GstElementFactory* factory = 0;

  factory = gst_element_factory_find(argv[1]);

  // Make sure that the feature is actually loaded:
  if (factory)
  {
    GstPluginFeature* loaded_feature =
            gst_plugin_feature_load(GST_PLUGIN_FEATURE(factory));

    g_object_unref(factory);
    factory = GST_ELEMENT_FACTORY(loaded_feature);
    type = gst_element_factory_get_element_type(factory);

    Glib::ustring typeName = g_type_name(type);
    Glib::ustring parentTypeName = g_type_name(g_type_parent(type));

    std::cout << "Type name: " << typeName << "." << std::endl;
    std::cout << "Parent type name: " << parentTypeName << "." << std::endl;

    g_object_unref(factory);
  }

  return 0;
}