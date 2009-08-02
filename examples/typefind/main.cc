/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2009 The gstreamermm Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <gstreamermm.h>
#include <iostream>

Glib::RefPtr<Glib::MainLoop> mainloop;
bool have_type = false;

static void on_typefind_have_type(guint probability, const Glib::RefPtr<Gst::Caps>& caps)
{
  have_type = true;

  std::cout << "have-type: probability=" << probability << std::endl;

  if(!caps)
  {
    std::cerr << "on_typefind_have_type(): caps is null" << std::endl;
    return;
  }

  const Gst::Structure structure = caps->get_structure(0);
  const Glib::ustring mime_type = structure.get_name();
  std::cout << "have-type: mime_type=" << mime_type << std::endl;

  if(mainloop)
    mainloop->quit();
  else
    std::cerr << "on_typefind_have_type(): mainloop is null" << std::endl;
}

int main(int argc, char** argv)
{
  // Initialize Gstreamermm:
  Gst::init(argc, argv);

  //Check input arguments:
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return -1;
  }

  const std::string filename = argv[1];

  // Create pipeline:
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my-pipeline");

  // Create elements:
  Glib::RefPtr<Gst::FileSrc> element_source = Gst::FileSrc::create();
  element_source->property_location() = filename;

  Glib::RefPtr<Gst::TypeFindElement> element_typefind = Gst::TypeFindElement::create();
  element_typefind->signal_have_type().connect(
    sigc::ptr_fun(&on_typefind_have_type) );
  Glib::RefPtr<Gst::Element> element_sink = Gst::FakeSink::create();

  // We must add the elements to the pipeline before linking them:
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    pipeline->add(element_source)->add(element_typefind)->add(element_sink);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch (std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }
#endif

  // Link the elements together:
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    element_source->link(element_typefind)->link(element_sink);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(const std::runtime_error& error)
  {
    std::cerr << "Exception while linking: " << error.what() << std::endl;
  }
#endif

  // Now set the whole pipeline to playing and start the main loop:
  std::cout << "Setting pipeline to PLAYING." << std::endl;
  mainloop = Glib::MainLoop::create();
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Pipeline is playing." << std::endl;
  if(!have_type)
    mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Stopping pipeline." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}
