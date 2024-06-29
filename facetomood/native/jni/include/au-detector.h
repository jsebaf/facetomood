/*
 * au-detector.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: jseba
 */

#ifndef AU_DETECTOR_H_
#define AU_DETECTOR_H_

#include <action-unit.h>

#include <opencv2/opencv.hpp>
#include <vector>

namespace insight {

struct DetectedActionUnit {

	DetectedActionUnit(short code, double probability) :
			code(code), probability(probability) {
	}

	short code;
	double probability;
};

class AUDetector {

public:
	static const int DEFAULT_AU_DETECTION_WINDOW_SIZE = 4;
	static const int DEFAULT_AU_VIEWS_FOR_DETECTION = 3;

	AUDetector();
	virtual ~AUDetector();

	void load(const char * fileName);

	std::vector<DetectedActionUnit> detect(std::vector<cv::Point> points);

	void reset();

	/* getters & setters */

	const std::vector<ActionUnit>& getActionUnits() const {
		return actionUnits;
	}

	bool isCalibrated() const {
		return calibrated;
	}

	unsigned long getStatsBufferLength() const {
		return statsBufferLength;
	}

	void setStatsBufferLength(unsigned long statsBufferLength) {
		this->statsBufferLength = statsBufferLength;
	}

private:
	std::vector<ActionUnit> actionUnits;
	std::map<short, int> lastDetected;
	int auDetectionWindowSize, auViewsForDetection;
	unsigned long statsBufferLength;
	bool calibrated;

	std::vector<short> stringToVector(std::string& segmentStr);
};

} /* namespace insight */

#endif /* AU_DETECTOR_H_ */
