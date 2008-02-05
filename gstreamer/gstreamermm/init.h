// -*- c++ -*-
#ifndef _GSTREAMERMM_INIT_H
#define _GSTREAMERMM_INIT_H

#include "wrap_init.h"
#include <string.h>

namespace Gst
{

void init(int& argc, char**& argv);
bool init_check(int& argc, char**& argv, Glib::Error& error);
Glib::OptionGroup init_get_option_group();
  
}//end namespace Gst

#endif //_GSTREAMERMM_INIT_H

