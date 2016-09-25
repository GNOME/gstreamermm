#include "mmtest.h"
#include <glibmm/threads.h>
#include <gstreamermm/identity.h>
#include <gstreamermm/iterator.h>
#include <gstreamermm/bus.h>

using namespace Gst;
using namespace Glib;

TEST(ElementTest, PostMessageShouldProperlyRefcountGivenMessage)
{
  RefPtr<Bus> bus = Bus::create();
  MM_ASSERT_TRUE(bus);
  RefPtr<Element> element = Identity::create();
  MM_ASSERT_TRUE(element);
  element->set_bus(bus);
  MM_ASSERT_TRUE(element->post_message(MessageStateDirty::create(element)));
  RefPtr<Message> msg = bus->pop();
  MM_ASSERT_TRUE(msg);
  MM_ASSERT_TRUE(GST_IS_MESSAGE(msg->gobj()));
  ASSERT_EQ(1, msg->get_refcount());
}
