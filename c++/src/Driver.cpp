// C++ Libraries
#include <iostream>
#include <stdio.h>

// OpenCV Libraries
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// Header files
#include "Driver.h"

using namespace cv;

void Driver::runVideo()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

    namedWindow("cam",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        imshow("cam", frame);
        if(waitKey(30) >= 0) break;
    }
}

void Driver::runBright()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

    namedWindow("window",1);
    for(;;)
    {
        double beta = 50; // Brightness increase

        Mat image;
        cap >> image; // get a new frame from camera
        Mat new_image = Mat::zeros(image.size(), image.type());
    
        // Do the operation new_image(i,j) = alpha*image(i,j) + beta
        for ( int y = 0; y < image.rows; y++ ) { 
            for( int x = 0; x < image.cols; x++ ) {
                for( int c = 0; c < 3; c++ ) {
                    new_image.at<Vec3b>(y,x)[c] =
                        saturate_cast<uchar>((image.at<Vec3b>(y,x)[c]) + beta);
                }
            }
        }

        imshow("window", new_image);
        if(waitKey(30) >= 0) break;
    }
}


void Driver::runEdges()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        Mat edges;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);    
        imshow("edges", edges);
        if(waitKey(30) >= 0){
            while(true){}
        }
    }
}



int Driver::runFace()
{
    //create the cascade classifier object used for the face detection
    CascadeClassifier face_cascade;

    //use the haarcascade_frontalface_alt.xml library
    face_cascade.load("datasets/haarcascade_frontalface_alt.xml");
 
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
        }
 
        //print the output
        imshow("outputcapture", captureframe);
 
        //pause for 33ms
        waitKey(33);
    }
 
    return 0;
}
