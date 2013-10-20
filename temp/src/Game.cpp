#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using std::cout;
using std::endl;
using std::string;

void Game::run()
{
    /**************************************************************************
    ***************************** Game Options ********************************
    **************************************************************************/
    int xMin = 150; // NOTE: Hardcoded
    int xMax = 500; // NOTE: Hardcoded
    int rows = 40; // NOTE: Hardcoded
    int columns = 100; // Mutable, must be greater than 20
    int wallWidth = 5;
    int minWidth = 10;
    char spacer = ' ';
    char player = '0';
    char obstacle = '=';
    char crash = 'X';
    bool alive = true;
    int counter = 0;
    double difficulty = .5; // 0.05 to 5
    int levelLength = 100;

    /**************************************************************************
    ******************** Window and Detector Initialization *******************
    **************************************************************************/
    CascadeClassifier face_cascade;
    face_cascade.load("dataSets/haarcascade_frontalface_alt.xml");
    VideoCapture capturedevice;
    capturedevice.open(0);
    Mat captureframe;
    Mat grayscaleframe;
    namedWindow("Live Feed", 1);

    /**************************************************************************
    *********************** Game Display Initialization ***********************
    **************************************************************************/
    string display[rows]; // The display for the game
    for (int k = 0; k < rows; k++){ // Initialize the display to empty values
        string row("");
        for (int j = 0; j < columns; j++){
            if (j < wallWidth || j > columns - 1 - wallWidth){
                row += obstacle;
            }
            else{
                row += spacer;
            }
        }
        display[k] = row;
    }

    /**************************************************************************
    ****************************** BEGIN LOOP *********************************
    **************************************************************************/
    
    // Obtain the new row position
    while(alive)
    {
        capturedevice>>captureframe;
        cvtColor(captureframe, grayscaleframe, CV_BGR2GRAY);
        equalizeHist(grayscaleframe, grayscaleframe);
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(grayscaleframe, faces, 1.1, 3, 
            CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(30,30));

        for(size_t i = 0; i < faces.size(); i++) {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
            rectangle(captureframe, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
        }

        // Find the x position for the player
        int x;
        if (faces.size() > 0){
            x = (2*faces[0].x + faces[0].width)/2.0;
        }
        else{
            x = (xMax + xMin)/2.0;
        }

        // Create the next row, based on player position
        string row;
        int xPos = columns - (x-xMin)/double(xMax-xMin) * columns;
        for (int i = 0; i < columns; i++){
            if (i == xPos){
                row += player;
            }
            else if (i < wallWidth || i > columns - 1 - wallWidth){
                row += obstacle;
            }
            else {
                row += spacer;
            }
        }

        // Update the game board
        if (counter < rows/2) {
            display[counter] = row;
        }
        else{
            string tempDisplay[rows];
            for (int i = 1; i < rows; i++){
                tempDisplay[i-1] = display[i];
            }

            // Generate new obstables
            string obRow("");
            for (int j = 0; j < columns; j++){
                if (j < wallWidth || j > (columns-1) - wallWidth) {
                    obRow += obstacle; 
                }
                else if(rand() % 1000 - difficulty*sqrt(counter) < 1){
                    obRow += obstacle;
                }
                else{
                    obRow += spacer;
                }
            }
            tempDisplay[rows-1] = obRow;
        
            // Overlay the current layer ON rows/2
            for (int i = 0; i < columns; i++){
                if (row[i] == '0'){
                    if (tempDisplay[rows/2][i] == obstacle){
                        tempDisplay[rows/2][i] = crash;
                        alive = false;
                    }
                    else{
                        tempDisplay[rows/2][i] = player;
                    }
                }
            }

            // Update the game board
            for (int i = 0; i < rows; i++){
                display[i] = tempDisplay[i];
            }
        }


        // Update the score display
        for (int i = 0; i < rows; i++){
            display[i].resize(columns);
        }
        std::stringstream s1;
        s1 << counter;
        display[rows-1] += ("   Score: " + s1.str());


        // Print out all rows at the end
        for (int k = 0; k < rows; k++){
            cout << display[k] << endl;
        }

        counter++; // Increase the score
        if (counter/levelLength + 5 > wallWidth){ // TODO: The '5' is harcoded here
            if (columns - wallWidth*2 >= minWidth){
                wallWidth = 5 + counter/levelLength;
            }
        }
        
        imshow("Live Feed", captureframe);
        waitKey(33);
    }
    
    gameOver(counter);
}


void Game::gameOver(int score){

    cout << "\nGAME OVER" << endl;
}
