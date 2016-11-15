/*
 * test-caps.cc
 *
 *  Created on: Aug 1, 2013
 *    Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

class CapsTest : public ::testing::Test
{
protected:
  Glib::RefPtr<Caps> caps;

  static int width;
  static Fraction framerate;

  template<typename T>
  void MakeAssert(const T& expected, const T& output)
  {
    EXPECT_EQ(expected, output);
  }
  void MakeAssert(const Fraction& expected, const Fraction& output)
  {
    EXPECT_EQ(expected.denom, output.denom);
    EXPECT_EQ(expected.num, output.num);
  }

  template<typename T>
  void CheckCaps(const Glib::ustring& field_name, T expected, int struct_id = 0)
  {
    T output;
    bool ok = caps->get_structure(struct_id).get_field(field_name, output);

    MM_ASSERT_TRUE(ok);
    MakeAssert(expected, output);
  }
};

int CapsTest::width = 500;
Fraction CapsTest::framerate = Fraction(25, 1);

TEST_F(CapsTest, CapsCreateSimple)
{
  caps = Caps::create_simple("video/x-raw");

  MM_ASSERT_TRUE(caps);
}

TEST_F(CapsTest, CapsCreateUsingStructure)
{
  Structure caps_struct("test-struct");
  caps_struct.set_field("width", width);
  caps_struct.set_field("framerate", framerate);

  caps = Caps::create(caps_struct);

  CheckCaps("width", width);
  CheckCaps("framerate", framerate);
}

TEST_F(CapsTest, AppendStructureToCaps)
{
  caps = Caps::create_simple("video/x-raw");

  Structure caps_struct("test-struct");
  caps_struct.set_field("width", width);

  caps->set_simple("framerate", framerate);
  caps->append_structure(caps_struct);

  CheckCaps("width", width, 1);
  CheckCaps("framerate", framerate);
}

TEST_F(CapsTest, AppendCapsToCaps)
{
  caps = Caps::create_simple("video/x-raw");
  caps->set_simple("framerate", framerate);

  Glib::RefPtr<Caps> new_caps = Caps::create_simple("video/x-raw");
  new_caps->set_simple("width", width);

  caps->append(std::move(new_caps));

  CheckCaps("width", width, 1);
  CheckCaps("framerate", framerate);
  MM_ASSERT_FALSE(new_caps);
}

TEST_F(CapsTest, GetNonExistingValue)
{
  caps = Caps::create_simple("video/x-raw");

  int output;
  bool ok = caps->get_structure(0).get_field("nonexisting-value", output);

  MM_ASSERT_FALSE(ok);
}

TEST_F(CapsTest, SetCapsToElement)
{
  Glib::RefPtr<Element> element = ElementFactory::create_element("capsfilter", "filter");

  const char* str_caps = "image/jpeg, framerate=(fraction)2/1";

  element->set_property("caps", Caps::create_from_string(str_caps));
  element->get_property("caps", caps);

  ASSERT_STREQ(str_caps, caps->to_string().c_str());
}

TEST_F(CapsTest, MergeCaps)
{
  Glib::RefPtr<Caps> tmp = Caps::create_from_string("video/x-raw, format=RGBA");
  Glib::RefPtr<Caps> tmp2 = Caps::create_from_string("video/x-raw, format=RGB");
  tmp = tmp->merge(std::move(tmp2));
  ASSERT_EQ(1, tmp->get_refcount());
  MM_ASSERT_FALSE(tmp2);
}

TEST_F(CapsTest, CapsBoxedType)
{
  Glib::RefPtr<Gst::Element> filter = Gst::ElementFactory::create_element("capsfilter");
  Glib::RefPtr<Gst::Caps> any_caps = Gst::Caps::create_any();
  Glib::RefPtr<Gst::Caps> any_caps2 = Gst::Caps::create_any();
  ASSERT_EQ(1, any_caps->get_refcount());
  filter->set_property("caps", any_caps);
  ASSERT_EQ(2, any_caps->get_refcount());
  filter->set_property("caps", any_caps2);
  ASSERT_EQ(1, any_caps->get_refcount());
  ASSERT_EQ(2, any_caps2->get_refcount());
}

TEST_F(CapsTest, CreateSimpleWithManyParameters)
{
  caps = Caps::create_simple("video/x-raw", "width", width, "framerate", framerate, "test-data", "test-value");
  CheckCaps("width", width);
  CheckCaps("framerate", framerate);
  CheckCaps<std::string>("test-data", "test-value");
}

TEST_F(CapsTest, SetSimpleWithManyParameters)
{
  caps = Caps::create_simple("video/x-raw");
  caps->set_simple("width", width, "framerate", framerate, "test-data", "test-value");
  CheckCaps("width", width);
  CheckCaps("framerate", framerate);
  CheckCaps<std::string>("test-data", "test-value");
}

class CapsTestDummy1
{
public:
	int a = 0;
	std::string b;
	CapsTestDummy1(int a, std::string b) : a(a), b(b) {}
	CapsTestDummy1() {}
};
class CapsTestDummy2
{
public:
	char c = 0;
	CapsTestDummy2(char c) : c(c) {}
	CapsTestDummy2() {}
};


TEST_F(CapsTest, CreateWithManyCustomTypeParameters)
{
  caps = Caps::create_simple("video/x-raw");
  caps->set_simple("d1", CapsTestDummy1(1, "dummy1"), "d2", CapsTestDummy2('x'), "d3", CapsTestDummy1(63, "dummy3"));
  Glib::Value<CapsTestDummy1> d1, d3;
  Glib::Value<CapsTestDummy2> d2;
  caps->get_structure(0).get_field("d1", d1);
  caps->get_structure(0).get_field("d2", d2);
  caps->get_structure(0).get_field("d3", d3);

  ASSERT_STREQ("dummy1", d1.get().b.c_str());
  ASSERT_EQ(1, d1.get().a);

  ASSERT_EQ('x', d2.get().c);

  ASSERT_STREQ("dummy3", d3.get().b.c_str());
  ASSERT_EQ(63, d3.get().a);
}
