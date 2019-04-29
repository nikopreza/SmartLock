#!/bin/bash

g++ smartlock.cpp -o smartlock.o -c -Wall -pthread -I/usr/local/include/opencv -I/usr/local/include
g++ smartlock.o -o smartlock -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lpng -lz -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lfontconfig -lfreetype -lgthread-2.0 -lglib-2.0 -lavcodec -lavformat -lavutil -lswscale -ldl -lm -lpthread -lrt -lraspicam -lraspicam_cv -lpigpio
