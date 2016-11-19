/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2009-2016 The gstreamermm Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <gstreamermm.h>
#include <glibmm/main.h>

#include <regex>
#include <iostream>

Glib::RefPtr<Glib::MainLoop> mainloop;

// Message watch function
bool bus_message_watch(const Glib::RefPtr<Gst::Bus>& /* bus */, const Glib::RefPtr<Gst::Message>& message)
{
  switch (message->get_message_type())
  {
  case Gst::MESSAGE_ERROR:
  case Gst::MESSAGE_EOS:
    mainloop->quit();
  default:
    break;
  }

  return true;
}

int main(int argc, char** argv)
{
  // Initialize Gstreamermm:
  Gst::init(argc, argv);

  //Check input arguments:
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  const std::string filename = argv[1];

  // Create pipeline:
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my-pipeline");

  // Create elements:
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("filesrc"),
    decoder = Gst::ElementFactory::create_element("decodebin"),
    tee = Gst::ElementFactory::create_element("tee"),
    audio_queue = Gst::ElementFactory::create_element("queue"),
    video_queue = Gst::ElementFactory::create_element("queue"),
    audio_convert = Gst::ElementFactory::create_element("audioconvert"),
    audio_convert_4v = Gst::ElementFactory::create_element("audioconvert"),
    video_convert = Gst::ElementFactory::create_element("videoconvert"),
    goom = Gst::ElementFactory::create_element("goom"),
    resample = Gst::ElementFactory::create_element("audioresample"),
    audio_sink = Gst::ElementFactory::create_element("autoaudiosink"),
    video_sink = Gst::ElementFactory::create_element("autovideosink");

  if (!source || !decoder || !tee || !audio_queue || !video_queue || !goom || !audio_convert_4v
      || !audio_convert || !video_convert || !resample || !audio_sink || !video_sink)
    std::cerr << "One of the elements could not be created." << std::endl;

  // Set location property of filesrc element
  source->set_property<Glib::ustring>("location", argv[1]);
  
  // We must add the elements to the pipeline before linking them:
  try
  {
    pipeline->add(source)->add(decoder)->add(tee)->add(audio_queue)->add(video_queue)
      ->add(goom)->add(audio_convert_4v)->add(audio_convert)->add(video_convert)
      ->add(resample)->add(audio_sink)->add(video_sink);
  }
  catch (std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }

  // Lik tee with queues
  Glib::RefPtr<Gst::PadTemplate> tee_src_tpl = tee->get_pad_template("src_%u");
  if (tee->request_pad(tee_src_tpl)->link(audio_queue->get_static_pad("sink")) != Gst::PAD_LINK_OK)
  {
    std::cerr << "Cannot link tee pad with audio queue" << std::endl;
    return 1;
  }
  if (tee->request_pad(tee_src_tpl)->link(video_queue->get_static_pad("sink")) != Gst::PAD_LINK_OK)
  {
    std::cerr << "Cannot link tee pad with video queue" << std::endl;
    return 1;
  }
  
  // Link other elements together:
  try
  {
    source->link(decoder);
    audio_queue->link(audio_convert)->link(resample)->link(audio_sink);
    video_queue->link(audio_convert_4v)->link(goom)->link(video_convert)->link(video_sink);
  }
  catch(const std::runtime_error& error)
  {
    std::cerr << "Exception while linking: " << error.what() << std::endl;
    return 1;
  }

  // Signal handler for on-pad-added signal of decoder element
  decoder->signal_pad_added().connect([tee] (const Glib::RefPtr<Gst::Pad> &pad) {
      Glib::RefPtr<Gst::Caps> caps = pad->get_current_caps();
      std::string media_type = caps->get_structure(0).get_name();

      std::cout << "New pad: " << pad->get_name() << ", media type: " << media_type << std::endl;

      if (std::regex_search(media_type, std::regex("^audio")))
      {
	if (pad->link(tee->get_static_pad("sink")) != Gst::PAD_LINK_OK)
	{
	  std::cerr << "Cannot link pad with queue" << std::endl;
	}
      }
      else
	std::cerr << "Unsupported media type" << std::endl;
    });

  // Add watch to pipeline's bus.
  pipeline->get_bus()->add_watch(sigc::ptr_fun(&bus_message_watch));

  
  // Now set the whole pipeline to playing and start the main loop:
  std::cout << "Setting pipeline to PLAYING." << std::endl;
  mainloop = Glib::MainLoop::create();
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Pipeline is playing." << std::endl;
  mainloop->run();
  
  std::cout << "Returned. Stopping pipeline." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}
