#ifndef TRACKER_H_
#define TRACKER_H_

#include <boost/thread.hpp>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/*
 * This class is reponsible for running the tracking application
 */
class Tracker
{
public:
    Tracker();
    ~Tracker();
    int track();
    void initialize();
    bool m_foundFile;
    bool m_isTracking;
    bool m_isInitialized;
    
    // The current offsets
    int yOffset;
    int xOffset;

    // Initial values for x and y, set in the initialize
    int yInit;
    int xInit;

    //create the cascade classifier object used for the face detection
    cv::CascadeClassifier face_cascade;

    //setup video capture device and link it to the first capture device
    cv::VideoCapture capturedevice;
};

#endif // TRACKER_H_
