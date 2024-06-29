/*
 * insight.h
 *
 *  Created on: 29 de sept. de 2015
 *      Author: jseba
 */

#ifndef INSIGHT_H_
#define INSIGHT_H_

#include <person.h>
#include <action-unit.h>
#include <mood.h>
#include <mood-level.h>
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

namespace insight {

class InsightImpl;

union Option {
	bool b;
	int i;
	double d;
};

/**
 * TODO: Some general documentation for class Insight ...
 */
class Insight {
public:
	/**
	 * \param[in] dataDir Path to the directory containing SDK resource files.
	 */
	Insight(const char * dataDir = "../data/"); //!< Instantiate the SDK.

	~Insight();

	const std::string getVersion() const; //!< Returns de current version number of the SDK.
	bool init(cv::Mat inImage); //!< Initializes SDK. Must be called once before anything else.
	bool process(cv::Mat inImage); //!< Processes a frame. On success true is returned. If true Insight::getPerson() object is valid.

	const Person & getPerson() const; //!< Retrieves person being processed.

	void resetTracker(); //!< Resets tracker state. Point tracker and AU detector are reinitialized.

	const std::vector<ActionUnit>& getActionUnits() const; //!< Get list of Action Units being tracked.

	const std::vector<MoodLevel>& getMoodLevels() const; //!< Get list of defined moods levels.

	const std::vector<Mood>& getMoods() const; //!< Get list of moods being tracked.

	bool isCalibrated() const; //!< Returns calibration status of internal detectors.

	const cv::Mat& getConnections() const;

	const cv::Mat& getTriangulations() const;

	void setOption(std::string key, Option option);

	void setDebug(bool debug);
private:
	std::unique_ptr<InsightImpl> pimpl;
};

} /* namespace insight */

#endif /* INSIGHT_H_ */
