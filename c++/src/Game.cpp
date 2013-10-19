#include "Game.h"

#include <iostream>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using std::cout;
using std::endl;

void Game::run()
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
    int xMin = 150;
    int xMax = 500;
    int columns = 50;
    int n = 100; // number of initialization frames
 
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
            x = (2*faces[0].x + faces[0].width)/2.0;
            y = (2*faces[0].y + faces[0].height)/2.0;
        }
        else{
            x = xInit;
            y = yInit;
        }
        
        //cout << x;
        int column = columns - (x-xMin)/double(xMax-xMin) * columns;
        for (int i = 0; i < columns; i++){
            if (i == column){
                cout << "0";
            }
            else{
                cout << "-";
            }
        }
        cout << endl;
        //cout << column << endl;

        imshow("outputcapture", captureframe);
        waitKey(33);
    }
}
