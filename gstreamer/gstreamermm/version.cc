#include "version.h"
#include <gstreamermmconfig.h>

namespace Gst
{

void version(guint& major, guint& minor, guint& micro)
{
  major = GSTREAMERMM_MAJOR_VERSION;
  minor = GSTREAMERMM_MINOR_VERSION;
  micro = GSTREAMERMM_MICRO_VERSION;
}

}//end namespace Gst
