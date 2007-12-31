#ifndef _GSTMM_MINIOBJECT_P_H
#define _GSTMM_MINIOBJECT_P_H

#include <glibmm/class.h>

namespace Gst
{

class MiniObject_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef MiniObject       CppObjectType;
  typedef GstMiniObject      BaseObjectType;
  typedef GstMiniObjectClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();

  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);
};


} // namespace Gst


#endif /* _GSTMM_MINIOBJECT_P_H */

