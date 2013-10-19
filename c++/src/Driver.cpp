// C++ Libraries
#include <iostream>
#include <stdio.h>

// OpenCV Libraries
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

// Header files
#include "Driver.h"

using namespace cv;

void Driver::runVideo()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        imshow("edges", frame);
        if(waitKey(30) >= 0) break;
    }
}

void Driver::runBright()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

    namedWindow("window",1);
    namedWindow("newwindow",1);
    for(;;)
    {
        double alpha = 2; // Brightness increase
        double beta = 50; // Brightness increase

        Mat image;
        cap >> image; // get a new frame from camera
        Mat new_image = Mat::zeros(image.size(), image.type());
    
        // Do the operation new_image(i,j) = alpha*image(i,j) + beta
        for ( int y = 0; y < image.rows; y++ ) { 
            for( int x = 0; x < image.cols; x++ ) {
                for( int c = 0; c < 3; c++ ) {
                    new_image.at<Vec3b>(y,x)[c] =
                        saturate_cast<uchar>(alpha*(image.at<Vec3b>(y,x)[c]) + beta);
                }
            }
        }

        imshow("window", image);
        imshow("newwindow", new_image);
        if(waitKey(30) >= 0) break;
    }
}
