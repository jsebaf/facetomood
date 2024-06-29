/*
 * distance-face-feature.h
 *
 *  Created on: 22 de oct. de 2015
 *      Author: jseba
 */

#ifndef DISTANCE_FACE_FEATURE_H_
#define DISTANCE_FACE_FEATURE_H_

#include <face-feature.h>
#include <circular.h>

namespace insight {

/**
 * TODO: Some general documentation for class DistanceFaceFeature ...
 */
class DistanceFaceFeature: public FaceFeature {
public:
	static const int DEFAULT_STATS_BUFFER_LENGTH = 50; // MMI test = 25, Inisle test = 100
	static const int DETECTION_BUFFER_LENGTH = 1;

	static const double DEFAULT_THRESHOLD;

	enum Mode {
		EXPAND, COMPRESS, POSITIVE, NEGATIVE
	};

	enum Type {
		POINT_TO_POINT,
		POINT_TO_SEGMENT,
		SEGMENT_TO_SEGMENT,
		X_DISTANCE,
		Y_DISTANCE
	};

	DistanceFaceFeature(short point1, short point2, Type type, double threshold,
			Mode mode);

	DistanceFaceFeature(short point1, std::vector<short> segment1,
			double threshold, Mode mode);

	DistanceFaceFeature(std::vector<short> segment1,
			std::vector<short> segment2, double threshold, Mode mode);

	virtual ~DistanceFaceFeature();

	void init();

	void addValue(cv::Point point1, cv::Point point2);

	void addValue(cv::Point point1, std::vector<cv::Point> segment1);

	void addValue(std::vector<cv::Point> segment1,
			std::vector<cv::Point> segment2);

	void clearValues();

	const int getNumberOfReferenceValues() const;

	virtual double isActive() const;

	double getPreviousValue() const;

	/* getters & setters */

	short getPoint1() const {
		return point1;
	}

	short getPoint2() const {
		return point2;
	}

	double getReferenceMean() const {
		return referenceMean;
	}

	double getReferenceStdDev() const {
		return referenceStdDev;
	}

	double getLastValue() const {
		return lastValue;
	}

	bool isCalibrated() const {
		return calibrated;
	}

	void setCalibrated(bool calibrated) {
		this->calibrated = calibrated;
	}

	const std::vector<short>& getSegment1() const {
		return segment1;
	}

	void setSegment1(const std::vector<short>& segment1) {
		this->segment1 = segment1;
	}

	const std::vector<short>& getSegment2() const {
		return segment2;
	}

	void setSegment2(const std::vector<short>& segment2) {
		this->segment2 = segment2;
	}

	double getThreshold() const {
		return threshold;
	}

	void setThreshold(double threshold) {
		this->threshold = threshold;
	}

	Type getType() const {
		return type;
	}

	void setType(Type type) {
		this->type = type;
	}

	long getStatsBufferLength() const {
		return statsBufferLength;
	}

	void setStatsBufferLength(unsigned long statsBufferLength) {
		this->statsBufferLength = statsBufferLength;
	}

	Mode getMode() const {
		return mode;
	}

	void setMode(Mode mode) {
		this->mode = mode;
	}

private:
	short point1, point2;
	std::vector<short> segment1;
	std::vector<short> segment2;
	double threshold;
	Mode mode;
	Type type;
	unsigned long statsBufferLength;

	double lastValue;
	double referenceMean, referenceStdDev;
	circular_buffer<double> values;
	bool calibrated;

	void updateReference();
	std::vector<double> lineEquation(cv::Point& p1, cv::Point& p2);
};

} /* namespace insight */

#endif /* DISTANCE_FACE_FEATURE_H_ */
