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
#include <gst/gstbin.h>
#include <gst/gsterror.h>
#include <iostream>

int main(int argc, char** argv)
{
  Gst::init(argc, argv);

  GstObject* cobject = GST_OBJECT (gst_bin_new("test"));
  GError* cerror = g_error_new_literal(GST_CORE_ERROR, GST_CORE_ERROR_FAILED, "test error message");
  GstMessage* cmessage = gst_message_new_warning(cobject, cerror, "test debug text");
  
  Glib::RefPtr<Gst::Message> message = Gst::Message::wrap(cmessage);

  std::cout << "C++ message instance is !null: " << (bool)(message) << std::endl;

  Glib::RefPtr<Gst::MessageWarning> message_warning = Glib::RefPtr<Gst::MessageWarning>::cast_dynamic(message);
  std::cout << "message is a Gst::MessageWarning: " << (bool)message_warning  << std::endl;
  std::cout << "message type name: '" << Gst::Enums::get_name(message->get_message_type()) << "'"  << std::endl;

  const Gst::Structure structure = message->get_structure();
  if(structure)
    std::cout << "Message structure name: '" << structure.get_name() << "'" << std::endl;

  // Test the creation of a message.
  Glib::RefPtr<Gst::Bin> bin = Glib::wrap(GST_BIN(cobject));
  Glib::RefPtr<Gst::MessageEos> eos = Gst::MessageEos::create(bin);
  if(!eos)
    std::cout << "The custom eos message could not be created" << std::endl;
  else
    std::cout << "The custom eos message was successfully created" << std::endl;

  return 0;
}
