/*
 * mood-level.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: jseba
 */

#ifndef MOOD_LEVEL_H_
#define MOOD_LEVEL_H_

#include <mood.h>
#include <string>
#include <vector>

namespace insight {

/**
 * TODO: Some general documentation for class MoodLevel ...
 */
class MoodLevel {
public:

	MoodLevel(std::string name);
	virtual ~MoodLevel();

	/* getters & setters */

	const std::string& getName() const {
		return name;
	}

	const std::vector<Mood>& getMoods() const {
		return moods;
	}

	void setMoods(const std::vector<Mood>& moods) {
		this->moods = moods;
	}

private:
	std::string name;
	std::vector<Mood> moods;
};

} /* namespace insight */

#endif /* MOOD_LEVEL_H_ */
