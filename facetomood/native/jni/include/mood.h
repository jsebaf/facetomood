/*
 * mood.h
 *
 *  Created on: 3 de nov. de 2015
 *      Author: jseba
 */

#ifndef MOOD_H_
#define MOOD_H_

#include <string>
#include <vector>

namespace insight {

/**
 * TODO: Some general documentation for class Mood ...
 */
class Mood {
public:
	/**
	 * \param[in] code Mood code.
	 *
	 * \param[in] label Mood label.
	 */
	Mood(short code, std::string label);
	virtual ~Mood();

	void addActionUnitCode(short code);

	/* getters & setters */

	const std::vector<short>& getActionUnitCodes() const {
		return actionUnitCodes;
	}

	short getCode() const {
		return code;
	}

	const std::string& getLabel() const {
		return label;
	}

	const std::vector<double>& getBase() const {
		return base;
	}

	void setBase(const std::vector<double>& base) {
		this->base = base;
	}

private:
	short code;
	std::string label;
	std::vector<short> actionUnitCodes;
	std::vector<double> base;
};

} /* namespace insight */

#endif /* MOOD_H_ */
