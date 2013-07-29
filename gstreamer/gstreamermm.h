#ifndef _GSTREAMERMM_H_
#define _GSTREAMERMM_H_

/** @mainpage gstreamermm Reference Manual
 *
 * @section Description Description
 *
 * gstreamermm provides C++ bindings for the <a
 * href="http://gstreamer.freedesktop.org">GStreamer streaming multimedia
 * library</a>.  With gstreamermm it is possible to develop applications that
 * work with multimedia in C++.  For instance, see Gst::Element, Gst::Bin and
 * Gst::Pipeline.
 *
 * @section Features Features
 *
 * - gstreamermm is developed over <a
 * href="http://www.gtkmm.org/index.shtml">glibmm</a>, <a
 * href="http://libsigc.sourceforge.net/">libsigc++</a> and <a
 * href="http://libxmlplusplus.sourceforge.net/">libxml++</a> and the
 * functionalities they provide.
 * - Referencing and unreferencing of GObjects is handled automatically via
 *  glibmm's automatic pointer class, Glib::RefPtr.
 * - libsigc++'s slots are used for callbacks and signals.
 * - Most of the GStreamer core and base plug-ins are wrapped.
 *
 * @section Basics Basic Usage
 *
 * Some form of the Gst::init() method must be called before using the
 * library's classes, functions, etc.  To get a deeper understanding of how to
 * set up pipelines, deal with elements, pads, etc., see the <a
 * href="http://gstreamer.freedesktop.org/data/doc/gstreamer/head/manual/html/index.html">GStreamer
 * Application Development Manual</a>.
 *
 * The following includes the gstreamermm header:
 * @code
 * #include <gstreamermm.h>
 * @endcode
 * (You may include individual headers, such as @c gstreamermm/pipeline.h
 * instead.)
 *
 * @section Compiling Compiling
 *
 * If your source file is @c program.cc, you can compile it with:
 * @code
 * g++ program.cc -o program  `pkg-config --cflags --libs gstreamermm-0.10`
 * @endcode
 *
 * Alternatively, if using autoconf, use the following in @c configure.ac:
 * @code
 * PKG_CHECK_MODULES([GSTREAMERMM], [gstreamermm-0.10])
 * @endcode
 * Then use the generated @c GSTREAMERMM_CFLAGS and @c GSTREAMERMM_LIBS
 * variables in the
 * project @c Makefile.am files. For example:
 * @code
 * program_CPPFLAGS = $(GSTREAMERMM_CFLAGS)
 * program_LDADD = $(GSTREAMERMM_LIBS)
 * @endcode
 */

#include <gstreamermm/init.h>
#include <gstreamermm/version.h>

// Core includes
#include <gstreamermm/bin.h>
#include <gstreamermm/buffer.h>
#include <gstreamermm/bufferlist.h>
#include <gstreamermm/bus.h>
#include <gstreamermm/caps.h>
#include <gstreamermm/childproxy.h>
#include <gstreamermm/clock.h>
#include <gstreamermm/element.h>
#include <gstreamermm/elementfactory.h>
#include <gstreamermm/enums.h>
#include <gstreamermm/error.h>
#include <gstreamermm/event.h>
#include <gstreamermm/format.h>
#include <gstreamermm/ghostpad.h>
#include <gstreamermm/iterator.h>
#include <gstreamermm/message.h>
#include <gstreamermm/object.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/padtemplate.h>
#include <gstreamermm/parse.h>
#include <gstreamermm/pipeline.h>
#include <gstreamermm/plugin.h>
#include <gstreamermm/pluginfeature.h>
#include <gstreamermm/preset.h>
#include <gstreamermm/query.h>
#include <gstreamermm/registry.h>
#include <gstreamermm/segment.h>
#include <gstreamermm/structure.h>
#include <gstreamermm/systemclock.h>
#include <gstreamermm/taglist.h>
#include <gstreamermm/tagsetter.h>
#include <gstreamermm/task.h>
#include <gstreamermm/taskpool.h>
#include <gstreamermm/typefind.h>
#include <gstreamermm/typefindfactory.h>
#include <gstreamermm/urihandler.h>
#include <gstreamermm/value.h>

// Core library base includes
#include <gstreamermm/basesink.h>
#include <gstreamermm/basesrc.h>
#include <gstreamermm/basetransform.h>
#include <gstreamermm/pushsrc.h>

// Base library includes
#include <gstreamermm/audioclock.h>
#include <gstreamermm/audiofilter.h>
#include <gstreamermm/audiosink.h>
#include <gstreamermm/audiosrc.h>
#include <gstreamermm/audiobasesink.h>
#include <gstreamermm/audiobasesrc.h>
#include <gstreamermm/discoverer.h>
#include <gstreamermm/discovererinfo.h>
#include <gstreamermm/audioringbuffer.h>
#include <gstreamermm/videosink.h>

// Base inteface includes
#include <gstreamermm/navigation.h>
#include <gstreamermm/videoorientation.h>

// Plug-in core includes
#include <gstreamermm/capsfilter.h>
#include <gstreamermm/fakesrc.h>
#include <gstreamermm/fakesink.h>
#include <gstreamermm/fdsink.h>
#include <gstreamermm/fdsrc.h>
#include <gstreamermm/filesrc.h>
#include <gstreamermm/filesink.h>
#include <gstreamermm/funnel.h>
#include <gstreamermm/identity.h>
#include <gstreamermm/multiqueue.h>
#include <gstreamermm/queue.h>
#include <gstreamermm/queue2.h>

// Plug-in base includes
#include <gstreamermm/adder.h>
#include <gstreamermm/alsasink.h>
#include <gstreamermm/alsasrc.h>
#include <gstreamermm/audioconvert.h>
#include <gstreamermm/audiorate.h>
#include <gstreamermm/audioresample.h>
#include <gstreamermm/audiotestsrc.h>
#include <gstreamermm/cdparanoiasrc.h>
#include <gstreamermm/clockoverlay.h>
#include <gstreamermm/decodebin.h>
#include <gstreamermm/giosink.h>
#include <gstreamermm/giosrc.h>
#include <gstreamermm/giostreamsink.h>
#include <gstreamermm/giostreamsrc.h>
//TODO? (Add plug-in first): #include <gstreamermm/gnomevfssink.h>
//TODO? (Add plug-in first): #include <gstreamermm/gnomevfssrc.h>
#include <gstreamermm/oggdemux.h>
#include <gstreamermm/oggmux.h>
#include <gstreamermm/subtitleoverlay.h>


#endif // _GSTREAMERMM_H
