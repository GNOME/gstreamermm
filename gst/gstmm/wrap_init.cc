
#include <glib.h>

// Disable the 'const' function attribute of the get_type() functions.
// GCC would optimize them out because we don't use the return value.
#undef  G_GNUC_CONST
#define G_GNUC_CONST /* empty */

#include <gstmm/wrap_init.h>
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

GType gst_bin_get_type(void);
GType gst_bus_get_type(void);
GType gst_clock_get_type(void);
GType gst_element_get_type(void);
GType gst_pad_get_type(void);
GType gst_pad_template_get_type(void);
GType gst_pipeline_get_type(void);
GType gst_system_clock_get_type(void);
GType gst_xml_get_type(void);

//Declarations of the *_error_quark() functions:

GQuark gst_core_error_quark(void);
GQuark gst_library_error_quark(void);
GQuark gst_resource_error_quark(void);
GQuark gst_stream_error_quark(void);
} // extern "C"


//Declarations of the *_Class::wrap_new() methods, instead of including all the private headers:

namespace Gst {  class Bin_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class Bus_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class Clock_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class Element_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class Pad_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class PadTemplate_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class Pipeline_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class SystemClock_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }
namespace Gst {  class XML_Class { public: static Glib::ObjectBase* wrap_new(GObject*); };  }

namespace Gst { 

void wrap_init()
{
  // Register Error domains:
  Glib::Error::register_domain(gst_core_error_quark(), &Gst::CoreError::throw_func);
  Glib::Error::register_domain(gst_library_error_quark(), &Gst::LibraryError::throw_func);
  Glib::Error::register_domain(gst_resource_error_quark(), &Gst::ResourceError::throw_func);
  Glib::Error::register_domain(gst_stream_error_quark(), &Gst::StreamError::throw_func);

// Map gtypes to gtkmm wrapper-creation functions:
  Glib::wrap_register(gst_bin_get_type(), &Gst::Bin_Class::wrap_new);
  Glib::wrap_register(gst_bus_get_type(), &Gst::Bus_Class::wrap_new);
  Glib::wrap_register(gst_clock_get_type(), &Gst::Clock_Class::wrap_new);
  Glib::wrap_register(gst_element_get_type(), &Gst::Element_Class::wrap_new);
  Glib::wrap_register(gst_pad_get_type(), &Gst::Pad_Class::wrap_new);
  Glib::wrap_register(gst_pad_template_get_type(), &Gst::PadTemplate_Class::wrap_new);
  Glib::wrap_register(gst_pipeline_get_type(), &Gst::Pipeline_Class::wrap_new);
  Glib::wrap_register(gst_system_clock_get_type(), &Gst::SystemClock_Class::wrap_new);
  Glib::wrap_register(gst_xml_get_type(), &Gst::XML_Class::wrap_new);

  // Register the gtkmm gtypes:
  Gst::Bin::get_type();
  Gst::Bus::get_type();
  Gst::Clock::get_type();
  Gst::Element::get_type();
  Gst::Pad::get_type();
  Gst::PadTemplate::get_type();
  Gst::Pipeline::get_type();
  Gst::SystemClock::get_type();
  Gst::XML::get_type();

} // wrap_init()

} //Gst


