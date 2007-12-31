#include <gstmm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my-pipeline");
  Glib::RefPtr<Gst::Element> source = Gst::Element::create("fakesrc", "source");

  pipeline->add(source);

  Glib::RefPtr<Gst::Element> sourceCopy = pipeline->get_by_name("source");

  if (sourceCopy)
    std::cout << "Successfully added element '" << sourceCopy->get_name() <<
     "' to pipeline '" << pipeline->get_name() << "'." << std::endl;
}
