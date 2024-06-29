/*
 * patch.h
 *
 *  Created on: 2 de oct. de 2015
 *      Author: jseba
 */

#ifndef PATCH_H_
#define PATCH_H_

#include <istream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

namespace facetracker {

class Patch {
public:
	/**
	 * Read patch from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	void buildResponse(cv::Mat &image, cv::Mat &response);

private:
	int type; /**< Type of patch (0=raw,1=grad,2=lbp) */
	double scaling; /**< scaling */
	double bias; /**< bias */
	cv::Mat Gain; /**< Gain */

	cv::Mat image, res;

	void grad(cv::Mat im,cv::Mat grad);
	void LBP(cv::Mat im,cv::Mat lbp);
};

} /* namespace facetracker */

#endif /* PATCH_H_ */
