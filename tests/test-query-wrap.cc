#include <gstmm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  GstQuery* cquery = gst_query_new_position(GST_FORMAT_PERCENT);
  
  Glib::RefPtr<Gst::Query> query = Gst::Query::wrap(cquery);

  std::cout << "C++ query instance is !NULL: " << (bool)(query) << std::endl;

  Glib::RefPtr<Gst::QueryPosition> query_position = Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);
  std::cout << "query is a Gst::QueryPosition: " << (bool)query_position  << std::endl;
  std::cout << "query type name: '" << Gst::get_name(query->get_query_type()) << "'" << std::endl;

  return 0;
}
