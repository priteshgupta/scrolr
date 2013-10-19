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
    //face_cascade.load("dataSets/haarcascade_frontalface_alt.xml");
    face_cascade.load("dataSets/haarcascade_mcs_eyepair_small.xml");
 
    //setup video capture device and link it to the first capture device
    VideoCapture capturedevice;
    capturedevice.open(0);
 
    //setup image files used in the capture process
    Mat captureframe;
    Mat grayscaleframe;
 
    //create a window to present the results
    namedWindow("outputcapture", 1);
 
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

            cout << "X: "<< (2*faces[i].x + faces[i].width)/2.0<<"  Y1: "<<(2*faces[i].y + faces[i].height) << endl;
        }
 
        //print the output
        imshow("outputcapture", captureframe);
 
        //pause for 33ms
        waitKey(33);
    }
}
