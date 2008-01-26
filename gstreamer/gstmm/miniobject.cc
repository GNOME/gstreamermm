#include <gstmm/miniobject.h>
#include <gstmm/private/miniobject_p.h>

namespace Gst
{


void MiniObject_Class::class_init_function(void*, void*)
{}

MiniObject::MiniObject()
: gobject_(0)
{
}

MiniObject::MiniObject(GstMiniObject* castitem)
: gobject_(castitem)
{
}

MiniObject::~MiniObject()
{
  if(gobject_)
    gst_mini_object_unref(gobject_);
}

void 
MiniObject::reference() const
{
  gst_mini_object_ref(gobject_);
}

void
MiniObject::unreference() const
{
  gst_mini_object_unref(gobject_);
}

// TODO: Investigate how this works:
/*
Glib::RefPtr<Gst::MiniObject>
MiniObject::copy()
{
  GstMiniObject * copy = gst_mini_object_copy(gobject_);
  return Glib::wrap(copy, false);
}
*/

bool
MiniObject::is_writable() const
{
  return gst_mini_object_is_writable(gobject_);
}

void
MiniObject::make_writable()
{
  gst_mini_object_make_writable(gobject_);
}

} //namespace Gst

/*
namespace Glib
{

Glib::RefPtr<Gst::MiniObject> wrap(GstMiniObject* object, bool take_copy)
{
  return Glib::RefPtr<Gst::MiniObject>(new MiniObject(object, take_copy));
}

} //namespace Glib

*/
