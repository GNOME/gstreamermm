#include <gstreamermm.h>
#include <gstreamermm/filesrc.h>
#include <gstreamermm/fakesink.h>
#include <iostream>

void on_handoff(const Glib::RefPtr<Gst::Buffer>& buffer,
                const Glib::RefPtr<Gst::Pad>& pad)
{
  std::cout << "Gst::FakeSink's handoff signal triggered." << std::endl <<
    "Exiting abruptly to stop execution." << std::endl;

  exit(0);
}

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return -1;
  }

  Glib::RefPtr<Glib::MainLoop>  mainloop = Glib::MainLoop::create();

  // Create elements:
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("audio-player");
  Glib::RefPtr<Gst::FileSrc> source = Gst::FileSrc::create();
  Glib::RefPtr<Gst::FakeSink> sink = Gst::FakeSink::create();

  if (!pipeline || !source || !sink) {
    std::cerr << "One element could not be created" << std::endl;
    return -1;
  }

  // Set filename property on the file source.
  source->property_location() = argv[1];

  // Put all elements in a bin:
  try
  {
    pipeline->add(source)->add(sink);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " <<
      ex.what() << std::endl;

    return -1;
  }

  // Link together:
  source->link(sink);

  // Enable the handoff signal emition and connect slot:
  sink->property_signal_handoffs() = true;
  sink->signal_handoff().connect(sigc::ptr_fun(on_handoff));

  // Now set to playing and iterate:
  std::cout << "Setting to PLAYING." << std::endl;
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Running." << std::endl;
  mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Stopping playback." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}
