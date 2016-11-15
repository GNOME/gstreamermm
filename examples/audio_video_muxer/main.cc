/*
 * main.cc
 *
 *  Created on: Aug 14, 2013
 *      Author: m.kolny
 */

#include <gstreamermm.h>
#include <iostream>
#include <glibmm/main.h>

using namespace Gst;
using Glib::RefPtr;

RefPtr<Element> video_parser, audio_parser;
RefPtr<Glib::MainLoop> main_loop;

bool on_bus_message(const RefPtr<Gst::Bus>&, const RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case Gst::MESSAGE_EOS:
    std::cout << std::endl << "End of stream" << std::endl;
    main_loop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
  {
    Glib::Error error;
    std::string debug_message;
    RefPtr<MessageError>::cast_static(message)->parse(error, debug_message);
    std::cerr << "Error: " << error.what() << std::endl << debug_message << std::endl;
    main_loop->quit();
    return false;
  }
  default:
    break;
  }

  return true;
}

void on_demux_pad_added(const RefPtr<Pad>& newPad)
{
  std::cout << "Dynamic pad created. Linking demuxer/decoder." << std::endl;
  RefPtr<Pad> sinkPad = video_parser->get_static_pad("sink");
  PadLinkReturn ret = newPad->link(sinkPad);

  if (ret != PAD_LINK_OK && ret != PAD_LINK_WAS_LINKED)
  {
    std::cerr << "Linking of pads " << newPad->get_name() << " and " <<
      sinkPad->get_name() << " failed." << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " <Ogg/Vorbis filename>"
        " <mp3 filename> <mkv output filename>" << std::endl;
    return 1;
  }

  init(argc, argv);

  RefPtr<Pipeline> pipeline = Pipeline::create("play-pipeline");
  main_loop = Glib::MainLoop::create();
  RefPtr<Bus> bus = pipeline->get_bus();
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  RefPtr<FileSrc> video_source = FileSrc::create(),
    audio_source = FileSrc::create();
    RefPtr<FileSink> filesink = FileSink::create();
#else
    RefPtr<Element> video_source = ElementFactory::create_element("filesrc"),
      audio_source = ElementFactory::create_element("filesrc"),
      filesink = ElementFactory::create_element("filesink");
#endif

  RefPtr<Element> ogg_demuxer = ElementFactory::create_element("oggdemux");
  audio_parser = ElementFactory::create_element("mad");

  RefPtr<Element> audiosink = ElementFactory::create_element("autoaudiosink"),
    videosink = ElementFactory::create_element("autovideosink");

  RefPtr<Element> muxer = ElementFactory::create_element("matroskamux");


  video_parser = ElementFactory::create_element("theoraparse");

  if (!video_source || !ogg_demuxer || !video_parser || !videosink || !pipeline || !audio_parser || !audio_source)
  {
    std::cout << "One element could not be created." << std::endl;
    return 1;
  }

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  video_source->property_location() = argv[1];
  audio_source->property_location() = argv[2];
  filesink->property_location() = argv[3];
#else
  video_source->set_property<Glib::ustring>("location", argv[1]);
  audio_source->set_property<Glib::ustring>("location", argv[2]);
  filesink->set_property<Glib::ustring>("location", argv[3]);
#endif
  
  pipeline->add(video_source)->
            add(ogg_demuxer)->
            add(video_parser)->
            add(audio_source)->
            add(audio_parser)->
            add(muxer)->
            add(filesink);

  ogg_demuxer->signal_pad_added().connect(sigc::ptr_fun(&on_demux_pad_added));

  video_source->link(ogg_demuxer);
  video_parser->link(muxer);
  audio_source->link(audio_parser)->link(muxer);
  muxer->link(filesink);

  pipeline->set_state(STATE_PLAYING);

  main_loop->run();

  pipeline->set_state(STATE_NULL);

  return 0;
}
