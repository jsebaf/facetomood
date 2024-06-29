/*
 * person.h
 *
 *  Created on: 29 de sept. de 2015
 *      Author: jseba
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <memory>
#include <opencv2/opencv.hpp>
// #include <pose.h>

namespace insight {

/**
 * TODO: Some general documentation for class Person ...
 */
class Person {

public:
	Person();
	virtual ~Person();

	/**
	 * @return face rectangle.
	 */
	const cv::Rect& getFaceRect() const {
		return faceRect;
	} //!< Rectangle containing person face.

	/**
	 * @param faceRect face rectangle to set.
	 */
	void setFaceRect(const cv::Rect& faceRect) {
		this->faceRect = faceRect;
	}

	/**
	 * @return tracking points.
	 */
	const std::vector<cv::Point>& getTrackingPoints() const {
		return trackingPoints;
	} //!< Tracking points on frame reference.

	/**
	 * @param trackingPoints tracking points to set.
	 */
	void setTrackingPoints(const std::vector<cv::Point>& trackingPoints) {
		this->trackingPoints = trackingPoints;
	}

	/**
	 * @return tracking points.
	 */
	const std::vector<cv::Point>& getTrackingDeformationPoints() const {
		return trackingDeformationPoints;
	} //!< Tracking points on scaled person reference.

	/**
	 * @return point visibility array.
	 */
	const std::vector<bool>& getPointVisibility() const {
		return pointVisibility;
	}

	/**
	 * @param point visibility array to set.
	 */
	void setPointVisibility(const std::vector<bool>& pointVisibility) {
		this->pointVisibility = pointVisibility;
	} //!< Point visibility array.

	/**
	 * @param trackingDeformationPoints tracking points to set.
	 */
	void setTrackingDeformationPoints(
			const std::vector<cv::Point>& trackingDeformationPoints) {
		this->trackingDeformationPoints = trackingDeformationPoints;
	}

	/**
	 * @return deformation center point.
	 */
	const cv::Point& getDeformationCenter() const {
		return deformationCenter;
	} //!< Center point of scaled person reference.

	/**
	 * @param deformationCenter center point to set.
	 */
	void setDeformationCenter(const cv::Point& deformationCenter) {
		this->deformationCenter = deformationCenter;
	}

	/**
	 * @return vector of detected Action Unit probabilities.
	 */
	const std::vector<double>& getDetectedActionUnits() const {
		return detectedActionUnits;
	} //!< Vector of detected Action Unit probabilities.

	/**
	 * @param actionUnitCodes vector of detected Action Units to set.
	 */
	void setDetectedActionUnits(const std::vector<double>& actionUnitCodes) {
		this->detectedActionUnits = actionUnitCodes;
	}

	/**
	 * @return vector of detected mood probabilities.
	 */
	const std::vector<double>& getDetectedMoods() const {
		return detectedMoods;
	} //!< Vector of detected mood probabilities.
	/**
	 * @param Vector of detected mood probabilities to set.
	 */
	void setDetectedMoods(std::vector<double>& detectedMoods) {
		this->detectedMoods = detectedMoods;
	}

	/**
	 * @return pose angles.
	 */
	// const Pose getPose() const {
	//	return pose;
	// } //!< Vector of pose angles.
	/**
	 * @param Vector of pose angles to set.
	 */
	// void setPose(Pose& pose) {
	//	this->pose = pose;
	// }

	double getExpressivity() const {
		return expressivity;
	}

	void setExpressivity(double expressivity) {
		this->expressivity = expressivity;
	}

private:
	cv::Rect faceRect;
	std::vector<cv::Point> trackingPoints;
	std::vector<cv::Point> trackingDeformationPoints;
	std::vector<bool> pointVisibility;
	cv::Point deformationCenter;
	// Pose pose;
	std::vector<double> detectedActionUnits;
	double expressivity;
	std::vector<double> detectedMoods;
};

} /* namespace insight */

#endif /* PERSON_H_ */
