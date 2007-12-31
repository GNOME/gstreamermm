#include <gstmm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Element> source, filter, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");

  source = Gst::Element::create("fakesrc", "source");
  filter = Gst::Element::create("identity", "filter");
  sink = Gst::Element::create("fakesink", "sink");

  pipeline->add(source)->add(filter)->add(sink);
  source->link(filter)->link(sink);

  std::cout << "Successfully linked elements '" << source->get_name() <<
    "', '" << filter->get_name() << "' and '" << sink->get_name() <<
      "'." << std::endl;
}
