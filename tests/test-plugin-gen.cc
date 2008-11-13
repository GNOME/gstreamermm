#include <gstreamermm.h>
#include <gstreamermm/fakesrc.h>
#include <iostream>

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::FakeSrc> fakesrc = Gst::FakeSrc::create();

  if (fakesrc)
    std::cout << "fakesrc is valid." << std::endl;
  else
    std::cout << "fakesrc is invalid." << std::endl;

  return 0;
}
