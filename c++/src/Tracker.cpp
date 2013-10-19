// C++ Libraries
#include <iostream>
#include <stdio.h>

// OpenCV Libraries
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// Header files
#include "Tracker.h"

using namespace cv;
using std::cout;
using std::endl;

void Tracker::runFace()
{
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



    // EDITED BY MACK:
    int xInit = 0;
    int yInit = 0;
    int n = 100;
    int tol = 20;
    int state = 0; // 0 is neutral, -1 is down, 1 is up
 
    cout << "Initialization Started" << endl;
    //create a loop to capture and find faces
    for(int i = 0; i < n; i++) // TODO: Test 100 initialization steps
    {
        //capture a new image frame
        capturedevice >> captureframe;
 
        //convert captured image to gray scale and equalize
        cvtColor(captureframe, grayscaleframe, CV_BGR2GRAY);
        equalizeHist(grayscaleframe, grayscaleframe);
 
        //create a vector array to store the face found
        std::vector<Rect> faces;
 
        //find faces and store them in the vector array
        face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
 
        //draw a rectangle for all found faces in the vector array on the original image
        for(int i = 0; i < faces.size(); i++)
        {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
 
            rectangle(captureframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);

            /*
            cout << "X: " << (2*faces[i].x + faces[i].width)/2.0 << "\nY: " << (2*faces[i].y + faces[i].height)/2.0 
                 << endl;*/
        }

        xInit += (2*faces[0].x + faces[0].width)/2.0;
        yInit += (2*faces[0].y + faces[0].height)/2.0;
 
        //print the output
        imshow("outputcapture", captureframe);
 
        //pause for 33ms
        waitKey(33);
    }

    xInit /= double(n);
    yInit /= double(n);

    cout << "Initialization Complete" << endl;

    //create a loop to capture and find faces
    while(true)
    {
        //capture a new image frame
        capturedevice>>captureframe;
 
        //convert captured image to gray scale and equalize
        cvtColor(captureframe, grayscaleframe, CV_BGR2GRAY);
        equalizeHist(grayscaleframe, grayscaleframe);
 
        //create a vector array to store the face found
        std::vector<Rect> faces;
 
        //find faces and store them in the vector array
        face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));
 
        //draw a rectangle for all found faces in the vector array on the original image
        for(int i = 0; i < faces.size(); i++)
        {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
 
            rectangle(captureframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);

            //cout << "X: "<< (2*faces[i].x + faces[i].width)/2.0<<"  Y1: "<<(2*faces[i].y + faces[i].height)/2.0 << endl;
        }

        int x = (2*faces[0].x + faces[0].width)/2.0;
        int y = (2*faces[0].y + faces[0].height)/2.0;
        
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

                    
 
        //print the output
        imshow("outputcapture", captureframe);
 
        //pause for 33ms
        waitKey(33);
    }
}
