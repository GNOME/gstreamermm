#include <gstreamermm.h>
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv)
{
  Glib::RefPtr<Gst::Pipeline> m_Pipeline;
  Glib::RefPtr<Gst::Element> m_Element_Source, m_Element_Filter, m_Element_Sink;

  // init Gstreamermm
  Gst::init(argc, argv);

  // create pipeline
  m_Pipeline = Gst::Pipeline::create("my-pipeline");

  // create elements
  try
  {
    m_Element_Source = Gst::Element::create("fakesrc", "source");
    m_Element_Filter = Gst::Element::create("identity", "filter");
    m_Element_Sink = Gst::Element::create("fakesink", "sink");
  }
  catch(std::runtime_error& error)
  {
    std::cout << error.what();
  }

  // we must add the elements to the pipeline before linking them
  m_Pipeline->add(m_Element_Source)->add(m_Element_Filter)->add(m_Element_Sink);

  // link
  try
  {
    m_Element_Source->link(m_Element_Filter)->link(m_Element_Sink);
  }
  catch(std::runtime_error& error)
  {
    std::cout << error.what();
  }

  return 0;
}
