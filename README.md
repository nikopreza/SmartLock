# SmartLock

## IOT Door Lock and Camera System

### By Nikolas and Kristofer Preza

Our project utlizes a Raspberry Pi in order to allow users to see when someone is waiting at their front door and remotly unlock/lock their door by controlling a servo through an android application. The project has 3 main parts: the Raspberry Pi, a google sheets database, and an andriod application. On the Raspberry Pi, the C++ client, uses the Raspberry Pi Cmaera Module to capture an image and then uses OpenCV to detect if there is a face in the image. The image and facial detection information are then passed off to a Python server which is responsible for reading and writing the data to the google sheets database, sending the lock status value back to the C++ client, which it uses to turn the servo to the correct postion. On the other side, the andriod application reads the information on the database, updates the imageview and writes the lock toggle status to the database.

## Flow Diagram
<img width="785" height="615" src=/Photos/SmartLockDiagram.jpg/>

## Components
- [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- [Raspberry Pi Camera Module V2](https://www.raspberrypi.org/products/camera-module-v2/)
- [HS-422 Deluxe Servo](https://www.servocity.com/hs-422-servo/)
- [RGB LED](https://www.adafruit.com/product/159)
- [M/F Jumper Wires](https://www.sparkfun.com/products/12794)
- 5v Power Bank
- Andriod Phone

## Pictures
- RGB LED
- <img width="350" height="250" src=/Photos/IMG_20190429_132023.jpg>
- Raspberry Pi
- <img width="350" height="250" src=/Photos/IMG_20190429_132034.jpg>
- Andriod Application
- <img width="250" height="400" src=/Photos/Screenshot_20190429-132111.png>
- Notification
- <img width="250" height="400" src=/Photos/Screenshot_20190429-132122.png>

## Demo Video
[![Demo](https://img.youtube.com/vi/JUYS_-SfBCw/0.jpg)](https://www.youtube.com/watch?v=JUYS_-SfBCw&feature=youtu.be)
