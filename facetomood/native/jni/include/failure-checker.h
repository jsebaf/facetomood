/*
 * failure-checker.h
 *
 *  Created on: 2 de oct. de 2015
 *      Author: jseba
 */

#ifndef FAILURE_CHECKER_H_
#define FAILURE_CHECKER_H_

#include <istream>
#include <piecewise-affine-warp.h>

namespace facetracker {

class FailureChecker {
public:

	/**
	 * Read failure checker from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	bool check(cv::Mat &image, cv::Mat &shape);

private:
	PiecewiseAffineWarp piecewiseAffineWarp; /**< Piecewise affine warp */
	double bias; /**< SVM bias */
	cv::Mat gain; /**< SVM gain */

	cv::Mat crop, vec;
};

} /* namespace facetracker */

#endif /* FAILURE_CHECKER_H_ */
