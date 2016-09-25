/*
 * test-buffer.cc
 *
 *  Created on: Jul 31, 2013
 *    Author: m.kolny
 */

#include "mmtest.h"
#include <glibmm/threads.h>
#include <gstreamermm/buffer.h>

using namespace Gst;

TEST(BufferTest, CheckBufferSize)
{
  gsize buff_size = 23;
  Glib::RefPtr<Buffer> buf = Buffer::create(buff_size);
  MapInfo map_info;

  buf->map(map_info, MAP_READ);

  EXPECT_EQ(buff_size, map_info.get_size());

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
  delete [] data;
  Glib::RefPtr<Buffer> buf = Buffer::create(10);
  mem2 = mem;
  buf->insert_memory(0, std::move(mem));
  MM_ASSERT_FALSE(mem);
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
  delete [] data;
  Glib::RefPtr<Memory> mem2 = mem;
  {
    Glib::RefPtr<Buffer> buf = Buffer::create(10);
    buf->replace_memory_range(0, -1, std::move(mem));
  }
  MM_ASSERT_FALSE(mem);
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

TEST(BufferTest, CheckBufferCopyIntoMethod)
{
  std::vector<char> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  Glib::RefPtr<Buffer> src = Buffer::create(data.size());
  Glib::RefPtr<Buffer> dest = Buffer::create();
  src->set_pts(10);
  MapInfo info;
  src->map(info, MAP_READ);
  std::copy(data.begin(), data.end(), info.get_data());
  src->unmap(info);

  Gst::Buffer::copy_into(dest, src, BUFFER_COPY_TIMESTAMPS | BUFFER_COPY_MEMORY, 0, data.size());
  ASSERT_EQ(dest->get_pts(), 10ul);
  ASSERT_EQ(data.size(), dest->get_size());

  ASSERT_EQ(0, dest->memcmp(0, data.data(), data.size()));
  
  ASSERT_EQ(1, src->get_refcount());
  ASSERT_EQ(1, dest->get_refcount());
}

TEST(BufferTest, CheckRefcountAppendBufferToBuffer)
{
  Glib::RefPtr<Gst::Buffer> buf1 = Gst::Buffer::create(10);

  { // buf1 not writable
    Glib::RefPtr<Gst::Buffer> buf2 = Gst::Buffer::create(6);
  Glib::RefPtr<Gst::Buffer> dummy = buf1;
    Glib::RefPtr<Gst::Buffer> b = buf1->append(std::move(buf2));
    MM_ASSERT_FALSE(buf2);
    ASSERT_EQ(2, buf1->get_refcount()); // dummy + buf1
    ASSERT_EQ(1, b->get_refcount());
    ASSERT_EQ(16u, b->get_size());
    ASSERT_EQ(10u, buf1->get_size());
    MM_ASSERT_FALSE(b == buf1);
  }

  { // buf1 writable
    Glib::RefPtr<Gst::Buffer> buf2 = Gst::Buffer::create(6);
    Glib::RefPtr<Gst::Buffer> b = buf1->append(std::move(buf2));
    MM_ASSERT_FALSE(buf2);
    ASSERT_EQ(2, buf1->get_refcount()); // b + buf1
    ASSERT_EQ(2, b->get_refcount());
    ASSERT_EQ(16u, b->get_size());
    MM_ASSERT_TRUE(b == buf1);
  }
}
