#include <gtest/gtest.h>
#include <glibmm/threads.h>
#include <gstreamermm/identity.h>
#include <gstreamermm/iterator.h>
#include <gstreamermm/bus.h>

using namespace Gst;
using namespace Glib;

TEST(ElementTest, PostMessageShouldProperlyRefcountGivenMessage)
{
  RefPtr<Bus> bus = Bus::create();
  ASSERT_TRUE(bus);
  RefPtr<Element> element = Identity::create();
  ASSERT_TRUE(element);
  element->set_bus(bus);
  ASSERT_TRUE(element->post_message(MessageStateDirty::create(element)));
  RefPtr<Message> msg = bus->pop();
  ASSERT_TRUE(msg);
  ASSERT_TRUE(GST_IS_MESSAGE(msg->gobj()));
  ASSERT_EQ(1, msg->get_refcount());
}
