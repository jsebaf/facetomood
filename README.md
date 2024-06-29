# Facetomood

## About

Facial expressions play an important role for recognizing people’s affective states, and to know how a person would react to the actions produced by external stimulus such as a video clip or one app interface. So far, interaction designers could consider these inputs in order to create smarter interfaces that react instantaneously to user’s affective states. There are other applications such as videogames that require longer user interactions, and therefore, the recognition of longer affective states. In this sense, the mood of a player could provide information about how he/she is experiencing the game.

Facetomood is a low-level library designed to recognize user's mood from long video sequences.

Our approach is mainly based on psychological studies in order to define a set of rules for robustly obtain the users mood from sequences of their facial expressions. First, we defined a set of rules, which associated Action Units (AUs) to each octant of the Mehrabian’s Pleasure-Arousal-Dominance (PAD) space and classifies the emotional state into: **DOCILE**, **HOSTILE**, **ANXIOUS**, **DISDAINFUL**, **BORED**, **EXUBERANT**, **DEPENDENT** and **RELAXED**.

By tracking the user’s facial features, we find a correspondence between their instantaneous micro expressions (AUs) and their mood. Finally, we used the tracked AUs together with the previously formulated rules to depict the mood of each user. 

Facetomood-Demo is a demostration android app using Facetomood that can be used as starting point for developing more complex applications.

## Dependencies and Requirements

* The library itself is written in C++ and the only dependency is OpenCV. The release packed with this example app uses OpenCV v4.1.1 (included in the package).
* The library packed with this app is built for min Android API level 21.

## Usage

It is necessary to have a basic knowledge of OpenCV and its data structures. Face images must be converted to OpenCV matrix type to be proccessed by Facetomood.

### Setup

To interact with the SDK you must use the *Insight* class in the *insight* namespace. The application must maintain an instance of this class that must be initialized at least once. 

	#include <opencv2/core/core.hpp>
	#include <opencv2/imgproc/imgproc.hpp>
	#include <opencv2/imgproc/imgproc_c.h>
	#include <opencv2/features2d/features2d.hpp>
	
	#include <insight.h>
	
	insight::Insight *ins = 0;
	
	void initialize(cv::Mat &image) {
		ins = new insight::Insight;
		ins->init(image);
	}

In this example *image* is a *cv::Mat* pointer containing an image in RGB format. In the following examples this identifier will refer to facial images in the same format. 

### Processing

Once initialized, the instance of the Insight class can be used to process subsequent images using the *process()* method. This method receives an image and returns *boolean* indicating processing success. If the processing has been successful, an instance of the *insight::Person* class can be obtained that encapsulates information about the mood and other elements of interest. 

	if (ins->process(image)) {
		insight::Person person = ins->getPerson();
		const std::vector<double> &detectedMoods = 
		person.getDetectedMoods();
	}

Method *Person::getDetectedMoods()* returns mood level probabilities encoded as a flat vector of length 14. Mood is presented in three levels. First (full) level is divided in the eight moods enumerated above. Second level is divided in four moods: **ELATED**, **CALM**, **ANXIOUS** and **BORED**. Finally third level is divided in **POSITIVE** and **NEGATIVE** moods. Levels position are reversed in the response vector, i.e. position one and two encode the third mood level probabilities, the following four positions encode the second level and the last eight positions encode the first level.

This order can be obtained from *Insight::getMoodLevels()* and *MoodLevel::getMoods()*:

	const std::vector<MoodLevel> &moodLevels = ins->getMoodLevels(); 
	
	int index = 0;
	
	for (MoodLevel &level : moodLevels) {
		std::cout << "Mood level: " << level.getName() << std::endl;
	    const std::vector<Mood> &moods = level.getMoods();
	    for (const Mood &mood : moods) {
			std::cout << "Mood: " << mood.getLabel() << ", value is: " << detectedMoods[i++] << std::endl;
		}
	}
	
For details about other available options please see the API documentation in docs directory.

### Licence notes

This repository includes OpenCV source files. For OpenCV licence details see [OpencCV licence file](opencv/LICENCE). 
