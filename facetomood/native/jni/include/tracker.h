/*
 * tracker.h
 *
 *  Created on: 1 de oct. de 2015
 *      Author: jseba
 */

#ifndef TRACKER_H_
#define TRACKER_H_

#include <istream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include <clm.h>
#include <face-detector.h>
#include <multi-failure-checker.h>

namespace facetracker {

class Tracker {
public:
  enum Status { DETECTING_FACE, ON_TRACKING };

  Tracker()
      : frameCounter(-1), consecutiveFaceDetections(0),
        minimumConsecutiveFaceDetections(4), poseStabilityCounter(0),
        minumumPoseStabilityCounter(0), debug(false) {}

  /**
   * Load tracker from model file
   * @param modelFile		Model file name.
   * @return         false on failure.
   */
  bool load(const char *modelFile);

  bool load();

  /**
   * Read tracking model from file stream
   * @param s				File input stream.
   * @return         false on failure.
   */
  void read(std::istream &s);

  /**
   * Track model in current frame
   * @param image        Image containing face
   * @param windowSizes     List of search window sizes (set from large to
   * small)
   * @param framesPerDetection    Number of frames between detections (-1:
   * never)
   * @param iterationNumber    Maximum number of optimization steps to perform
   * @param clamp      Shape model parameter clamping factor (in standard dev's)
   * @param optimizationTolerance Convergence tolerance of optimization
   * @return           false on failure.
   */
  bool track(cv::Mat &image, std::vector<int> &windowSizes,
             const int framesPerDetection = -1, const int iterationNumber = 10,
             const double clamp = 3.0,
             const double optimizationTolerance = 0.01);

  void frameCounterReset(bool hard = false) {
    frameCounter = -1;
    if (hard) {
      if (debug)
        std::cout << "hard reset" << std::endl;
      consecutiveFaceDetections = 0;
      minimumConsecutiveFaceDetections += 1;
    }
  }

  void faceDetectorReset() {
		faceDetector.reset();
	}

  const cv::Mat &getDeformationShape() { return shapePDM; }

  const Status getStatus();

  /* getters & setters */

  int64 getFrameCounter() const { return frameCounter; }

  const CLM &getClm() const { return clm; }

  const cv::Mat &getShape() const { return shape; }

  const cv::Rect &getStoredRect() const { return storedRect; }

  void setDebug(bool debug) { this->debug = debug; }

private:
  CLM clm;                   /**< Constrained Local Model */
  FaceDetector faceDetector; /**< Face Detector */
  int64 frameCounter;        /**< Frame number since last detection */

  MultiFailureChecker multiFailureChecker;
  cv::Mat shape;          /**< Current shape */
  cv::Mat shapePDM;       /**< Current shape without rigid transformation */
  cv::Mat referenceShape; /**< Reference shape */
  cv::Rect storedRect;    /**< Detected rectangle */
  cv::Scalar initializationSimilarity; /**< Initialization similarity */

  cv::Mat small, faceTemplate;

  void initShape(cv::Rect &faceRect);
  cv::Rect redetect(cv::Mat &im);
  cv::Rect updateTemplate(cv::Mat &image, bool rsize);

  int consecutiveFaceDetections;
  int minimumConsecutiveFaceDetections;

  int poseStabilityCounter;
  int minumumPoseStabilityCounter;

  bool debug;
};

} /* namespace facetracker */

#endif /* TRACKER_H_ */
