/*
 * mood-detector.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: jseba
 */

#ifndef MOOD_DETECTOR_H_
#define MOOD_DETECTOR_H_

#include <dom-support.h>
#include <mood.h>
#include <mood-level.h>
#include <au-detector.h>
#include <vector>
#include <map>
#include <circular.h>

namespace insight {

class MoodDetector {
public:
	const int MOOD_DETECT_THRESHOLD = 3;
	const int ACTION_UNIT_DETECTION_BUFFER_SIZE = (1500 * 5); // minutes, 25 frames = 1s. 1500 frames = 1minute

	MoodDetector();
	virtual ~MoodDetector();

	void load(const char * fileName);

	std::vector<double> detect(
			std::vector<DetectedActionUnit>& detectedaAtionUnits);

	/* getters & setters */

	const std::vector<Mood>& getMoods() const {
		return moods;
	}

	void setAuDetector(const AUDetector * auDetector) {
		this->auDetector = auDetector;
	}

	const std::vector<double>& getAccumulatedAUs() const {
		return accumulatedAUs;
	}

	const std::vector<double>& getAuDetectionRates() const {
		return auDetectionRates;
	}

	const std::vector<MoodLevel>& getMoodLevels() const {
		return moodLevels;
	}

private:
	const AUDetector * auDetector;

	std::vector<Mood> moods;

	std::vector<double> accumulatedAUs;

	std::vector<double> auDetectionRates;

	std::vector<MoodLevel> moodLevels;

	std::map<short, circular_buffer<double>> auDetectionBufferMap;
	unsigned short auDetectionWindow;

	long auDetectionBufferMapSize;

	std::vector<Mood> loadLevel(xml::XMLElement * levelElement);

	void updateAUDetectionBufferMap(std::vector<DetectedActionUnit>& detectedActionUnits);

	void accumulateAUDetectionBufferMap();

	std::vector<double> normalize(std::vector<double>& input);
};

} /* namespace insight */

#endif /* MOOD_DETECTOR_H_ */
