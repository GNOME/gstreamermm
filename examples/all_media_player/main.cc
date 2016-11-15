/*
 * main.cc
 *
 *  Created on: Sep 12, 2014
 *      Author: m.kolny
 */

#include <gstreamermm.h>
#include <iostream>
#include <glibmm/main.h>

using namespace Gst;
using Glib::RefPtr;


class AllMediaPlayer
{
private:
  RefPtr<Glib::MainLoop> main_loop;
  RefPtr<Pipeline> pipeline;

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  RefPtr<FileSrc> source;
#else
  RefPtr<Gst::Element> source;
#endif

  RefPtr<Element> decoder;

  bool on_bus_message(const RefPtr<Bus>&, const RefPtr<Message>& message);
  void on_decoder_pad_added(const RefPtr<Pad>& pad);

  void init()
  {
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
    source = FileSrc::create();
#else
    source = ElementFactory::create_element("filesrc");
#endif
    
    decoder = ElementFactory::create_element("decodebin");

    if (!decoder || !source)
    {
      throw std::runtime_error("One element could not be created.");
    }

    pipeline->add(source)->add(decoder);
    decoder->signal_pad_added().connect(sigc::mem_fun(*this, &AllMediaPlayer::on_decoder_pad_added));

    source->link(decoder);
  }

public:
  AllMediaPlayer()
  {
    main_loop = Glib::MainLoop::create();
    pipeline = Pipeline::create();
    pipeline->get_bus()->add_watch(sigc::mem_fun(*this, &AllMediaPlayer::on_bus_message));
  }

  void play_until_eos(const std::string& filename)
  {
    init();

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
    source->property_location() = filename;
#else
    source->set_property("location", filename);
#endif

    pipeline->set_state(STATE_PLAYING);
    main_loop->run();
    pipeline->set_state(STATE_NULL);
  }
};

bool AllMediaPlayer::on_bus_message(const RefPtr<Bus>&, const RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case Gst::MESSAGE_EOS:
    std::cout << std::endl << "End of stream" << std::endl;
    main_loop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
    std::cerr << "Error." << RefPtr<MessageError>::cast_static(message)->parse_debug() << std::endl;
    main_loop->quit();
    return false;
  default:
    break;
  }

  return true;
}

void AllMediaPlayer::on_decoder_pad_added(const RefPtr<Pad>& pad)
{
  Glib::ustring caps_format = pad->get_current_caps()->to_string().substr(0, 5);
  RefPtr<Bin> parent = parent.cast_dynamic(pad->get_parent()->get_parent());

  if (!parent)
  {
    std::cerr << "cannot get parent bin" << std::endl;
    return;
  }

  Glib::ustring factory_name;

  if (caps_format == "video")
  {
    factory_name = "autovideosink";
  }
  else if (caps_format == "audio")
  {
    factory_name = "autoaudiosink";
  }
  else
  {
    std::cerr << "unsupported media type: " << pad->get_current_caps()->to_string() << std::endl;
    return;
  }

  RefPtr<Element> element = ElementFactory::create_element(factory_name);

  if (!element)
  {
    std::cerr << "cannot create element " << factory_name << std::endl;
    return;
  }

  try
  {
    parent->add(element);
    element->set_state(STATE_PLAYING);
    pad->link(element->get_static_pad("sink"));
  }
  catch (const std::runtime_error& err)
  {
    std::cerr << "cannot add element to a bin: " << err.what() << std::endl;
  }
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <multimedia filename>" << std::endl;
    return 1;
  }

  init(argc, argv);
  AllMediaPlayer player;

  try
  {
    player.play_until_eos(argv[1]);
  }
  catch (const std::runtime_error& err)
  {
    std::cerr << "runtime error: " << err.what() << std::endl;
  }

  return 0;
}



