/*
 * insight-impl.h
 *
 *  Created on: 9 de oct. de 2015
 *      Author: jseba
 */

#ifndef INSIGHT_IMPL_H_
#define INSIGHT_IMPL_H_

#include <insight-config.h>
#include <insight.h>
#include <tracker.h>
#include <person.h>
#include <au-detector.h>
#include <mood-detector.h>
#include <map>

namespace insight {

class InsightImpl {
public:
	InsightImpl(const char * dataDir = "../data/");

	const std::string getVersion() const;
	bool init(cv::Mat inImage);
	bool process(cv::Mat inImage);
	void resetTracker();

	const Person& getPerson() const {
		return person;
	}

	const std::vector<ActionUnit>& getActionUnits() const;

	const std::vector<MoodLevel>& getMoodLevels() const;

	const std::vector<Mood>& getMoods() const;

	bool isCalibrated() const;

	const cv::Mat& getConnections() const {
		return connections;
	}

	const cv::Mat& getTriangulations() const {
		return triangulations;
	}

	void setOption(std::string key, Option option);

	void setDebug(bool debug) {
		this->debug = debug;
		tracker.setDebug(debug);
	}

private:
	bool loadConfig();
	cv::Point2f rotate2d(const cv::Point2f& p, const cv::Point center,
			double a);

	std::string dataDir;
	std::map<std::string, Option> options;
	facetracker::Tracker tracker;
	AUDetector auDetector;
	MoodDetector moodDetector;
	Person person;
	cv::Mat triangulations, connections;
	std::vector<CvPoint3D32f> modelPoints;

	int imageCenterX, imageCenterY;

	bool debug;
};

} /* namespace insight */

#endif /* INSIGHT_IMPL_H_ */
