#include <gstreamermm.h>
#include <gstreamermm/fakesrc.h>
#include <iostream>

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> element =
          Gst::ElementFactory::create_element("fakesrc");

  Glib::RefPtr<Gst::FakeSrc> fakesrc = Glib::RefPtr<Gst::FakeSrc>::cast_dynamic(element);

  if (!fakesrc)
    std::cout << "fakesrc is invalid." << std::endl;

  return 0;
}
