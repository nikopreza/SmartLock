# SmartLock

## IOT Door Lock and Camera System

### By Nikolas and Kristofer Preza

Our project utlizes a Raspberry Pi in order to allow users to see when someone is waiting at their front door and remotly unlock/lock their door by controlling a servo through an android application. The project has 3 main parts: the Raspberry Pi, a google sheets database, and an andriod application. On the Raspberry Pi, the C++ client, uses the Raspberry Pi Cmaera Module to capture an image and then uses OpenCV to detect if there is a face in the image. The image and facial detection information are then passed off to a Python server which is responsible for reading and writing the data to the google sheets database, sending the lock status value back to the C++ client, which it uses to turn the servo to the correct postion. On the other side, the andriod application reads the information on the database, updates the imageview and writes the lock toggle status to the database.

 Components
- [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- [Raspberry Pi Camera Module V2](https://www.raspberrypi.org/products/camera-module-v2/)
- [HS-422 Deluxe Servo](https://www.servocity.com/hs-422-servo/)
- [RGB LED](https://www.adafruit.com/product/159)
- 5v Power Bank
- Andriod Phone

