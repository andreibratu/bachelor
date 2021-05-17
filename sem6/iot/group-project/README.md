# Artificial Intelligence Based Doorbell System

The purpose of this IoT application is to provide a proof of concept for a doorbell system designed for common households.
The doorbell system represents a smart lock that uses a camera to scan people's faces that 'ring' on the doorbell button, and only 'unlocks the door' 
for recognized faces.
The concept of unlocking is represented by lighting a blue LED for 'allowed' faces, and a red LED for the ones that are not recognized.
The IoT project is built using a Raspberry Pi 4 and a Pi Noir camera and the process of facial recognition is handled by artificial intelligence algorithms embedded on the Raspberry Pi. It uses Firebase as cloud storage for the recognized faces and all the attempts made.

The artificial intelligence part is handled through the TensorFlow library. Our approach recognizes the coordinates of 15 key facial points (e.g. (top_upper_lip_x, top_upper_lip_y)) and compares them between users. Under the assumption that the coordinates are differently localized for each person, we allow a user only if the average euclidian distance between a known set of 15 points and their set of 15 points is below a threshold. 

As input, the model takes 96x96 mono-channel images, with pixel values normalized in [-1; 1].

The model consists of several convolutional layers, followed by dense layers. A HyperBand algorithm has been used for hyperparameter optimization.

A distribution of the 15 key points:

![image](https://user-images.githubusercontent.com/20412697/117971528-b452e400-b332-11eb-9be4-6034422100f5.png)

Neural network architecture:

![image](https://user-images.githubusercontent.com/20412697/117972118-65597e80-b333-11eb-8feb-6b7435bb29bf.png)


There is also a companion mobile application made with Flutter that shows all the photos taken each time someone pushed the doorbell button, together with the date and access provided (allowed/denied entrance). The application is also used for adding a new face to the collection of recognized faces, which are allowed entrance.

## Pictures

![Setup](p1.jpeg?raw=true "Setup")

![Ringing the doorbell](p2.jpeg?raw=true "Ringing the doorbell")

![Not allowed](p3.jpeg?raw=true "Not allowed")

<sub><it>**Disclaimer*: no resistors can be seen in the photos, but they should be included in the project in order not to damage the components.<sub>

## Schematics

![Schematics](fritzing_diagram.jpeg?raw=true "Schematics")

## Pre-requisites

- Raspberry Pi 3 or 4
- Pi Noir Camera with CSI cable
- The following individual components:
  - 1 breadboard
  - jumper wires
  - 1 push button
  - 3 resistors (0.22-1 kΩ)
  - 2 LEDs (blue, red)

## Running the application

To run the application on the Raspberry Pi, follow these steps below:
- Connect the push button and the two LEDs to the GPIO pins according to the presented schematics
- Connect the Pi Noir camera to the CSI input and the power source to the Raspberry Pi
- Find the Raspberry Pi IP address on your local network and connect to it via ssh (e.g.: `ssh pi@192.168.100.92`)
- Clone this repository locally on the Raspberry Pi
- Make sure Python 3 is installed (run `python3 --version`) on the Raspberry Py. If not, install it via `sudo apt-get install python3`
- Make sure pip is installed (run `pip --version`) on the Raspberry Py. If not, install it via `sudo apt-get install python-pip`
- Navigate to the folder `raspberry_pi/`
- Install all the packages via `pip install -r requirements.txt`
- Once everything is installed, run the command `python3 main.py`
- Push the physical button to ring on the doorbell and make sure to look in the camera
- A photo of your face will be taken. If your face will be recognized, you will be 'allowed access', so the blue LED will light up, otherwise, the red LED will light up

Follow the steps below for running the mobile application:
- In order to add your face to the list of recognized ones, install the mobile application, `mobile/doorbell_app.apk` on an Android device
- On the main screen of the application you will be able to see all the attempts made by people that rang the doorbell
- Press the add (+) button from the top-right of the application to add your face to the list of recognized ones


