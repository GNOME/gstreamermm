/*
 * test-allocator.cc
 *
 *  Created on: Aug 4, 2014
 *      Author: loganek
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;

TEST(AllocatorTest, ShouldFindSystemAllocator)
{
  Glib::RefPtr<Allocator> allocator = Allocator::find(GST_ALLOCATOR_SYSMEM);

  ASSERT_TRUE(allocator);
}

TEST(AllocatorTest, DefaultAllocatorTheSameAsSystemAllocator)
{
  Glib::RefPtr<Allocator> allocator1 = Allocator::find(GST_ALLOCATOR_SYSMEM),
		allocator2 = Allocator::get_default_allocator();

  ASSERT_TRUE(allocator1);
  ASSERT_EQ(allocator1, allocator2);
}

TEST(AllocatorTest, ShouldCorrectAllocateMemory)
{
  AllocationParams params;
  params.set_align(7);
  MemoryFlags flags = MEMORY_FLAG_NO_SHARE | MEMORY_FLAG_LAST;
  params.set_flags(flags);
  Glib::RefPtr<Allocator> allocator = Allocator::get_default_allocator();
  Glib::RefPtr<Memory> mem = allocator->alloc(10, params);

  ASSERT_TRUE(mem);
  EXPECT_EQ(10, mem->get_size());
  EXPECT_EQ(7, mem->get_align());
  EXPECT_TRUE(flags & mem->get_flags());

  allocator->free(mem);
}
