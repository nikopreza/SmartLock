#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <raspicam/raspicam_cv.h>
#include <unistd.h>
#include <pigpio.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#define PORT 8080 

using namespace std;
using namespace cv;

int main( int argc, const char** argv )
{
    int sock = 0; 
    struct sockaddr_in serv_addr;  
    char buffer[1] = {0}; 
    char last;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    if (gpioInitialise() < 0) {
        return -1;
    }
    gpioSetMode(4, PI_OUTPUT);
    gpioSetMode(19, PI_OUTPUT);
    gpioSetMode(26, PI_OUTPUT);
    
    raspicam::RaspiCam_Cv picam;
    //set camera params
    picam.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
    
    //Open camera
    printf("Opening Camera\n");
    if (!picam.open()) {
        printf("Error opnening camera\n");
        return -1;
    }
    //Start capture

    //VideoCapture capture;
    Mat frame;
    
    CascadeClassifier face_cascade;
    if(!face_cascade.load("/home/pi/opencv-3.4.6/data/haarcascades/haarcascade_frontalface_alt.xml")) {
        printf("error loading cascade\n");
        return -1;
    }
    
    while(1) {
        picam.grab();
        picam.retrieve(frame);
        
        if(frame.empty()) {
            break;
        }
        
        vector<Rect> faces;
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        resize(gray, gray, Size(300, 300));
        equalizeHist(gray, gray);
        face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(30, 30));
        
        resize(frame, frame, Size(150, 150));
        imwrite("capture.jpg", frame);
        
        
        if(!faces.empty()) {
            printf("face detected\n");
            char c = '1';
            send(sock, &c, 1, 0);
        } else {
            printf("face not detected\n");
            char c = '0';
            send(sock, &c, 1, 0);
        }
        read(sock, buffer, 1);
        
        printf("%d\n", buffer[0]);
        
        if (buffer[0] == 49 && last != buffer[0]) {
            printf("locked\n");
            gpioServo(4,500);
            gpioWrite(19, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(19, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(19, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(19, 0);
            
        } else if (buffer[0] == 48 && last != buffer[0]) {
            printf("unlocked\n");
            gpioServo(4,1500);
            gpioWrite(26, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(26, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(26, 1);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            gpioWrite(26, 0);
        }
        last = buffer[0];
    }
}
