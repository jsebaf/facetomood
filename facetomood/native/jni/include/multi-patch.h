/*
 * multi-patch.h
 *
 *  Created on: 2 de oct. de 2015
 *      Author: jseba
 */

#ifndef MULTI_PATCH_H_
#define MULTI_PATCH_H_

#include <vector>
#include <opencv2/opencv.hpp>
#include <patch.h>

namespace facetracker {

class MultiPatch {
public:
	/**
	 * Read multi patch from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	void buildResponse(cv::Mat &image, cv::Mat &response);

	int getHeight() const {
		return height;
	}

	const cv::Mat& getResponse() const {
		return response;
	}

	int getWidth() const {
		return width;
	}

private:
	int width, height; /**< Width and height of patch */
	std::vector<Patch> patches; /**< List of patches */

	cv::Mat response;

	void sum2one(cv::Mat &M);
};

} /* namespace facetracker */

#endif /* MULTI_PATCH_H_ */
