/*
 * test-regression-bininpipeline.cc
 *
 *  Created on: 5 sie 2013
 *      Author: loganek
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <gstreamermm/filesrc.h>
#include <gstreamermm/filesink.h>
#include <glibmm.h>

using namespace Gst;
using Glib::RefPtr;

class CustomBin : public Bin
{
private:
    RefPtr<FileSrc> source_file;
    RefPtr<Element> png_decoder;
    RefPtr<GhostPad> src_pad;
protected:
    explicit CustomBin(const Glib::ustring& name)
    : Bin(name)
    {
        source_file = FileSrc::create("source-file");
        png_decoder = ElementFactory::create_element("pngdec");

        add(source_file);
        add(png_decoder);
        source_file->link(png_decoder);

        src_pad = add_ghost_pad(png_decoder, "src", "src");
        src_pad->set_active(true);
    }
public:
    virtual ~CustomBin() {}

    static RefPtr<CustomBin> create(const Glib::ustring& name)
    {
        return RefPtr<CustomBin>(new CustomBin(name));
    }

    void set_location(const Glib::ustring& filename)
    {
        source_file->property_location() = filename;
    }
};

RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
    switch(message->get_message_type())
    {
        case MESSAGE_EOS:
            mainloop->quit();
            return false;
        case MESSAGE_ERROR:
        {
            mainloop->quit();
            return false;
        }
        default:
            break;
    }

    return true;
}

TEST(BinInPipelineRegressionTest, CustomBinShouldCorrectEncodeImageAndOtherElementsShouldEncodeItToJPGAndWriteToFile)
{
    Glib::ustring input_png = "resources/input-image.png",
            output_jpg = "resources/test-regression-bininpipeline-output-image.jpg";

    mainloop = Glib::MainLoop::create();
    ASSERT_TRUE(mainloop);
    RefPtr<CustomBin> custom_bin = CustomBin::create("file-png-decoder");
    ASSERT_TRUE(custom_bin);
    RefPtr<Element> jpg_encoder = ElementFactory::create_element("jpegenc");
    ASSERT_TRUE(jpg_encoder);
    RefPtr<FileSink> file_sink = FileSink::create("file-sink");
    ASSERT_TRUE(file_sink);
    RefPtr<Pipeline> pipeline = Pipeline::create("image-converter-pipeline");
    ASSERT_TRUE(custom_bin);

    ASSERT_NO_THROW(pipeline->add(custom_bin)->add(jpg_encoder)->add(file_sink));
    ASSERT_NO_THROW(custom_bin->link(jpg_encoder)->link(file_sink));

    Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
    ASSERT_TRUE(bus);
    bus->add_watch(sigc::ptr_fun(&on_bus_message));

    custom_bin->set_location(input_png);

    file_sink->property_location() = output_jpg;

    pipeline->set_state(STATE_PLAYING);
    mainloop->run();

    pipeline->set_state(Gst::STATE_NULL);
}
