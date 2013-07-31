#include <gstreamermm.h>

int main(int argc, char** argv)
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::BufferList> list = Gst::BufferList::create();
  Gst::BufferListIterator test;
  list->iterate(test);
}
