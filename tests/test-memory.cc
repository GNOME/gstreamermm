/*
 * test-message.cc
 *
 *  Created on: Feb 28, 2015
 *      Author: m.kolny
 */
#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

TEST(MemoryTest, CheckMemoryMappedRefcount)
{
  guint* data = new guint[10];
  Glib::RefPtr<Memory> mem = Memory::create(MEMORY_FLAG_READONLY, data, 10, 0, 10);
  MapInfo info;
  Glib::RefPtr<Memory> mp = mem->make_mapped(info, MAP_READ);
  mp->unmap(info);
  ASSERT_EQ(2, mem->get_refcount());
  ASSERT_EQ(2, mp->get_refcount());
  delete [] data;
}
