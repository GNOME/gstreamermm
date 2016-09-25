/*
 * test-allocator.cc
 *
 *  Created on: Aug 4, 2014
 *      Author: loganek
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

TEST(AllocatorTest, ShouldFindSystemAllocator)
{
  Glib::RefPtr<Allocator> allocator = Allocator::find(GST_ALLOCATOR_SYSMEM);

  MM_ASSERT_TRUE(allocator);
}

TEST(AllocatorTest, DefaultAllocatorTheSameAsSystemAllocator)
{
  Glib::RefPtr<Allocator> allocator1 = Allocator::find(GST_ALLOCATOR_SYSMEM),
		allocator2 = Allocator::get_default_allocator();

  MM_ASSERT_TRUE(allocator1);
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

  MM_ASSERT_TRUE(mem);
  EXPECT_EQ(10ul, mem->get_size());
  EXPECT_EQ(7ul, mem->get_align());
  EXPECT_TRUE(flags & mem->get_flags());

  allocator->free(std::move(mem));
}

class DerivedFromAllocator : public Gst::Allocator
{
  Glib::RefPtr<Gst::Allocator> the_allocator;

public:
  explicit DerivedFromAllocator(GstAllocator *gobj)
  : Glib::ObjectBase(typeid (DerivedFromAllocator)),
    Gst::Allocator(gobj),
    the_allocator(Allocator::get_default_allocator())
  {
  }

  Glib::RefPtr<Gst::Memory> alloc_vfunc(gsize size, const AllocationParams& params) override
  {
    Glib::RefPtr<Gst::Memory> r = the_allocator->alloc(size, params);
    r->gobj()->allocator = gobj(); // pretend that it was us who allocated this memory
    return r;
  }

  void free_vfunc(Glib::RefPtr<Gst::Memory>&& memory) override
  {
    memory->gobj()->allocator = the_allocator->gobj(); // pretend that it was the_allocator who allocated this memory
    the_allocator->free(std::move(memory));
  }

  static Glib::RefPtr<Allocator> create()
  {
    return Glib::RefPtr<Allocator>(new DerivedFromAllocator((GstAllocator*)g_object_new(Allocator::get_type(), NULL)));
  }
};

TEST(AllocatorTest, DerivedFromAllocatorShouldReturnProperlyRefcountedWrappedGstMemory)
{
  Glib::RefPtr<Allocator> allocator = DerivedFromAllocator::create();
  MM_ASSERT_TRUE(allocator);
  MM_ASSERT_TRUE(allocator->gobj());
  MM_ASSERT_TRUE(GST_IS_ALLOCATOR(allocator->gobj()));

  AllocationParams params;
  params.set_align(7);
  MemoryFlags flags = MEMORY_FLAG_NO_SHARE | MEMORY_FLAG_LAST;
  params.set_flags(flags);

  Glib::RefPtr<Memory> mem = allocator->alloc(10, params);
  MM_ASSERT_TRUE(mem);
  MM_ASSERT_TRUE(mem->gobj());
  MM_ASSERT_TRUE(GST_IS_MINI_OBJECT_TYPE(mem->gobj(), GST_TYPE_MEMORY));
  ASSERT_EQ(1, mem->get_refcount());
  EXPECT_EQ(10ul, mem->get_size());
  EXPECT_EQ(7ul, mem->get_align());
  EXPECT_TRUE(flags & mem->get_flags());

  allocator->free(std::move(mem));
}

TEST(AllocatorTest, DerivedFromAllocatorShouldReturnProperlyRefcountedGstMemory)
{
  Glib::RefPtr<Allocator> allocator = DerivedFromAllocator::create();
  MM_ASSERT_TRUE(allocator);
  MM_ASSERT_TRUE(allocator->gobj());
  MM_ASSERT_TRUE(GST_IS_ALLOCATOR(allocator->gobj()));

  AllocationParams params;
  params.set_align(7);
  MemoryFlags flags = MEMORY_FLAG_NO_SHARE | MEMORY_FLAG_LAST;
  params.set_flags(flags);

  GstMemory *mem = gst_allocator_alloc(allocator->gobj(), 10, params.gobj());
  MM_ASSERT_TRUE(mem);
  MM_ASSERT_TRUE(GST_IS_MINI_OBJECT_TYPE(mem, GST_TYPE_MEMORY));
  ASSERT_EQ(1, mem->mini_object.refcount);
  EXPECT_EQ(10ul, mem->size);
  EXPECT_EQ(7ul, mem->align);
  EXPECT_TRUE(flags & mem->mini_object.flags);
  gst_allocator_free(allocator->gobj(), mem);
}
