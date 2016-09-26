/*
 * The example presents how to initialize gstreamermm, read
 * version of GStreamer, and use GStreamer option group together
 * with your application's option group.
 */
#include <gstreamermm.h>
#include <glibmm/optioncontext.h>

#include <iostream>

class MainOptionGroup : public Glib::OptionGroup
{
public:
  MainOptionGroup();

  bool version;
};

MainOptionGroup::MainOptionGroup()
: Glib::OptionGroup("main_group", "main group"),
  version(false)
{
  Glib::OptionEntry entry1;
  entry1.set_long_name("version");
  entry1.set_short_name('v');
  entry1.set_description("Show gstreamer version");
  add_entry(entry1, version);
}

static void print_gstreamer_version()
{
  guint major, minor, micro, nano;

  // Read GStreamer version
  Gst::version(major, minor, micro, nano);

  std::string nano_str;

  switch (nano) {
    case 1: nano_str = "(CSV)"; break;
    case 2: nano_str = "(Prerelease)"; break;
  }

  std::cout << "This program is linked against GStreamer "
      << major << "." << minor << "." << micro << "."
      << nano << " " << nano_str << std::endl;
}

int main (int argc, char *argv[])
{
  // Initialize gstreamermm
  Gst::init(argc, argv);

  Glib::OptionContext context("- gstreamermm init example");

  MainOptionGroup main_group;
  context.set_main_group(main_group);

  // Get GStreamer option group and add it to the context
  Glib::OptionGroup gst_group = Gst::get_option_group();
  context.add_group(gst_group);

  try
  {
    context.parse(argc, argv);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Failed to initialize: " << ex.what() << std::endl;
    return 1;
  }

  if (main_group.version)
  {
    print_gstreamer_version();
  }

  std::cout << "Run me with --help to see the Application options appended." << std::endl;

  return 0;
}
