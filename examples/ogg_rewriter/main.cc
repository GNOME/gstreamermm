#include <gstreamermm.h>
#include <glibmm/main.h>
#include <iostream>
#include <stdlib.h>

Glib::RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */,
  const Glib::RefPtr<Gst::Message>& message)
{
  switch(message->get_message_type()) {
    case Gst::MESSAGE_EOS:
      std::cout << std::endl << "End of stream" << std::endl;
      mainloop->quit();
      return false;
    case Gst::MESSAGE_ERROR:
    {
        std::cerr << "Error." << std::endl;
        mainloop->quit();
        return false;
    }
    default:
      break;
  }

  return true;
}

int main(int argc, char** argv)
{
  Gst::init(argc, argv);
  Glib::RefPtr<Gst::Pipeline> pipeline;

  if(argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " <input ogg file> <output ogg file>" << std::endl;
    return EXIT_FAILURE;
  }

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::FileSrc> filesrc = Gst::FileSrc::create();
  Glib::RefPtr<Gst::FileSink> filesink = Gst::FileSink::create();
#else
  Glib::RefPtr<Gst::Element> filesrc = Gst::ElementFactory::create_element("filesrc");
  Glib::RefPtr<Gst::Element> filesink = Gst::ElementFactory::create_element("filesink");
#endif

  if(!filesrc || !filesink)
  {
    std::cerr << "The FileSrc or FileSink element could not be created." << std::endl;
    return EXIT_FAILURE;
  }

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  filesrc->property_location() = argv[1];
  filesink->property_location() = argv[2];
#else
  filesrc->set_property<Glib::ustring>("location", argv[1]);
  filesink->set_property<Glib::ustring>("location", argv[2]);
#endif
  
  mainloop = Glib::MainLoop::create();
  pipeline = Gst::Pipeline::create("rewriter");

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  pipeline->add(filesrc)->add(filesink);

  std::cout << "Setting to PLAYING." << std::endl;
  pipeline->set_state(Gst::STATE_PLAYING);
  filesrc->link(filesink);
  std::cout << "Running." << std::endl;
  mainloop->run();

  std::cout << "Returned. Setting state to NULL." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return EXIT_SUCCESS;
}
