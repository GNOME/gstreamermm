/*
 * test-bus.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;

class BusTest : public ::testing::Test
{
protected:
    Glib::RefPtr<Bus> bus;
    Glib::RefPtr<Message> message;

    void PostMessage()
    {
        bool message_posted = bus->post(MessageEos::create(Glib::RefPtr<Object>()));
        ASSERT_TRUE(message_posted);
    }

    void CheckPending(bool expected = true)
    {
        bool have_pending = bus->have_pending();
        EXPECT_EQ(expected, have_pending);
    }
};

TEST_F(BusTest, CorrectCreateBus)
{
    bus = Bus::create();

    ASSERT_TRUE(bus);
}

TEST_F(BusTest, PostMessageAndPeekIt)
{
    bus = Bus::create();

    PostMessage();
    CheckPending();

    Glib::RefPtr<Message> msg = bus->peek();

    ASSERT_TRUE(msg);
}

TEST_F(BusTest, PostMessageAndPopIt)
{
    bus = Bus::create();

    PostMessage();
    CheckPending();

    Glib::RefPtr<Message> msg = bus->pop();

    ASSERT_TRUE(msg);

    CheckPending(false);
}
