/*
 * generate_plugin_module_defs_gst.cc
 *
 *  Created on: Jul 30, 2015
 *      Author: mkolny
 */

#include <glibmm_generate_extra_defs/generate_extra_defs.h>

#include <gst/gst.h>

#include <iostream>

static std::string
get_element_factory_defs(GstElementFactory *factory)
{
  GType type = 0;
  std::string result;

  GstPluginFeature* loaded_feature = gst_plugin_feature_load(GST_PLUGIN_FEATURE(factory));
  factory = GST_ELEMENT_FACTORY(loaded_feature);
  type = gst_element_factory_get_element_type(factory);
  result = get_defs(type, gtype_is_a_pointer);
  g_object_unref(factory);
  return result;
}


static gboolean
feature_filter (GstPluginFeature *feature, gpointer user_data)
{
  GstPlugin *plugin = gst_plugin_feature_get_plugin (feature);
  gchar *expected_source = reinterpret_cast<char*>(user_data);

  if (plugin == NULL) {
     return FALSE;
  }

  return g_strcmp0 (expected_source, gst_plugin_get_source (plugin)) == 0;
}

int main (int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <source module>" << std::endl;
    return -1;
  }

  gst_init (&argc, &argv);

  GstRegistry *registry = gst_registry_get ();

  GList *features_list = gst_registry_feature_filter (registry, feature_filter, FALSE, argv[1]);
  GList *l = features_list;
  while (l) {
    GstPluginFeature *feature = reinterpret_cast<GstPluginFeature*>(l->data);

    if (GST_IS_ELEMENT_FACTORY (feature)) {
      std::cout << get_element_factory_defs (GST_ELEMENT_FACTORY_CAST (feature)) << std::endl;
    }
    l = l->next;
  }

  gst_plugin_feature_list_free (features_list);



}
