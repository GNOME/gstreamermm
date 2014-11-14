/*
 * check.h
 *
 *  Created on: 3 sie 2013
 *      Author: loganek
 */

#ifndef _GSTREAMERMM_CHECK_H
#define _GSTREAMERMM_CHECK_H

#include <glibmm/threads.h>
#include <glibmm/ustring.h>
#include <gstreamermm/element.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/caps.h>
#include <gstreamermm/buffer.h>
#include <stdexcept>

#define THROW_IF(condition, message) \
        if (condition) \
            throw Exception(message);

namespace Gst
{
class Exception : std::runtime_error
{
public:
    Exception(const std::string& message)
        : std::runtime_error(message)
    {}
};

class Check
{
    class _Check
    {
    public:
        /**
         * Setup an element.
         *
         * @param factory Factory.
         * @return a new element.
         * @throw Gst::Exception if creating element fails.
         */
        Glib::RefPtr<Gst::Element> setup_element (const Glib::ustring& factory);

        /**
         * Compare two caps with.
         *
         * @param caps1 First caps to compare.
         * @param caps2: Second caps to compare.
         * @throw Gst::Exception if caps are not equal.
         */
        void caps_equal (Glib::RefPtr<Gst::Caps> caps1, Glib::RefPtr<Gst::Caps> caps2);
    };

    Check();
    Check(const Check&);
    Check& operator=(const Check&);

    virtual ~Check(){}
public:
    static _Check& Instance()
    {
        static _Check instance;

        return instance;
    }
};

}

#endif
