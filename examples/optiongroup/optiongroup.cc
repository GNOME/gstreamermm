#include <gstreamermm.h>
#include <iostream>

Glib::OptionEntry make_entry(const Glib::ustring& long_name, const gchar& short_name, const Glib::ustring& description)
{
  Glib::OptionEntry m_OptionEntry;

  if (!long_name.empty())
    m_OptionEntry.set_long_name(long_name);
  if (short_name)
    m_OptionEntry.set_short_name(short_name);
  if (!description.empty())
    m_OptionEntry.set_description(description);

  return m_OptionEntry;
}

int main(int argc, char** argv)
{
  bool silent = false;
  std::string path;

  Glib::OptionGroup m_OptionGroup("name", "description", "help description");
  Glib::OptionContext m_OptionContext("- Your application");

  m_OptionGroup.add_entry(make_entry("silent", 's', "do not output status information"), silent);
  m_OptionGroup.add_entry_filename(make_entry("output", 'o', "save xml representation of pipeline to file and exit"), path);

  // We must initialise the threading system before using any other GLib function.
  // See Gstreamer's documentation for more info.
  if (!Glib::thread_supported ())
    Glib::thread_init ();

  m_OptionContext.set_main_group(m_OptionGroup);

  Glib::OptionGroup m_GstOptiongroup = Gst::init_get_option_group();
  m_OptionContext.add_group(m_GstOptiongroup);

  try
  {
    m_OptionContext.parse(argc, argv);
  }
  catch(const Glib::OptionError& error)
  {
    std::cout << "Failed to initialize: " << error.what() << std::endl;
    return 1;
  }

  std::cout << "Run me with --help to see the Application options appended.\n";
  return 0;
}
