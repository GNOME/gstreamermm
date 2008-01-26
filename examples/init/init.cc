#include <gstreamermm.h>
#include <iostream>

int main(int argc, char** argv)
{
  guint major, minor, micro;

  Gst::init(argc, argv);

  Gst::version(major, minor, micro);

  std::cout << "This program is linked against GStreamermm " << major << "." << minor << "." << micro << std::endl;

  return 0;
}
