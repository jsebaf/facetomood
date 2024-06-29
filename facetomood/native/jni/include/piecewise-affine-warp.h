/*
 * piecewise-affine-warp.h
 *
 *  Created on: 2 de oct. de 2015
 *      Author: jseba
 */

#ifndef PIECEWISE_AFFINE_WARP_H_
#define PIECEWISE_AFFINE_WARP_H_

#include <istream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

namespace facetracker {

class PiecewiseAffineWarp {
public:
	/**
	 * Read piecewise affine warp from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	void crop(cv::Mat &src, cv::Mat &dst, cv::Mat &s);

	/* getters & setters */

	int getNumberOfPixels() const {
		return numberOfPixels;
	}

	const cv::Mat& getMask() const {
		return mask;
	}

private:

	int numberOfPixels; /**< Number of pixels */
	double xMin; /**< Minimum x-coord for src */
	double yMin; /**< Minimum y-coord for src */
	cv::Mat src; /**< Source points */
	cv::Mat dst; /**< Destination points */
	cv::Mat triangulation; /**< Triangulation */
	cv::Mat triangle; /**< Triangle for each valid pixel */
	cv::Mat mask; /**< Valid region mask */
	cv::Mat affineCoefficients; /**< affine coeffs for all triangles */
	cv::Mat alpha; /**< matrix of (c,x,y) coeffs for alpha */
	cv::Mat beta; /**< matrix of (c,x,y) coeffs for alpha */
	cv::Mat mapX; /**< x-destination of warped points */
	cv::Mat mapY; /**< y-destination of warped points */

	void calcCoeff();
	void warpRegion(cv::Mat &mapx, cv::Mat &mapy);
	inline int numberOfPoints() {
		return src.rows / 2;
	}
	inline int numberOfTriangles() {
		return triangulation.rows;
	}
};

} /* namespace facetracker */

#endif /* PIECEWISE_AFFINE_WARP_H_ */
