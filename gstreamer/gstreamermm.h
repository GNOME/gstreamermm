#ifndef _GSTREAMERMM_H_
#define _GSTREAMERMM_H_

#include <gstreamermm/init.h>
#include <gstreamermm/version.h>

// Core includes
#include <gstreamermm/bin.h>
#include <gstreamermm/buffer.h>
#include <gstreamermm/bus.h>
#include <gstreamermm/caps.h>
#include <gstreamermm/childproxy.h>
#include <gstreamermm/clock.h>
#include <gstreamermm/element.h>
#include <gstreamermm/elementfactory.h>
#include <gstreamermm/enums.h>
#include <gstreamermm/error.h>
#include <gstreamermm/event.h>
#include <gstreamermm/filter.h>
#include <gstreamermm/format.h>
#include <gstreamermm/ghostpad.h>
#include <gstreamermm/index.h>
#include <gstreamermm/indexfactory.h>
#include <gstreamermm/interface.h>
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
#include <gstreamermm/xml.h>

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
#include <gstreamermm/baseaudiosink.h>
#include <gstreamermm/baseaudiosrc.h>
#include <gstreamermm/cddabasesrc.h>
#include <gstreamermm/ringbuffer.h>
#include <gstreamermm/videosink.h>

// Base inteface includes
#include <gstreamermm/colorbalance.h>
#include <gstreamermm/colorbalancechannel.h>
#include <gstreamermm/mixer.h>
#include <gstreamermm/mixeroptions.h>
#include <gstreamermm/mixertrack.h>
#include <gstreamermm/navigation.h>
#include <gstreamermm/propertyprobe.h>
#include <gstreamermm/streamvolume.h>
#include <gstreamermm/tuner.h>
#include <gstreamermm/tunerchannel.h>
#include <gstreamermm/tunernorm.h>
#include <gstreamermm/videoorientation.h>
#include <gstreamermm/xoverlay.h>

// Plug-in core includes
#include <gstreamermm/capsfilter.h>
#include <gstreamermm/fakesrc.h>
#include <gstreamermm/fakesink.h>
#include <gstreamermm/fdsink.h>
#include <gstreamermm/fdsrc.h>
#include <gstreamermm/filesrc.h>
#include <gstreamermm/filesink.h>
#include <gstreamermm/identity.h>
#include <gstreamermm/multiqueue.h>
#include <gstreamermm/queue.h>
#include <gstreamermm/queue2.h>
#include <gstreamermm/tee.h>
#include <gstreamermm/typefindelement.h>

// Plug-in base includes
#include <gstreamermm/adder.h>
#include <gstreamermm/alsamixer.h>
#include <gstreamermm/alsasink.h>
#include <gstreamermm/alsasrc.h>
#include <gstreamermm/audioconvert.h>
#include <gstreamermm/audiorate.h>
#include <gstreamermm/audioresample.h>
#include <gstreamermm/audiotestsrc.h>
#include <gstreamermm/cdparanoiasrc.h>
#include <gstreamermm/clockoverlay.h>
#include <gstreamermm/decodebin.h>
#include <gstreamermm/decodebin2.h>
#include <gstreamermm/ffmpegcolorspace.h>
#include <gstreamermm/gdpdepay.h>
#include <gstreamermm/gdppay.h>
#include <gstreamermm/giosink.h>
#include <gstreamermm/giosrc.h>
#include <gstreamermm/giostreamsink.h>
#include <gstreamermm/giostreamsrc.h>
//TODO (Add plug-in first): #include <gstreamermm/gnomevfssink.h>
//TODO (Add plug-in first): #include <gstreamermm/gnomevfssrc.h>
#include <gstreamermm/multifdsink.h>
#include <gstreamermm/oggdemux.h>
#include <gstreamermm/oggmux.h>
#include <gstreamermm/playbin.h>
#include <gstreamermm/playbin2.h>
#include <gstreamermm/subtitleoverlay.h>
#include <gstreamermm/tcpclientsrc.h>
#include <gstreamermm/tcpclientsink.h>
#include <gstreamermm/tcpserversrc.h>
#include <gstreamermm/tcpserversink.h>
#include <gstreamermm/textoverlay.h>
#include <gstreamermm/textrender.h>
#include <gstreamermm/theoradec.h>
#include <gstreamermm/theoraenc.h>
#include <gstreamermm/theoraparse.h>
#include <gstreamermm/timeoverlay.h>
#include <gstreamermm/uridecodebin.h>
#include <gstreamermm/videorate.h>
#include <gstreamermm/videoscale.h>
#include <gstreamermm/videotestsrc.h>
#include <gstreamermm/volume.h>
#include <gstreamermm/vorbisdec.h>
#include <gstreamermm/vorbisenc.h>
#include <gstreamermm/vorbisparse.h>
#include <gstreamermm/vorbistag.h>
#include <gstreamermm/ximagesink.h>
#include <gstreamermm/xvimagesink.h>

#endif // _GSTREAMERMM_H
