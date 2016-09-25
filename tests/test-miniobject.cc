/*
 * test-miniobject.cc
 *
 *  Created on: Aug 19, 2014
 *      Author: m.kolny
 */

#include "mmtest.h"
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

TEST(MiniObjectTest, CheckFinalizeNotifier)
{
  int finalize_cnt = 0;
  {
    RefPtr<Buffer> obj = Buffer::create();
    obj->add_finalize_notifier([&finalize_cnt](){
      finalize_cnt++;
    });
  }

  ASSERT_EQ(1, finalize_cnt);
}

TEST(MiniObjectTest, ShouldCorrectRemoveFinalizeHandler)
{
  int finalize_cnt = 0;
  {
    RefPtr<Buffer> obj = Buffer::create();
    obj->add_finalize_notifier([&finalize_cnt](){
      finalize_cnt++;
    });
    obj->remove_finalize_notifier();
  }

  ASSERT_EQ(0, finalize_cnt);
}

TEST(MiniObjectTest, AddRemoveFinalizerHandlerCombination)
{
  int finalize_cnt = 0;
  {
    RefPtr<Buffer> obj = Buffer::create();
    obj->add_finalize_notifier([&finalize_cnt](){
      finalize_cnt++;
    });
    obj->remove_finalize_notifier();
    obj->add_finalize_notifier([&finalize_cnt](){
      finalize_cnt += 17;
    });
    obj->add_finalize_notifier([&finalize_cnt](){
      finalize_cnt += 104;
    });
  }

  ASSERT_EQ(104, finalize_cnt);
}
