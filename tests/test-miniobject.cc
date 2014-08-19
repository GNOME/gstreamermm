/*
 * test-miniobject.cc
 *
 *  Created on: Aug 19, 2014
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;

TEST(MiniObjectTest, ShouldCorrectCreateWritableObjects)
{
	// we cannot create Gst::MiniObject object, so I used Gst::Buffer::create
	// method to make an object.
	RefPtr<MiniObject> obj = Buffer::create();

	ASSERT_EQ(1, obj->gobj()->refcount);

	obj = obj->create_writable();

	ASSERT_EQ(1, obj->gobj()->refcount);

	RefPtr<MiniObject> obj2 = obj;

	ASSERT_EQ(2, obj->gobj()->refcount);
	ASSERT_EQ(2, obj2->gobj()->refcount);

	obj2 = obj->create_writable();

	ASSERT_EQ(1, obj->gobj()->refcount);
	ASSERT_EQ(1, obj2->gobj()->refcount);
}

