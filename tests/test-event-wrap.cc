#include <gstmm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  GstEvent* cevent = gst_event_new_latency(GST_SECOND);
  
  Glib::RefPtr<Gst::Event> event = Gst::Event::wrap(cevent);

  std::cout << "C++ event instance is !NULL: " << (bool)(event) << std::endl;

  Glib::RefPtr<Gst::EventLatency> event_latency = Glib::RefPtr<Gst::EventLatency>::cast_dynamic(event);
  std::cout << "event is a Gst::EventLatency: " << (bool)event_latency  << std::endl;
  std::cout << "event type name: '" << Gst::get_name(event->get_event_type()) << "'" << std::endl;

  return 0;
}
