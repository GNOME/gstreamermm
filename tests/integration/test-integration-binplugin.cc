/*
 * test-integration-binplugin.cc
 *
 *  Created on: 8 sie 2013
 *      Author: loganek
 */

#include "mmtest.h"
#include <gstreamermm.h>
#include <glibmm/main.h>

#include "pluginbin.h"

using namespace Gst;
using Glib::RefPtr;

RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case MESSAGE_EOS:
    mainloop->quit();
    return false;
  case MESSAGE_ERROR:
    mainloop->quit();
    return false;
  default:
    break;
  }

  return true;
}

TEST(IntegrationBinPluginTest, DISABLED_ShouldDecodeAndEncodeFile)
{
  Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "pluginbin",
              "pluginbin is example of C++ element", sigc::ptr_fun(&PluginBin::register_pluginbin), "0.1",
              "LGPL", "source?", "package?", "http://example.com");

  Glib::ustring input_png = "resources/input-image.png",
          output_jpg = "resources/test-integration-binplugin-output-image.jpg";

  mainloop = Glib::MainLoop::create();
  MM_ASSERT_TRUE(mainloop);
  RefPtr<Element> pluginbin = Gst::ElementFactory::create_element("pluginbin", "sample-pluginbin");
  MM_ASSERT_TRUE(pluginbin);
  RefPtr<Element> jpg_encoder = ElementFactory::create_element("queue");
  MM_ASSERT_TRUE(jpg_encoder);
  RefPtr<Element> file_sink = ElementFactory::create_element("filesink", "file-sink");
  MM_ASSERT_TRUE(file_sink);
  RefPtr<Pipeline> pipeline = Pipeline::create("image-converter-pipeline");
  MM_ASSERT_TRUE(pipeline);

  ASSERT_NO_THROW(pipeline->add(pluginbin)->add(jpg_encoder)->add(file_sink));
  ASSERT_NO_THROW(pluginbin->link(jpg_encoder)->link(file_sink));

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  MM_ASSERT_TRUE(bus);
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  pluginbin->set_property("location", input_png);
  file_sink->set_property("location", output_jpg);

  pipeline->set_state(STATE_PLAYING);
  mainloop->run();

  pipeline->set_state(Gst::STATE_NULL);

  struct stat st;
  stat(output_jpg.c_str(), &st);
  MM_ASSERT_TRUE( st.st_size > 0 ); // weak checking
}
