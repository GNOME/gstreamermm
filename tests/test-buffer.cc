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

TEST(BufferTest, PeekedMemoryShouldExistsEvenWhenBufferWillBeDestroyed)
{
  Glib::RefPtr<Memory> mem;
  {
    Glib::RefPtr<Buffer> buf = Buffer::create(123);
    mem = buf->peek_memory(0);
  }

  ASSERT_EQ(1, mem->gobj()->mini_object.refcount);
}

TEST(BufferTest, ShouldInsertMemoryObjectAndResetItButAllowToMakeExplicityRef)
{
  Glib::RefPtr<Memory> mem2;
  char *data = new char[10];
  Glib::RefPtr<Memory> mem = Memory::create(Gst::MEMORY_FLAG_READONLY, data, 10, 0, 10);
  delete data;
  Glib::RefPtr<Buffer> buf = Buffer::create(10);
  mem2 = mem;
  buf->insert_memory(0, mem);
  ASSERT_FALSE(mem);
  ASSERT_EQ(2, mem2->gobj()->mini_object.refcount); // two - one handled by mem2,
                                                    //and the second by memory stored in buffer
}

TEST(BufferTest, ShouldGetMemoryRangeAndIncreaseRefcount)
{
  Glib::RefPtr<Memory> mem;
  {
    Glib::RefPtr<Buffer> buf = Buffer::create(10);
    mem = buf->get_memory_range(0, -1);
  }
  ASSERT_EQ(1, mem->gobj()->mini_object.refcount);
}

TEST(BufferTest, ShouldResetMemoryPointerButAllowIncreaseRefcount)
{
  char *data = new char[10];
  Glib::RefPtr<Memory> mem = Memory::create(Gst::MEMORY_FLAG_READONLY, data, 10, 0, 10);
  delete data;
  Glib::RefPtr<Memory> mem2 = mem;
  {
    Glib::RefPtr<Buffer> buf = Buffer::create(10);
    buf->replace_memory_range(0, -1, mem);
  }
  ASSERT_FALSE(mem);
  ASSERT_EQ(1, mem2->gobj()->mini_object.refcount);
}

TEST(BufferTest, CheckBufferRefcountAfterCopyingRegion)
{
  Glib::RefPtr<Buffer> buf = Buffer::create(10);
  auto b = buf->copy_region(BUFFER_COPY_MEMORY, 0, 10);
  ASSERT_EQ(1, b->gobj()->mini_object.refcount);
  ASSERT_EQ(1, buf->gobj()->mini_object.refcount);
}

TEST(BufferTest, CheckBufferRefcountAfterCopying)
{
  Glib::RefPtr<Buffer> buf = Buffer::create(10);
  auto b = buf->copy();
  ASSERT_EQ(1, b->gobj()->mini_object.refcount);
  ASSERT_EQ(1, buf->gobj()->mini_object.refcount);
}
