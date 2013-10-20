#include "Tracker.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <boost/thread.hpp>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using std::cout;
using std::endl;
using std::fstream;



Tracker::Tracker(): m_foundFile(false), m_isTracking(true), xOffset(0), yOffset(0), 
                    xInit(0), yInit(0), m_isInitialized(false), face_cascade(),
                    capturedevice()
{}

Tracker::~Tracker() {}

int Tracker::track(){

    /**************************************************************************
     ****************************** Facial Tracking ***************************
     **************************************************************************/

    //setup image files used in the capture process
    cv::Mat captureframe;
    cv::Mat grayscaleframe;

    // NOTE: If you can't see any rectangles, try full file path
    const char* s = "/home/mackward/scrolr/extension/haarcascade_frontalface_alt.xml";

    //use the haarcascade_frontalface_alt.xml library
    face_cascade.load(s);
    capturedevice.open(0);
    //create a window to present the results
    namedWindow("outputcapture", 1);

    capturedevice>>captureframe;
    cvtColor(captureframe, grayscaleframe, CV_BGR2GRAY);
    equalizeHist(grayscaleframe, grayscaleframe);
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
    for(size_t i = 0; i < faces.size(); i++)
    {
        Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        Point pt2(faces[i].x, faces[i].y);
        rectangle(captureframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
    }

    int x;
    int y;
    if (faces.size() > 0){ // If finds a face
        x = (2*faces[0].x + faces[0].width)/2.0;
        y = (2*faces[0].y + faces[0].height)/2.0;
    }
    else{
        x = xInit;
        y = yInit;
    }

    xOffset = (x - xInit);
    yOffset = (y - yInit);

    imshow("outputcapture", captureframe); // TODO
    waitKey(5);

    return yOffset;
}

void Tracker::initialize(){

    /**************************************************************************
     *********************** User Position Initialization **********************
     **************************************************************************/

    // NOTE: If you can't see any rectangles, try full file path
    const char* s = "/home/mackward/scrolr/extension/haarcascade_frontalface_alt.xml";

    fstream file(s);
    if (file){
        m_foundFile = true;
    }

    //create the cascade classifier object used for the face detection
    CascadeClassifier face_cascade;

    //use the haarcascade_frontalface_alt.xml library
    face_cascade.load(s);

    //setup video capture device and link it to the first capture device
    VideoCapture capturedevice;
    capturedevice.open(0);

    //setup image files used in the capture process
    Mat captureframe;
    Mat grayscaleframe;

    //create a window to present the results
    namedWindow("outputcapture", 1);


    int n = 20; // number of initialization frames
    for(int i = 0; i < n; i++)
    {
        capturedevice >> captureframe;
        cvtColor(captureframe, grayscaleframe, CV_BGR2GRAY);
        equalizeHist(grayscaleframe, grayscaleframe);
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
        for(size_t i = 0; i < faces.size(); i++)
        {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
            rectangle(captureframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
        }
        if (faces.size() > 0){
            xInit += (2*faces[0].x + faces[0].width)/2.0;
            yInit += (2*faces[0].y + faces[0].height)/2.0;
        }
        imshow("outputcapture", captureframe);
        waitKey(33);
    }
    xInit /= double(n);
    yInit /= double(n);

    m_isInitialized = true;
}
