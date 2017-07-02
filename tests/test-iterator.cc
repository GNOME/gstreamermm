#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;

TEST(IteratorTest, AssignmentOperatorShouldCopyIterator)
{
  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("fakesink");

  Gst::Iterator<Gst::Pad> iter = element->iterate_pads();
  Gst::Iterator<Gst::Pad> iter2;
  iter2 = iter;

  while (iter.next())
  {
    ASSERT_STREQ("sink", iter->get_name().c_str());
  }

  while(iter2.next())
  {
    ASSERT_STREQ("sink", iter2->get_name().c_str());
  }
}


TEST(IteratorTest, BeginShouldResetIterator)
{
  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("fakesink");

  Gst::Iterator<Gst::Pad> iter = element->iterate_pads();
  
  while (iter.next())
  {
    ASSERT_STREQ("sink", iter->get_name().c_str());
  }

  iter.begin();
  while (iter.next())
  {
    ASSERT_STREQ("sink", iter->get_name().c_str());
  }
}

TEST(IteratorTest, CopyConstructorShouldCopyIteratorAndItsState)
{
  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("fakesink");

  Gst::Iterator<Gst::Pad> iter = element->iterate_pads();

  while (iter.next())
  {
    ASSERT_STREQ("sink", iter->get_name().c_str());
  }

  ASSERT_FALSE(iter.next());

  Gst::Iterator<Gst::Pad> iter2 = iter;

  ASSERT_FALSE(iter.next());
}

