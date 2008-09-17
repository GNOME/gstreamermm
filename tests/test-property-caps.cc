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

  Glib::RefPtr<Gst::Caps> caps;

  source->get_property("caps", caps);

  if (!caps)
    std::cout << "`caps' property is null before setting property." <<
      std::endl;

  source->set_property("caps", Gst::Caps::create_from_string("image/jpeg,framerate=2/1"));

  source->get_property("caps", caps);

  if (caps)
    std::cout << "`caps' property after setting and getting is '" <<
      caps->to_string() << "'." << std::endl;

  return 0;
}
