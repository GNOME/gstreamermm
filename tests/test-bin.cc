/*
 * test-bin.cc
 *
 *  Created on: Jul 31, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <string>

using namespace Gst;
using Glib::RefPtr;

class BinTest : public ::testing::Test
{
protected:
    RefPtr<Bin> bin;
    static constexpr gchar* element_name = "source";
    static constexpr gchar* default_element = "fakesrc";

    virtual void SetUp()
    {
        bin = Bin::create("sample-bin");
    }

    RefPtr<Element> AddElementToBin(const gchar* element_name = default_element, const gchar* name = element_name)
    {
        RefPtr<Element> element = ElementFactory::create_element(element_name, name);

        bin->add(element);

        return element;
    }
};


TEST_F(BinTest, CreatingBin)
{
    ASSERT_TRUE(bin);
}


TEST_F(BinTest, GetElementFromBin)
{
    AddElementToBin();

    RefPtr<Element> source_copy = bin->get_element(element_name);

    ASSERT_TRUE(source_copy);
}

TEST_F(BinTest, GetNonExistingElement)
{
    AddElementToBin();

    RefPtr<Element> source_copy = bin->get_element("element-with-this-name-cannot-exists-in-bin");

    ASSERT_FALSE(source_copy);
}

TEST_F(BinTest, RemoveElementFromBin)
{
    AddElementToBin();

    RefPtr<Element> source = bin->get_element(element_name);

    bin->remove(source);

    RefPtr<Element> source_copy = bin->get_element(element_name);

    ASSERT_FALSE(source_copy);
}

TEST_F(BinTest, FindElementInParentBin)
{
    RefPtr<Bin> bin_child = Bin::create();

    AddElementToBin();

    bin->add(bin_child);

    RefPtr<Element> source = bin_child->get_element_recurse_up(element_name);

    ASSERT_TRUE(source);
}

TEST_F(BinTest, AddTwoElementsWithTheSameName)
{
    AddElementToBin();

    EXPECT_ANY_THROW(AddElementToBin());
}

TEST_F(BinTest, FindUnlinkedPad)
{
    AddElementToBin();
    AddElementToBin("fakesink", "sink");

    RefPtr<Pad> pad_sink = bin->find_unlinked_pad(PAD_SINK);
    RefPtr<Pad> pad_src = bin->find_unlinked_pad(PAD_SRC);

    ASSERT_TRUE(pad_sink);
    ASSERT_TRUE(pad_src);
}

TEST_F(BinTest, FindUnlinkedPadWhenElementsAreLinked)
{
    RefPtr<Element> src = AddElementToBin();
    RefPtr<Element> sink = AddElementToBin("fakesink", "sink");

    src->link(sink);

    RefPtr<Pad> pad_sink = bin->find_unlinked_pad(PAD_SINK);
    RefPtr<Pad> pad_src = bin->find_unlinked_pad(PAD_SRC);

    ASSERT_FALSE(pad_sink);
    ASSERT_FALSE(pad_src);
}

TEST_F(BinTest, GetCorrectChildNumber)
{
    int element_count = 5;

    for (int i =0; i < element_count; i++)
        AddElementToBin("fakesrc", std::string(std::string("element") + std::to_string(i)).c_str());

    EXPECT_EQ(element_count, bin->get_num_children());
}
