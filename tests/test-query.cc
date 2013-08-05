/*
 * test-query.cc
 *
 *  Created on: 5 sie 2013
 *      Author: loganek
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;


// TODO use std::function instead of c++ pointers - some strange errors occurs
template<typename RetType, typename QType, QueryType type, typename... Args>
void CreatingQueryTest(RefPtr<RetType> (*create_method)(Args...) , Args... args)
{
    RefPtr<Query> query = create_method(args...);

    ASSERT_TRUE(query);

    RefPtr<QType> query_position = RefPtr<QType>::cast_static(query);

    ASSERT_TRUE(query_position);

    ASSERT_EQ(type, query->get_query_type());
}

template<typename QType, QueryType type, typename... Args>
void CreatingQueryTest(Args... args)
{
    CreatingQueryTest<QType, QType, type, Args...>(&QType::create, args...);
}

template<typename QType, QueryType type, typename... Args>
void CreatingQueryTestStatic(RefPtr<Query> (*create_method)(Args...) , Args... args)
{
    CreatingQueryTest<Query, QType, type, Args...>(create_method, args...);
}


TEST(QueryTest, CorrectCreatingQueryBuffering)
{
    CreatingQueryTestStatic<QueryBuffering, QUERY_BUFFERING, Format>(&Query::new_buffering, FORMAT_BUFFERS);
    CreatingQueryTest<QueryBuffering, QUERY_BUFFERING, Format>(FORMAT_BUFFERS);
}

TEST(QueryTest, CorrectCreatingQueryPosition)
{
    CreatingQueryTestStatic<QueryPosition, QUERY_POSITION, Format>(&Query::new_position, FORMAT_PERCENT);
    CreatingQueryTest<QueryPosition, QUERY_POSITION, Format>(FORMAT_PERCENT);
}

TEST(QueryTest, CorrectCreatingQueryConvert)
{
    CreatingQueryTestStatic<QueryConvert, QUERY_CONVERT, Format, gint64, Format>(&Query::new_convert, FORMAT_PERCENT, 10, FORMAT_BYTES);
    CreatingQueryTest<QueryConvert, QUERY_CONVERT, Format, gint64, Format>(FORMAT_PERCENT, 10, FORMAT_BYTES);
}
