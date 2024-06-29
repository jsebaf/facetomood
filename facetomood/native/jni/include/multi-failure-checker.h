/*
 * multi-failure-checker.h
 *
 *  Created on: 2 de oct. de 2015
 *      Author: jseba
 */

#ifndef MULTI_FAILURE_CHECKER_H_
#define MULTI_FAILURE_CHECKER_H_

#include <istream>
#include <vector>
#include <failure-checker.h>

namespace facetracker {

class MultiFailureChecker {
public:
	/**
	 * Read multi failure checker from file stream
	 * @param s				File input stream.
	 * @return       		false on failure.
	 */
	void read(std::istream &s);

	bool check(int index, cv::Mat &im, cv::Mat &s);

private:
	std::vector<FailureChecker> failureCheckers; /**< Failure checkers for each view */
};

} /* namespace facetracker */

#endif /* MULTI_FAILURE_CHECKER_H_ */
