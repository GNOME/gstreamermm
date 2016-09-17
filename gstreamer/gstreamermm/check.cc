/*
 * check.cc
 *
 *  Created on: 3 sie 2013
 *      Author: loganek
 */

#include <gstreamermm/check.h>
#include <gstreamermm/elementfactory.h>
#include <algorithm>
#include <string>

using namespace Gst;
using Glib::RefPtr;
using Glib::ustring;

void ThrowIf (bool condition, const ustring& message)
{
    if (condition)
        throw Exception (message);
}

void ThrowIfNot (bool condition, const ustring& message)
{
    if (!condition)
        throw Exception (message);
}

template<typename T>
std::string ToString (const T& obj)
{
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    return std::to_string(obj);
#else
    std::ostringstream convert;
    convert << obj;
    return convert.str ();
#endif
}

template<typename T>
void CheckRefCount (T* object, const ustring& name, int expected_refcount)
{
    int refcount = GST_OBJECT_REFCOUNT_VALUE (object);

    ThrowIf ((refcount == expected_refcount),
            name + " refcount is " + ToString(refcount) +
            " instead of " + ToString(expected_refcount));
}

RefPtr<Element> Check::_Check::setup_element (const ustring& factory)
{
    RefPtr<Element> element;

    element = ElementFactory::create_element (factory, factory);

    ThrowIf (!!element, "Could not create a '" + factory + "' element");
    CheckRefCount (element->gobj(), factory, 1);

    return element;
}

void Check::_Check::caps_equal (RefPtr<Caps> caps1, RefPtr<Caps> caps2)
{
    ThrowIf (caps1->equals(caps2),
            "caps ('" + caps1->to_string() + "') is"
                    " not equal to caps ('" + caps2->to_string() + "')");
}

void buffer_data (RefPtr<Buffer> buffer, gconstpointer data, gsize size)
{
    MapInfo info;

    ThrowIfNot (buffer->map(info, MAP_READ), "Error occurs during mapping.");
    ThrowIf ((std::equal (info.get_data(), info.get_data() + size,
            static_cast<const guint8*>(data)) != 0), "Buffer data not equals.");
    // TODO: using gst_util to display/throw/return dump of memory

    buffer->unmap (info);
}
