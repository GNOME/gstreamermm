/*
 * test-buffer.cc
 *
 *  Created on: Jul 31, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <glibmm/threads.h>
#include <gstreamermm/buffer.h>

using namespace Gst;

TEST(BufferTest, CheckBufferSize)
{
    int buff_size = 23;
    Glib::RefPtr<Buffer> buf = Buffer::create(buff_size);
    Glib::RefPtr<MapInfo> map_info(new MapInfo());

    buf->map(map_info, MAP_READ);

    EXPECT_EQ(buff_size, map_info->get_size());

    buf->unmap(map_info);
}

TEST(BufferTest, CheckBufferFlags)
{
    guint buff_flags = 1;
    Glib::RefPtr<Buffer> buf = Buffer::create();

    buf->set_flags(buff_flags);

    EXPECT_EQ(buff_flags, buf->get_flags());
}
