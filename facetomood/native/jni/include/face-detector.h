/*
 * face-detector.h
 *
 *  Created on: 1 de oct. de 2015
 *      Author: jseba
 */

#ifndef FACE_DETECTOR_H_
#define FACE_DETECTOR_H_

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

namespace facetracker {

class FaceDetector {
public:
	/**
	 * Read face detector parameters from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	cv::Rect detect(cv::Mat &im);

	void reset();

private:

	void initCascade();

	int minNeighbours;
	int minSize;
	double imgScale;
	double scaleFactor;
	cv::CascadeClassifier * cascade;
	// CvMemStorage * storage;

	cv::Mat smallImage;
};

} /* namespace facetracker */

#endif /* FACE_DETECTOR_H_ */
