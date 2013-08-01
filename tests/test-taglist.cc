/*
 * test-taglist.cc
 *
 *  Created on: Jul 31, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;


class TagListTest : public ::testing::Test
{
protected:
    TagList tag_list;

    static Glib::ustring song_title;
    static Glib::ustring song_artist;
    static guint64 song_duration;
    static Glib::Date song_date;

    virtual void SetUp()
    {
        tag_list.add(TAG_TITLE, song_title);
        tag_list.add(TAG_ARTIST, song_artist);
        tag_list.add(TAG_DURATION, song_duration);
        tag_list.add(TAG_DATE, song_date);
    }

    template<typename Ty>
    Ty ValidateTag(Tag tag)
    {
        Ty output;

        bool ok = tag_list.get(tag, output);

        EXPECT_EQ(true, ok);

        return output;
    }
};

Glib::ustring TagListTest::song_title = "Funky Song";
Glib::ustring TagListTest::song_artist = "Marcin Kolny";
guint64 TagListTest::song_duration = 120;
Glib::Date TagListTest::song_date = Glib::Date(28, Glib::Date::DECEMBER, 1991);


TEST_F(TagListTest, GetTagTitleFromList)
{
    Glib::ustring out_title = ValidateTag<Glib::ustring>(TAG_TITLE);
    ASSERT_STREQ(song_title.c_str(), out_title.c_str());
}

TEST_F(TagListTest, GetTagArtistFromList)
{
    Glib::ustring out_artist = ValidateTag<Glib::ustring>(TAG_ARTIST);
    ASSERT_STREQ(song_artist.c_str(), out_artist.c_str());
}

TEST_F(TagListTest, GetTagDurationFromList)
{
    guint64 out_duration = ValidateTag<guint64>(TAG_DURATION);
    EXPECT_EQ(song_duration, out_duration);
}

TEST_F(TagListTest, GetTagDateFromList)
{
    Glib::Date out_date = ValidateTag<Glib::Date>(TAG_DATE);

    EXPECT_EQ(song_date.get_day(), out_date.get_day());
    EXPECT_EQ(song_date.get_year(), out_date.get_year());
    EXPECT_EQ(song_date.get_month(), out_date.get_month());
}

TEST_F(TagListTest, GetNonExistingTag)
{
	Glib::ustring album;

    bool album_exists = tag_list.get(TAG_ALBUM, album);

    ASSERT_FALSE(album_exists);

}
