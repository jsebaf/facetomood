/*
 * pdm.h
 *
 *  Created on: 1 de oct. de 2015
 *      Author: jseba
 */

#ifndef PDM_H_
#define PDM_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc_c.h>

namespace facetracker {

class PDM {
public:
	/**
	 * Read PDM from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	void clamp(cv::Mat &p, double c);

	void identity(cv::Mat &localParameters, cv::Mat &globalParameters);

	void calcShape3D(cv::Mat &shape, cv::Mat &localParameters);

	void calcShape2D(cv::Mat &shape, cv::Mat &localParameters,
			cv::Mat &globalParameters);

	void calcParams(cv::Mat &shape, cv::Mat &localParameters,
			cv::Mat &globalParameters);

	void calcRigidJacob(cv::Mat &localParameters, cv::Mat &globalParameters,
			cv::Mat &Jacob);

	void calcJacob(cv::Mat &localParameters, cv::Mat &globalParameters,
			cv::Mat &Jacob);

	void calcReferenceUpdate(cv::Mat &dp, cv::Mat &localParameters,
			cv::Mat &globalParameters);

	void applySimilarityTrasnform(double a, double b, double tx, double ty,
			cv::Mat &globalParameters);

	inline int numberOfPoints() {
		return M.rows / 3;
	}

	inline int numberOfModes() {
		return V.cols;
	}

	/* getters & setters */

	const cv::Mat& getV() const {
		return V;
	}

	const cv::Mat& getE() const {
		return E;
	}

	const cv::Mat& getM() const {
		return M;
	}

	const cv::Mat& getShape3D() const {
		return shape3D;
	}

private:
	cv::Mat V; /**< basis of variation                            */
	cv::Mat E; /**< vector of eigenvalues (row vector)            */
	cv::Mat M; /**< mean 3D shape vector [x1,..,xn,y1,...yn]      */

	cv::Mat shape3D;
	cv::Mat R, P, Px, Py, Pz, R1, R2, R3;

	void align3Dto2DShapes(double& scale, double& pitch, double& yaw,
			double& roll, double& x, double& y, cv::Mat &shape2D,
			cv::Mat &shape3D);
	void addOrthRow(cv::Mat &R);
	void rotationMatrix2Euler(cv::Mat &R, double& pitch, double& yaw,
			double& roll);
	void rotationMatrix2Euler(cv::Mat &R, cv::Mat &p);
	void euler2RotationMatrix(cv::Mat &R, const double pitch, const double yaw,
			const double roll, bool full = true);
	void euler2RotationMatrix(cv::Mat &R, cv::Mat &p, bool full = true);
	void metricUpgrade(cv::Mat &R);
};

} /* namespace facetracker */

#endif /* PDM_H_ */
