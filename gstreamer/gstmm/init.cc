#include <gstmm/init.h>
#include <gstmm/wrap.h>
#include <gstmm/gst_wrap_init.h>
#include <gst/gst.h>

namespace Gst
{

void init(int& argc, char**& argv)
{
  static bool s_init = false;
  if(!s_init)
  {
    Glib::init();
    gst_init(&argc, &argv);

    //For Glib::wrap(), for Glib::Object-derived classes.
    Gst::wrap_init(); 

    //For Gst::wrap(), for Gst::MiniObject-derived classes.
    Gst::wrap_register_init();
    Gst::gst_wrap_init();

    s_init = true;
  }
}

bool init_check(int& argc, char**& argv, Glib::Error& error)
{
  static bool s_init = false;
  if(!s_init)
  {
    Glib::init();
    GError* c_error;
    gst_init_check(&argc, &argv, &c_error);
    error = Glib::Error(c_error);
    Gst::wrap_init();
    s_init = true;
  }
}

Glib::OptionGroup init_get_option_group()
{
  return Glib::OptionGroup(gst_init_get_option_group());
}

}
