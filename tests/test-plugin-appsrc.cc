/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gstreamermm.h>
#include <iostream>
#include <cassert>
#include <gstreamermm/appsrc.h>
#include <cstring>

int main(int argc, char** argv)
{
  Gst::init(argc, argv);

  {
    // gstreamermm plugins don't register in the mm system (why?)
    // get_type() calls "register" indirectly, however we must assure that return value is used or it won't be realy called (because of attribute((const)) )
    volatile GType dummy = Gst::AppSrc::get_type();
  }

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Element> source, sink;

  pipeline = Gst::Pipeline::create();

  source = Gst::ElementFactory::create_element("appsrc", "source");
  sink = Gst::ElementFactory::create_element("fakesink", "sink");

  assert(source);
  assert(sink);

  Glib::RefPtr<Gst::AppSrc> appsrc = appsrc.cast_dynamic(source);
  assert(appsrc);

  pipeline->add(source)->add(sink);

  source->link(sink);

  pipeline->set_state(Gst::STATE_PLAYING);

  std::string data = "hello world";
  Glib::RefPtr<Gst::Buffer> buf = Gst::Buffer::create(data.length() + 1);
  strcpy((char *)buf->get_data(), data.c_str());
  appsrc->push_buffer(buf);

  {
    std::cout << "waiting for state change" << std::endl;
    Gst::State state;
    Gst::StateChangeReturn ret=pipeline->get_state(state, state, 1*Gst::SECOND);
    assert(ret == Gst::STATE_CHANGE_SUCCESS);
  }

  appsrc->end_of_stream();

  std::cout << "waiting for eos or error" << std::endl;
  Glib::RefPtr<Gst::Message> msg = pipeline->get_bus()->poll((Gst::MessageType)(Gst::MESSAGE_EOS | Gst::MESSAGE_ERROR) , 1*Gst::SECOND);
  assert(msg);
  assert(msg->get_message_type() == Gst::MESSAGE_EOS);
  std::cout << "shutting down" << std::endl;

  pipeline->set_state(Gst::STATE_NULL);


  return 0;
}
