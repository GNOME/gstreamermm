#include "gst_type_is_a_pointer.h"
#include <gst/gst.h>

bool gst_type_is_a_pointer(GType gtype)
{
  return (g_type_is_a(gtype, G_TYPE_OBJECT) ||
    g_type_is_a(gtype, G_TYPE_BOXED) ||
    g_type_is_a(gtype, GST_TYPE_MINI_OBJECT));
}
