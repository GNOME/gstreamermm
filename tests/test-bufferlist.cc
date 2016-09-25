/*
 * test-bufferlist.cc
 *
 *  Created on: Aug 22, 2015
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm/bufferlist.h>
#include <gstreamermm/buffer.h>

using namespace Gst;

TEST(BufferTest, BufferShouldBeReleasedAfterAddToAList)
{
  Glib::RefPtr<Gst::BufferList> list = Gst::BufferList::create();
  Glib::RefPtr<Gst::Buffer> buff = Gst::Buffer::create();
  Glib::RefPtr<Gst::Buffer> buff2 = buff;
  list->insert(0, std::move(buff));
  MM_ASSERT_FALSE(buff);
  buff = list->get(0);
  MM_ASSERT_TRUE(buff == buff2);
}
