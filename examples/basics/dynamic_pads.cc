/*
 * This example presents basic usage of dynamics Gst::Pad objects.
 */
#include <gstreamermm.h>
#include <glibmm/main.h>

#include <iostream>

int main(int argc, char *argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Glib::MainLoop> main_loop = Glib::MainLoop::create();

  // Create pipeline
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my_pipeline");

  // Create elements
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("videotestsrc", "source"),
      decodebin = Gst::ElementFactory::create_element("decodebin", "decoder"),
      sink = Gst::ElementFactory::create_element("autovideosink", "videosink");

  // Add elements to a pipeline
  try
  {
    pipeline->add(source)->add(decodebin)->add(sink);
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }

  // Link elements
  try
  {
    // We can't link decodebin with sink, because decodebin
    // doesn't have any src pad on start up.
    source->link(decodebin);
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << "Exception while linking: " << ex.what() << std::endl;
  }

  // Handle messages posted on bus
  pipeline->get_bus()->add_watch([main_loop] (const Glib::RefPtr<Gst::Bus>&,
                                     const Glib::RefPtr<Gst::Message>& message) {
    switch (message->get_message_type())
    {
    case Gst::MESSAGE_EOS:
    case Gst::MESSAGE_ERROR:
      main_loop->quit();
      break;
    default:
      break;
    }
  return true;
  });

  // Listen for newly created pads
  decodebin->signal_pad_added().connect([decodebin, sink] (const Glib::RefPtr<Gst::Pad>& pad) {
    std::cout << "New pad added to " << decodebin->get_name() << std::endl;
    std::cout << "Pad name: " << pad->get_name() << std::endl;

    Gst::PadLinkReturn ret = pad->link(sink->get_static_pad("sink"));

    if (ret != Gst::PAD_LINK_OK)
    {
      std::cout << "Cannot link pads. Error: " << ret << std::endl;
    }
    else
    {
      std::cout << "Pads linked correctly!" << std::endl;
    }
  });

  // Start the pipeline
  pipeline->set_state(Gst::STATE_PLAYING);
  main_loop->run();
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}
