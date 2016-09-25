/*
 * test-message.cc
 *
 *  Created on: Feb 27, 2015
 *      Author: m.kolny
 */
#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

TEST(MessageTest, CheckDerivedMessageRefcount)
{
  Glib::RefPtr<MessageStateDirty> msg = MessageStateDirty::create(Glib::RefPtr<Object>());
  ASSERT_EQ(1, msg->get_refcount());
}
