#include <gstreamermm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::ustring fieldName = "field";
  Glib::RefPtr<Gst::Query> latencyQuery = Gst::QueryLatency::create();
  Gst::Structure structure = latencyQuery->get_structure();

  Glib::Value<Glib::ustring> stringValue;
  stringValue.init(Glib::Value<Glib::ustring>::value_type());
  stringValue.set("Hello; This is a ustring.");

  structure.set_field(fieldName, stringValue);

  Glib::Value<Glib::ustring> value;
  structure.get_field(fieldName, value);
  std::cout << "value = '" << value.get() << "'" << std::endl;

  return 0;
}
