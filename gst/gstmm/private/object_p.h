#ifndef _GSTMM_OBJECT_P_H
#define _GSTMM_OBJECT_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Gst
{

class Object_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Object CppObjectType;
  typedef GstObject BaseObjectType;
  typedef GstObjectClass BaseClassType;
  typedef Glib::Object_Class CppClassParent;
  typedef GObjectClass BaseClassParent;

  friend class Object;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();

  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);
};


} // namespace Gst


#endif /* _GSTMM_OBJECT_P_H */

