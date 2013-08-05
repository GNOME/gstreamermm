/*
 * utils.h
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <gstreamermm.h>
#include <fstream>

void GenerateSampleOggFile(int num_buffers, const Glib::ustring& filename);
bool FilesEqual(const std::string& filename1, const std::string& filename2);
#endif /* UTILS_H_ */
