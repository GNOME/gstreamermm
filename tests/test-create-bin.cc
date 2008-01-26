#include <gstreamermm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Bin> bin;
  Glib::RefPtr<Gst::Element> source, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");
  bin = Gst::Bin::create("my-bin");

  source = Gst::Element::create("fakesrc", "source");
  sink = Gst::Element::create("fakesink", "sink");

  bin->add(source)->add(sink);

  pipeline->add(bin);
  source->link(sink);

  std::cout << "Successfully added elements '" << source->get_name() <<
    "' and '" << sink->get_name() << "' to bin '" <<
      bin->get_name() << "'." << std::endl;
}
