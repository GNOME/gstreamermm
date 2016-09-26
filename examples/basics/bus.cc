/*
 * This example presents basic usage of the Gst::Bus class.
 */
#include <gstreamermm.h>
#include <glibmm/main.h>

#include <iostream>

Glib::RefPtr<Glib::MainLoop> main_loop;

// Message watch function
bool bus_message_watch(const Glib::RefPtr<Gst::Bus>& /* bus */, const Glib::RefPtr<Gst::Message>& message)
{
  // Print type of the message posted on the bus, and the source object name.
  std::cout << "Got message of type " << Gst::Enums::get_name(message->get_message_type()) << std::endl;

  if (message->get_source())
  {
    std::cout << "Source object: " << message->get_source()->get_name() << std::endl;
  }

  switch (message->get_message_type())
  {
  // Handle ERROR message - print error and debug information
  case Gst::MESSAGE_ERROR:
  {
    auto error_msg = Glib::RefPtr<Gst::MessageError>::cast_static(message);
    std::cout << "Error: " << error_msg->parse_error().what() << std::endl;
    std::cout << "Debug: " << error_msg->parse_debug() << std::endl;
    break;
  }
  // Handle EOS message - quit the loop
  case Gst::MESSAGE_EOS:
    main_loop->quit();
    break;
  // Handle state changed message - print details
  case Gst::MESSAGE_STATE_CHANGED:
  {
    auto state_changed_msg = Glib::RefPtr<Gst::MessageStateChanged>::cast_static(message);
    std::cout << "Old state: " << Gst::Enums::get_name(state_changed_msg->parse_old_state()) << std::endl;
    std::cout << "New state: " << Gst::Enums::get_name(state_changed_msg->parse_new_state()) << std::endl;
    break;
  }
  // Unhanlded messages
  default:
    break;
  }

  return true;
}

int main(int argc, char *argv[])
{
  Gst::init(argc, argv);

  // Create some elements
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("videotestsrc", "source");
  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("autovideosink", "sink");

  // Create pipeline
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my-pipeline");

  // Add elements to a pipeline
  try
  {
    pipeline->add(source)->add(sink);
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }

  // Link elements
  try
  {
    source->link(sink);
  }
  catch (const std::runtime_error& ex)
  {
    std::cerr << "Exception while linking: " << ex.what() << std::endl;
  }

  // Get a bus object of the pipeline
  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();

  // Add watch to the bus
  bus->add_watch(sigc::ptr_fun(bus_message_watch));

  // Start pipeline
  pipeline->set_state(Gst::STATE_PLAYING);

  main_loop = Glib::MainLoop::create();
  main_loop->run();

  // Stop playing the pipeline
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

