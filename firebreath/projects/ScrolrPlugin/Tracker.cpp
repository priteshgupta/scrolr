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


Tracker::Tracker(): m_foundFile(false), m_isTracking(false)
{}

Tracker::~Tracker() {}

void Tracker::track()
{
   m_thread = new boost::thread(&Tracker::runThread, this);
}

void Tracker::runThread(){

    /**************************************************************************
     ******************** Window and Detector Initialization *******************
     **************************************************************************/

    // NOTE: If you can't see any rectangles, try full file path
    const char* s = "/home/mackward/scrolr/firebreath/projects/ScrolrPlugin/haarcascade_frontalface_alt.xml";

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


    /**************************************************************************
     *********************** User Position Initialization **********************
     **************************************************************************/

    int xInit = 0;
    int yInit = 0;
    int n = 20; // number of initialization frames
    int xTol = 30; // Position tolerance
    int yTol = 20; // Position tolerance
    int xState = 0; // 0 is neutral, -1 is right, 1 is left // TODO: Make this an enum
    int yState = 0; // 0 is neutral, -1 is down, 1 is up // TODO: Make this an enum

    /*cout << "Initialization Started" << endl;
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
    cout << "Initialization Complete" << endl;*/


    /**************************************************************************
     ****************************** Facial Tracking ***************************
     **************************************************************************/

    while(m_isTracking)
    {
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
        if (faces.size() > 0){
            x = (2*faces[0].x + faces[0].width)/2.0;
            y = (2*faces[0].y + faces[0].height)/2.0;
        }
        else{
            x = xInit;
            y = yInit;
        }

        // A switch statement for determining the y output of the program
        switch(yState){
            case -1: // Down
                if (y < yInit + yTol){
                    if (y < yInit - yTol){ yState = 1; cout << "UP" << endl; }
                    else{ yState = 0; cout << "YNEUTRAL" << endl; }
                }
                break;

            case 0: // NEUTRAL
                if (y < yInit - yTol){ yState = 1; cout << "UP" << endl; }
                else if (y > yInit + yTol){ yState = -1; cout << "DOWN" << endl;}
                break;

            case 1: // UP
                if (y > yInit - yTol){
                    if (y > yInit + yTol){ yState = -1; cout << "DOWN" << endl; }
                    else{ yState = 0; cout << "YNEUTRAL" << endl; }
                }
                break;
        }

        // A switch statement for determining the x output of the program
        switch(xState){
            case -1: // Right
                if (x > xInit - xTol){
                    if (x > xInit + xTol){ xState = 1; cout << "LEFT" << endl;}
                    else{ xState = 0; cout << "XNEUTRAL" << endl;}
                }
                break;

            case 0: // NEUTRAL
                if (x < xInit - xTol){ xState = -1; cout << "RIGHT" << endl;}
                else if (x > xInit + xTol){ xState = 1; cout << "LEFT" << endl;}
                break;

            case 1: // Left
                if (x < xInit + xTol){
                    if (x < xInit - xTol){ xState = -1; cout << "RIGHT" << endl; }
                    else{ xState = 0; cout << "XNEUTRAL" << endl;}
                }
                break;
        }

        imshow("outputcapture", captureframe);
        waitKey(33);
    }
}

