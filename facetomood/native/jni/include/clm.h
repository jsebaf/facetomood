/*
 * clm.h
 *
 *  Created on: 1 de oct. de 2015
 *      Author: jseba
 */

#ifndef CLM_H_
#define CLM_H_

#include <istream>
#include <pdm.h>
#include <multi-patch.h>

namespace facetracker {

class CLM {
public:
	/**
	 * Read CLM from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	void fit(cv::Mat image, std::vector<int> &windowSizes, int iterationNumber =
			10, double clamp = 3.0, double optimizationTolerance = 0.0);

	int getViewIndex() const;

	/* getters & setters */

	const PDM& getPdm() const {
		return pdm;
	}

	cv::Mat& getGlobalParams() {
		return globalParams;
	}

	cv::Mat& getLocalParams() {
		return localParams;
	}

	const std::vector<cv::Mat>& getVisibility() const {
		return visibility;
	}

private:
	PDM pdm; /**< 3D Shape model */

	cv::Mat localParams; /**< local parameters */
	cv::Mat globalParams; /**< global parameters */
	cv::Mat referenceShape; /**< Reference shape */
	std::vector<cv::Mat> centers; /**< Centers/view (Euler) */
	std::vector<cv::Mat> visibility; /**< Visibility for each view */
	std::vector<std::vector<MultiPatch> > patches; /**< Patches/point/view */

	cv::Mat backedShape, u, g, J, H;
	std::vector<cv::Mat> prob, pmem, wmem;

	void optimize(int idx, int windowSize, int nIter,
			double optimizationTolerance, double clamp, bool rigid);

	void calcSimilarityTransform(cv::Mat &src, cv::Mat &dst, double &a, double &b, double &tx,
			double &ty);
	void invertSimilarityTransform(double a1, double b1, double tx1, double ty1, double& a2,
			double& b2, double& tx2, double& ty2);
	void similarityTransform(cv::Mat &s, double a, double b, double tx, double ty);
};

} /* namespace facetracker */

#endif /* CLM_H_ */
