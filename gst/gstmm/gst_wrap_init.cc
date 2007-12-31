
#include <glib.h>

// Disable the 'const' function attribute of the get_type() functions.
// GCC would optimize them out because we don't use the return value.
#undef  G_GNUC_CONST
#define G_GNUC_CONST /* empty */

#include <gstmm/gst_wrap_init.h>
#include <glibmm/error.h>
#include <glibmm/object.h>

// #include the widget headers so that we can call the get_type() static methods:

#include "enums.h"
#include "caps.h"
#include "clock.h"
#include "element.h"
#include "error.h"
#include "event.h"
#include "iterator.h"
#include "format.h"
#include "pad.h"
#include "padtemplate.h"
#include "query.h"
#include "structure.h"
#include "systemclock.h"
#include "xml.h"
#include "bin.h"
#include "pipeline.h"
#include "bus.h"
#include "message.h"

extern "C"
{

//Declarations of the *_get_type() functions:

GType gst_event_get_type(void);
GType gst_message_get_type(void);
GType gst_query_get_type(void);

//Declarations of the *_error_quark() functions:

} // extern "C"


//Declarations of the *_Class::wrap_new() methods, instead of including all the private headers:

namespace Gst {  class Event_Class { public: static Gst::MiniObject* wrap_new(GstMiniObject*); };  }
namespace Gst {  class Message_Class { public: static Gst::MiniObject* wrap_new(GstMiniObject*); };  }
namespace Gst {  class Query_Class { public: static Gst::MiniObject* wrap_new(GstMiniObject*); };  }

namespace Gst { 

void gst_wrap_init()
{

// Map gtypes to gstmm wrapper-creation functions:
  Gst::wrap_register(gst_event_get_type(), &Gst::Event_Class::wrap_new);
  Gst::wrap_register(gst_message_get_type(), &Gst::Message_Class::wrap_new);
  Gst::wrap_register(gst_query_get_type(), &Gst::Query_Class::wrap_new);

  // Register the gtkmm gtypes:
  Gst::Event::get_type();
  Gst::Message::get_type();
  Gst::Query::get_type();

} // gst_wrap_init()

} //Gst


