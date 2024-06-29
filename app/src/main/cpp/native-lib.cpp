#include <jni.h>
#include <string>

#include <android/log.h>
#include <android/native_window_jni.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/features2d/features2d.hpp>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "Facetomood", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Facetomood", __VA_ARGS__)

#include <insight.h>

cv::Scalar blackColor = CV_RGB(0, 0, 0);
cv::Scalar whiteColor = CV_RGB(255, 255, 255);
cv::Scalar redColor = CV_RGB(0, 0, 255);
cv::Scalar greenColor = CV_RGB(0, 255, 0);

insight::Insight *ins = 0;

int positive_mood_index = -1;
int negative_mood_index = -1;

std::string process(cv::Mat &image);

void initialize(cv::Mat &image);

extern "C" JNIEXPORT jstring JNICALL
Java_cat_norna_facetomood_MainActivity_reset(
        JNIEnv *env,
        jobject /* this */) {
    LOGD("Reseting Facetomood");
    // ins->resetTracker();
    delete ins;
    ins = 0;
    std::string str = "Reset";
    return env->NewStringUTF(str.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_cat_norna_facetomood_MainActivity_detect(
        JNIEnv *env,
        jobject /* this */, jint imageWidth, jint imageHeight,
        jobject imageBuffer, jobject dstSurface) {

    LOGD("Starting processing ...");

    uint8_t *srcLumaPtr = reinterpret_cast<uint8_t *>(env->GetDirectBufferAddress(imageBuffer));
    if (srcLumaPtr == nullptr) {
        LOGE("blit NULL pointer ERROR");
        return NULL;
    }

    cv::Mat imageYuv(imageHeight + imageHeight / 2, imageWidth, CV_8UC1, srcLumaPtr);

    ANativeWindow *win = ANativeWindow_fromSurface(env, dstSurface);
    ANativeWindow_acquire(win);

    ANativeWindow_Buffer buf;

    int dstWidth = imageHeight;
    int dstHeight = imageWidth;

    ANativeWindow_setBuffersGeometry(win, dstWidth, dstHeight, 0 /*format unchanged*/);

    if (int32_t err = ANativeWindow_lock(win, &buf, NULL)) {
        LOGE("ANativeWindow_lock failed with error code %d\n", err);
        ANativeWindow_release(win);
        return NULL;
    }

    uint8_t *dstLumaPtr = reinterpret_cast<uint8_t *>(buf.bits);
    cv::Mat dstRgba(dstHeight, buf.stride, CV_8UC4,
                    dstLumaPtr);        // TextureView buffer, use stride as width
    cv::Mat imageRgba(imageHeight, imageWidth, CV_8UC4);
    cv::Mat flipRgba(dstHeight, dstWidth, CV_8UC4);

    // convert YUV -> RGBA
    cv::cvtColor(imageYuv, imageRgba, CV_YUV2RGBA_NV21);

    // Rotate 90 degree
    cv::transpose(imageRgba, flipRgba);
    cv::flip(flipRgba, flipRgba, 0);
    cv::flip(flipRgba, flipRgba, 1);

    /* process image */
    std::string result = process(flipRgba);

    // copy to TextureView surface
    uchar *sourceBuffer = flipRgba.data;;
    uchar *destinationBuffer = dstRgba.data;
    for (int i = 0; i < flipRgba.rows; i++) {
        destinationBuffer = dstRgba.data + i * buf.stride * 4;
        memcpy(destinationBuffer, sourceBuffer, flipRgba.cols * 4);
        sourceBuffer += flipRgba.cols * 4;
    }

    LOGD("Image processed");

    ANativeWindow_unlockAndPost(win);
    ANativeWindow_release(win);

    return env->NewStringUTF(result.c_str());
}

void initialize(cv::Mat &image) {
    ins = new insight::Insight;
    ins->init(image);
}

std::string process(cv::Mat &image) {

    if (ins == 0) {
        initialize(image);
        LOGD("MoodSDK native initialized");
    }

    int image_width = image.cols;
    int image_height = image.rows;

    if (ins->process(image)) {

        insight::Person person = ins->getPerson();
        cv::rectangle(image, person.getFaceRect(), cv::Scalar(255, 255, 0), 1, 8,
                      0);

        /* tracking points */
        std::vector<cv::Point> trackingPoints = person.getTrackingPoints();
        int n = trackingPoints.size();
        for (int i = 0; i < n; i++)
            cv::circle(image, trackingPoints[i], 2, greenColor, -1);

        const std::vector<insight::Mood> &moods = ins->getMoods();
        int numberOfMoods = moods.size();

        if (positive_mood_index == -1) {
            for (int i = 0; i < numberOfMoods; i++) {
                if (moods[i].getCode() == 13)
                    positive_mood_index = i;
                if (moods[i].getCode() == 14)
                    negative_mood_index = i;
            }
        }

        const std::vector<double> &detectedMoods = person.getDetectedMoods();

        /* etiquetas */

        int maxIndex = -1;
        for (int i = 0; i < numberOfMoods; i++) {
            if (i == positive_mood_index || i == negative_mood_index)
                continue;
            double detectedMood = detectedMoods[i];
            if (maxIndex == -1 || detectedMoods[maxIndex] < detectedMood)
                maxIndex = i;
        }

        std::stringstream ss;
        ss << "Mood: " << moods[maxIndex].getLabel();

        cv::putText(image, ss.str(), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX,
                    1,
                    blackColor,
                    2, cv::LINE_AA);

        /* tercer nivel */

        float positive_mood = detectedMoods[positive_mood_index];
        float negative_mood = detectedMoods[negative_mood_index];

        LOGD("Mood: positive=%f negative=%f", positive_mood, negative_mood);

        /* bar background */
        cv::rectangle(image, cv::Point(image_width - 65, 0),
                      cv::Point(image_width, image_height), whiteColor, -1);

        if (positive_mood > 0 || negative_mood > 0) {

            int positive_bar_height = positive_mood * (image_height / 2);
            int negative_bar_height = negative_mood * (image_height / 2);

            if (positive_mood > 0) {
                cv::rectangle(image, cv::Point(image_width - 65, image_height / 2),
                              cv::Point(image_width, image_height / 2 - positive_bar_height),
                              greenColor, -1);

                std::stringstream ss;
                int percent = positive_mood * 100;
                ss << "P:" << percent << "%";
                int textY = image_height / 2 - positive_bar_height > 30 ?
                            image_height / 2 - positive_bar_height - 10 : 30;
                cv::putText(image, ss.str(), cv::Point(image_width - 62, textY),
                            cv::FONT_HERSHEY_SIMPLEX,
                            0.6,
                            blackColor,
                            2, cv::LINE_AA);
            }

            if (negative_mood > 0) {
                cv::rectangle(image, cv::Point(image_width - 65, image_height / 2),
                              cv::Point(image_width, image_height / 2 + negative_bar_height),
                              redColor, -1);

                std::stringstream ss;
                int percent = negative_mood * 100;
                ss << "N:" << percent << "%";
                int textY = image_height / 2 + negative_bar_height < image_height - 30 ?
                            image_height / 2 + negative_bar_height + 20 : image_height - 30;
                cv::putText(image, ss.str(), cv::Point(image_width - 62, textY),
                            cv::FONT_HERSHEY_SIMPLEX,
                            0.6,
                            blackColor,
                            2, cv::LINE_AA);
            }
        }

        LOGD("Mood: %s (%f %%)", moods[maxIndex].getLabel().c_str(), detectedMoods[maxIndex] * 100);

    } else {
        cv::rectangle(image, cv::Point(image_width - 65, 0),
                      cv::Point(image_width, image_height), whiteColor, -1);
    }

    return "Processed image";
}