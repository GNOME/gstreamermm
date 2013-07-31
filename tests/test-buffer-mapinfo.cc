/*
 * test-buffer-mapinfo.cc
 *
 *  Created on: Jul 31, 2013
 *      Author: m.kolny
 */

#include <gstreamermm.h>
#include <assert.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Gst::init(argc, argv);
    int buffer_size = 15;
    cout << "Creating buffer..." << endl;
    Glib::RefPtr<Gst::Buffer> buffer = Gst::Buffer::create(buffer_size);
    Gst::MapInfo mapinfo ;
    Gst::MapFlags flags;

    buffer->map(&mapinfo, flags);

    assert(mapinfo.get_size() == buffer_size);

    cout << "Correct!" << endl;
}
