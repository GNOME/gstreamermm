#include <gstreamermm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw-yuv");
 
  //caps->set_simple("width", Glib::Value<int>(384));
  //caps->set_simple("height", Glib::Value<int>(288));

  Glib::Value<int> width, height;
  width.init(G_TYPE_INT);
  width.set(384);

  height.init(G_TYPE_INT);
  height.set(288);

  caps->set_simple("width", width);
  caps->set_simple("height", height);

  return 0;
}
