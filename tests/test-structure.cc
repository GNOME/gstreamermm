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

  structure[fieldName] = stringValue;

  Gst::StructureValueProxy testProxy = structure[fieldName];

  if (!testProxy) {
    std::cout << "No field named '" << fieldName << "' found." << std::endl;
  };

  if (testProxy) {
    Glib::ValueBase value;
    testProxy.get(value);
    std::cout << "Value type id = '" << typeid(value).name() <<
      "'" << std::endl;
  };

  return 0;
}
