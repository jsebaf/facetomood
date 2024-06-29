/*
 * pose.h
 *
 *  Created on: 29/06/2014
 *      Author: jseba
 */

#ifndef POSE_H_
#define POSE_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

namespace insight {

class Pose {
public:
	Pose();

	Pose(std::vector<CvPoint3D32f>& modelPoints,
			std::vector<CvPoint2D32f>& viewPoints);
	virtual ~Pose();

	bool isFrontal();

	friend std::ostream& operator<<(std::ostream & os, const Pose& v);

	/* getters & setters */

	float* getRotationMatrix() const {
		return rotationMatrix;
	}

	void setRotationMatrix(float* rotationMatrix) {
		this->rotationMatrix = rotationMatrix;
	}

	float* getTranslationVector() const {
		return translationVector;
	}

	void setTranslationVector(float* translationVector) {
		this->translationVector = translationVector;
	}

	double getPitch() const {
		return pitch;
	}

	void setPitch(double pitch) {
		this->pitch = pitch;
	}

	double getRoll() const {
		return roll;
	}

	void setRoll(double roll) {
		this->roll = roll;
	}

	double getYaw() const {
		return yaw;
	}

	void setYaw(double yaw) {
		this->yaw = yaw;
	}

private:
	float * rotationMatrix;
	float * translationVector;
	double yaw, roll, pitch;
	CvPoint3D32f originPoint3D;
	CvPoint3D32f baseIPoint3D;
	CvPoint3D32f baseJPoint3D;
	CvPoint3D32f baseKPoint3D;
};

} /* namespace insight */

#endif /* POSE_H_ */
