#include <iostream>
#include "webcam.h"
#include "resource.h"


// Opencv libraries
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

// Dynamixel libraries
#ifdef __linux__
// all in included files
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

// Set video resolution
#define XRES  640
#define YRES  480

using namespace cv;
using namespace std;


int main() {

    char name[] = "";

    // Ask for name
    printf("-> Input Video Name\n");
    cin >> name;

    // Create name of output video file
    char videoName[80];
    strcpy (videoName, name);
    strcat (videoName,".avi");

    // Wait to continue
    printf("-> Press any key to continue \n");
    string continueProg = "";
    cin >> continueProg;
    getch();


    // Initialise frame
    RGBImage frame;

    // Define the webcam
    Webcam webcam("/dev/video1", XRES, YRES);

    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl;

    // Create output video object
    int fourcc = VideoWriter::fourcc('M','J','P','G'); //VideoWriter_fourcc(*'XVID');
    Size videoSize(XRES, YRES);
    VideoWriter output = VideoWriter(videoName,fourcc, 20.0, videoSize);


    // Update camera
    // wait for a new frame from camera and store it into 'frame'
    while(! kbhit()) {

        // Get a new frame
        frame = webcam.frame();
        Mat image = Mat(int(frame.height), int(frame.width), CV_8UC3, frame.data);

        // From RGB to BGR (format supported by opencv)
        cvtColor(image, image, COLOR_RGB2BGR);

        // check if we succeeded
        if (image.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }


        // write to output video file so save
        output.write(image);

        // show live and wait for a key with timeout long enough to show images
        cvNamedWindow("Endoscope", CV_WINDOW_NORMAL);
        cvSetWindowProperty("Endoscope", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
        imshow("Endoscope", image);
        waitKey(5);

    } // end of loop

    // close video
    output.release();


}