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

  int sizemax = 0;
  GstFakeSrc* obj = fakesrc->gobj();
  g_object_get(obj, "sizemax", &sizemax, NULL);

  std::cout << "sizemax = "  << sizemax << std::endl;

  return 0;
}
