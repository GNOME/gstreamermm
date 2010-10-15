#include <gstreamermm.h>

int main(int, char**)
{
  Glib::RefPtr<Gst::BufferList> list = Gst::BufferList::create();
  Gst::BufferListIterator test;
  list->iterate(test);
}
