#include <gstmm.h>
#include <gst/gstbin.h>
#include <gst/gsterror.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  GstObject* cobject = GST_OBJECT (gst_bin_new("test"));
  GError* cerror = g_error_new_literal(GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "test error message");
  GstMessage* cmessage = gst_message_new_warning(cobject, cerror, "test debug text");
  
  Glib::RefPtr<Gst::Message> message = Gst::wrap(cmessage);

  std::cout << "C++ message instance is !NULL: " << (bool)(message) << std::endl;

  return 0;
}
