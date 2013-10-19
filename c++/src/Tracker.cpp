#include "Tracker.h"

#include <iostream>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using std::cout;
using std::endl;

void Tracker::track()
{

    /**************************************************************************
    ******************** Window and Detector Initialization *******************
    **************************************************************************/

    //create the cascade classifier object used for the face detection
    CascadeClassifier face_cascade;

    //use the haarcascade_frontalface_alt.xml library
    face_cascade.load("dataSets/haarcascade_frontalface_alt.xml");
    //face_cascade.load("dataSets/haarcascade_mcs_eyepair_small.xml");
 
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
    int n = 100; // number of initialization frames
    int tol = 20; // Position tolerance
    int state = 0; // 0 is neutral, -1 is down, 1 is up // TODO: Make this an enum
 
    cout << "Initialization Started" << endl;
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
    cout << "Initialization Complete" << endl;


    /**************************************************************************
    ****************************** Facial Tracking ***************************
    **************************************************************************/

    while(true)
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
            x = (2*faces[0].x + faces[0].width)/2.0; //TODO: Implement side to side motion
            y = (2*faces[0].y + faces[0].height)/2.0;
        }
        else{
            x = xInit;
            y = yInit;
        }

        // A switch statement for determining the output of the program
        switch(state){
            case -1: // Down
                if (y < yInit + tol){
                    if (y < yInit - tol){
                        state = 1;
                        cout << "UP" << endl;
                    }
                    else{
                        state = 0;
                        cout << "NEUTRAL" << endl;
                    }
                }
                break;

            case 0: // NEUTRAL
                if (y < yInit - tol){
                    state = 1;
                    cout << "UP" << endl;
                }
                else if (y > yInit + tol){
                    state = -1;
                    cout << "DOWN" << endl;
                }
                break;

            case 1: // UP
                if (y > yInit - tol){
                    if (y > yInit + tol){
                        state = -1;
                        cout << "DOWN" << endl;
                    }
                    else{
                        state = 0;
                        cout << "NEUTRAL" << endl;
                    }
                }
                break;
        }

        imshow("outputcapture", captureframe);
        waitKey(33);
    }
}
