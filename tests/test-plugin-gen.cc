#include <gstreamermm.h>
#include <gstreamermm/filesrc.h>
#include <iostream>

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> element =
          Gst::ElementFactory::create_element("filesrc");

  Glib::RefPtr<Gst::FileSrc> filesrc = Gst::FileSrc::create();

  if (filesrc)
    std::cout << "filesrc is valid." << std::endl;
  else
    std::cout << "filesrc is invalid." << std::endl;

  gulong mmapsize = 0;
  GstFileSrc* obj = filesrc->gobj();
  g_object_get(obj, "mmapsize", &mmapsize, NULL);

  std::cout << "mmapsize = "  << mmapsize << std::endl;

  return 0;
}
