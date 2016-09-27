/*
 * utils.h
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#ifndef TESTS_INTEGRATION_UTILS_H_
#define TESTS_INTEGRATION_UTILS_H_

#include <gstreamermm.h>
#include <fstream>

void GenerateSampleOggFile(int num_buffers, const Glib::ustring& filename);
bool FilesEqual(const std::string& filename1, const std::string& filename2);
#endif /* TESTS_INTEGRATION_UTILS_H_ */
