/*
 * io.h
 *
 *  Created on: 1 de oct. de 2015
 *      Author: jseba
 */

#ifndef FT_IO_H_
#define FT_IO_H_

#include <istream>
#include <opencv2/opencv.hpp>

namespace facetracker {

class IO {
public:
	enum {
		PDM = 0, PAW, PATCH, MPATCH, CLM, FDET, FCHECK, MFCHECK, TRACKER
	};

	static void readMat(std::istream& s, cv::Mat &mat);
	static cv::Mat loadTriangulation(const char* fileName);
	static cv::Mat loadTriangulation(std::istream& s);
  static cv::Mat loadConnections(const char* fileName);
	static cv::Mat loadConnections(std::istream& s);
};

} /* namespace facetracker */

#endif /* FT_IO_H_ */
