/*
 * face-feature.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: jseba
 */

#ifndef FACE_FEATURE_H_
#define FACE_FEATURE_H_

#include <opencv2/opencv.hpp>

namespace insight {

class FaceFeature {
public:
	FaceFeature();
	virtual ~FaceFeature();

	virtual double isActive() const = 0;
};

} /* namespace insight */

#endif /* FACE_FEATURE_H_ */
