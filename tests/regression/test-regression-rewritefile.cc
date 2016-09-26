/*
 * test-rewritefile.cc
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>
#include <glibmm/main.h>
#include <cstdio>
#include "utils.h"

using namespace Gst;
using Glib::RefPtr;

RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case Gst::MESSAGE_EOS:
    mainloop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
    mainloop->quit();
    return false;
  default:
    break;
  }

  return true;
}

TEST(RegressionRewriteFileTest, CreateAndRewriteFile)
{
  Glib::ustring input_filename = "test.ogg",
          output_filename = "output.ogg";

  GenerateSampleOggFile(20, input_filename);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  RefPtr<FileSrc> filesrc = Gst::FileSrc::create();
  MM_ASSERT_TRUE(filesrc);

  filesrc->property_location() = input_filename;

  mainloop = Glib::MainLoop::create();
  pipeline = Gst::Pipeline::create("rewriter");
  Glib::RefPtr<Gst::FileSink> filesink = Gst::FileSink::create();
  MM_ASSERT_TRUE(filesink);

  filesink->property_location() = output_filename;

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  pipeline->add(filesrc)->add(filesink);

  pipeline->set_state(Gst::STATE_PLAYING);
  filesrc->link(filesink);
  mainloop->run();

  pipeline->set_state(Gst::STATE_NULL);

  EXPECT_TRUE(FilesEqual(input_filename, output_filename));

  remove(input_filename.c_str());
  remove(output_filename.c_str());
}
