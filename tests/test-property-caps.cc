#include <gstreamermm.h>
#include <iostream>

int
main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> source = 
          Gst::ElementFactory::create_element("multifilesrc", "source");

  if (!source)
  {
    std::cout << "Could not create `multifilesrc' element.  Exiting." <<
      std::endl;

    return -1;
  }

  Glib::RefPtr<Gst::Caps> caps =
          Gst::Caps::create_from_string("image/jpeg,framerate=2/1");
 
  // Verify that setting "caps" property compiles:
  source->set_property("caps", caps);

  return 0;
}
