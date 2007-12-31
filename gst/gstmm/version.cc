#include "version.h"
#include <gstmmconfig.h>

namespace Gst
{

void version(guint& major, guint& minor, guint& micro)
{
  major = GSTMM_MAJOR_VERSION;
  minor = GSTMM_MINOR_VERSION;
  micro = GSTMM_MICRO_VERSION;
}

}//end namespace Gst
