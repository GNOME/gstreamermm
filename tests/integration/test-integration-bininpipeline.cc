/*
 * test-integration-bininpipeline.cc
 *
 *  Created on: 5 sie 2013
 *      Author: loganek
 */

#include "mmtest.h"
#include <gstreamermm.h>
#include <glibmm/main.h>

using namespace Gst;
using Glib::RefPtr;

class CustomBin : public Bin
{
private:
  RefPtr<Element> source_file;
  RefPtr<Element> queue;
  RefPtr<GhostPad> src_pad;
protected:
  explicit CustomBin(const Glib::ustring& name)
  : Bin(name)
  {
    source_file = ElementFactory::create_element("filesrc", "source-file");
    queue = ElementFactory::create_element("queue");

    add(source_file);
    add(queue);
    source_file->link(queue);

    src_pad = add_ghost_pad(queue, "src", "src");
    src_pad->set_active(true);
  }
public:
  virtual ~CustomBin() {}

  static RefPtr<CustomBin> create(const Glib::ustring& name)
  {
    return RefPtr<CustomBin>(new CustomBin(name));
  }

  void set_location(const Glib::ustring& filename)
  {
    source_file->set_property("location", filename);
  }
};

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

TEST(IntegrationBinInPipelineTest, CustomBinShouldCorrectPassThroughImage)
{
  Glib::ustring input_png = "/home/loganek/repos/gstreamermm/tests/resources/input-image.png",
      output_jpg = "test-integration-bininpipeline-output-image.jpg";

  mainloop = Glib::MainLoop::create();
  MM_ASSERT_TRUE(mainloop);
  RefPtr<CustomBin> custom_bin = CustomBin::create("file-png-decoder");
  MM_ASSERT_TRUE(custom_bin);
  RefPtr<Element> queue = ElementFactory::create_element("queue");
  MM_ASSERT_TRUE(queue);
  RefPtr<Element> file_sink = ElementFactory::create_element("filesink", "file-sink");
  MM_ASSERT_TRUE(file_sink);
  RefPtr<Pipeline> pipeline = Pipeline::create("image-converter-pipeline");
  MM_ASSERT_TRUE(custom_bin);

  ASSERT_NO_THROW(pipeline->add(custom_bin)->add(queue)->add(file_sink));
  ASSERT_NO_THROW(custom_bin->link(queue)->link(file_sink));

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  MM_ASSERT_TRUE(bus);
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  custom_bin->set_location(input_png);

  file_sink->set_property("location", output_jpg);

  pipeline->set_state(STATE_PLAYING);

  mainloop->run();

  pipeline->set_state(Gst::STATE_NULL);
}
