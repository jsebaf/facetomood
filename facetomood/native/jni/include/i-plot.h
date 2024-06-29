/*
 * plot.h
 *
 *  Created on: 12 de nov. de 2015
 *      Author: jseba
 */

#ifndef I_PLOT_H_
#define I_PLOT_H_

#include <opencv2/opencv.hpp>
#include <boost/circular_buffer.hpp>
#include <string>

namespace insight {

class Plot {
public:
	Plot(std::string title, int width, int height);

	void add(double yValue);

	void draw();

	/* getters & setters */

	double getMax() const {
		return max;
	}

	void setMax(double max) {
		this->max = max;
	}

	double getMin() const {
		return min;
	}

	void setMin(double min) {
		this->min = min;
	}

	double getThreshold() const {
		return threshold;
	}

	void setThreshold(double threshold) {
		this->threshold = threshold;
	}

	double getBound() const {
		return bound;
	}

	void setBound(double bound) {
		this->bound = bound;
	}

private:
	static const int BORDER_WIDTH = 40;

	cv::Point toCanvas(double x, double y);

	void drawGrid();

	void drawDottedLine(cv::Point p1, cv::Point p2, int thikness, cv::Scalar color = CV_RGB(0, 0, 0));

	std::string title;
	int width, height;
	double min, max;
	double threshold;
	double bound;
	cv::Mat canvas;
	boost::circular_buffer<double> yValues;
};

} /* namespace insight */

#endif /* I_PLOT_H_ */
