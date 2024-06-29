/*
 * action-unit.h
 *
 *  Created on: 16 de oct. de 2015
 *      Author: jseba
 */

#ifndef ACTION_UNIT_H_
#define ACTION_UNIT_H_

#include <distance-face-feature.h>

#include <vector>
#include <memory>

namespace insight {

/**
 * TODO: Some general documentation for class ActionUnit ...
 */
class ActionUnit {
public:
	static const double DEFAULT_CALIBRATION_DEVIATION;

	ActionUnit();

	ActionUnit(int code);

	virtual ~ActionUnit();

	void addFeature(DistanceFaceFeature feature);

	void addNoOccurrence(short code);

	void reset();

	void addPoints(std::vector<cv::Point> points);

	const int getNumberOfActiveFeatures() const;

	/* getters & setters */

	const short getCode() const {
		return code;
	}

	const std::vector<DistanceFaceFeature>& getFeatures() const {
		return features;
	}

	const std::vector<short>& getNoOccurrences() const {
		return noOccurrences;
	}

	void setNoOccurrences(const std::vector<short>& noOccurrences) {
		this->noOccurrences = noOccurrences;
	}

	bool isCalibrated() const {
		return calibrated;
	}

	void setCalibrated(bool calibrated) {
		this->calibrated = calibrated;
	}

private:
	short code;
	std::vector<DistanceFaceFeature> features;
	std::vector<short> noOccurrences;
	bool calibrated;
};

} /* namespace insight */

#endif /* ACTION_UNIT_H_ */
