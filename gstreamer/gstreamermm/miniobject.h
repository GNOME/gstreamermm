#ifndef _GSTMM_MINIOBJECT_H
#define _GSTMM_MINIOBJECT_H

#include <glibmm/objectbase.h>
#include <gst/gstminiobject.h>

namespace Gst
{

class MiniObject_Class;

/** This is a base class for some gstreamermm objects.
 * It is similar to Glib::Object but has no GObject property or signal support.
 * Use Gst::wrap() (instead of Glib::wrap()) to create C++ instances that wrap C instances.
 */
class MiniObject : public Glib::ObjectBase
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef MiniObject       CppObjectType;
  typedef MiniObject_Class CppClassType;
  typedef GstMiniObject      BaseObjectType;
  typedef GstMiniObjectClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

//protected:
public:
  //friend Glib::wrap;

  MiniObject();
  MiniObject(GstMiniObject* castitem);

public:
  virtual ~MiniObject();
  
  //Note that we don't add a constructor for gst_mini_object_new()
  //because it's just an equivalent for g_object_new(), 
  //which is just an equivalent for C++'s new(). 


//private:
  // noncopyable
  MiniObject(const MiniObject&);
  MiniObject& operator=(const MiniObject&);

public:
  //Glib::RefPtr<Gst::MiniObject> copy();

  bool is_writable() const;
  void make_writable();

  void reference() const;
  void unreference() const;

  // static void replace(Glib::RefPtr<Gst::MiniObject> & olddata, Glib::RefPtr<Gst::MiniObject> & newdata);

protected:
  GstMiniObject* gobject_;
};

} // namespace Gst

/*
namespace Glib
{
  inline Glib::RefPtr<Gst::MiniObject> wrap(GstMiniObject *object, bool take_copy)
  {
    return Glib::RefPtr<Gst::MiniObject>(new MiniObject(object, take_copy));
  }

} //namespace Glib
*/

#endif //#ifndef _GSTMM_MINIOBJECT_H

