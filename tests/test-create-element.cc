#include <gstmm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> element = Gst::Element::create("fakesrc", "source");

  if(element)
    std::cout << "Successfully created gst element '" <<
      element->get_name() << "'." << std::endl;
}
