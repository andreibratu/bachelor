# solo-project-andreibratu
solo-project-andreibratu created by GitHub Classroom

__Video demonstration can be found at this [link](https://drive.google.com/file/d/1JHfQo7od055cAg3yo_XDZSQ1f_evjvl4/view?usp=sharing)__

A IoT surveillance project. IoT device will leverage deep learning to identify pre-defined keywords from speech and notify the user via a mobile application.

## User requirements:
* As a user I want to dod CRUD operations on the keywords
* As a user I want to see frequency statistics for each keyword
* As a user I want to record audio phrases in 1- seconds intervals
* As a user I want to see a list of all phrases that contain deisgnated keywords

## Required hardware
* Rasberry Pi 4 https://www.robofun.ro/raspberry/placa-raspberry-pi-4-model-b-4gb.html
* USB Microphone https://www.emag.ro/microfon-trust-gxt212-mico-conectare-usb-3-5mm-tripod-negru-23791trust/pd/DWZGGYMBM/?X-Search-Id=58cf526bfb6df2df0946&X-Product-Id=6781450&X-Search-Page=1&X-Search-Position=0&X-Section=search&X-MB=0&X-Search-Action=view
* MicroSD card https://www.emag.ro/card-de-memorie-microsd-kingston-canvas-select-plus-32gb-100mb-s-cu-adaptor-sdcs2-32gb/pd/D63FBGBBM/?X-Search-Id=ff2358a2f017ffe4add9&X-Product-Id=59172346&X-Search-Page=1&X-Search-Position=0&X-Section=search&X-MB=0&X-Search-Action=view
* A UNIX/ [Windows with WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10) laptop


## Setup instructions

1. Configure Raspbian on RPi4 using the [official flasher on the before-mentioned MicroSD card](https://youtu.be/cOYTE0TjQL8). Find out your RPi4's IP address so you can ```ssh``` into it.
2.  Install [Rust compiler](https://www.rust-lang.org/tools/install) (required by ```transformers``` Python dependency)
3. Install the ```torch``` deep kearning library from source code using [this guide](https://medium.com/hardware-interfacing/how-to-install-pytorch-v4-0-on-raspberry-pi-3b-odroids-and-other-arm-based-devices-91d62f2933c7). ```Danger: This takes an unbeliavably long time (3-5h compilation). The sooner this is taken care of the better.```
4. Sync the ```pi``` directory to device using [rsync](https://linux.die.net/man/1/rsync): ```rsync -chav solo-project-andreibratu <<PI_USER>>@<<PI_IP_ADDRESS>>:```
5. Create a virtual environment for project's python dependencies: ```python3 -m venv```
6. Activate the virtual environment: ```source venv/bin/activate```
7. Install project dependencies: ```pip install -r pi/requirements.txt```
8. Run the listener ```python pi/listener_service.py```
9. [Set up Flutter on your computer](https://flutter.dev/docs/get-started/install)
10. [Compile your application to a target mobile device](https://flutter.dev/docs/deployment/android)

## Architecture

Project uses Google Firebase as a serverless backend with real-time capabilities. It syncronises a mobile application and a IoT device (RaspberryPi4 running Raspbian)

The project uses a deep learning model running on RPi4 to convert audio input to text. The recognized phrases are scanned for user-picked keywords. If keywords are detected, the phrase is submitted to Firebase and forwarded to the mobile application.

![project_org_at_solo](https://user-images.githubusercontent.com/20412697/116459079-0a715300-a86e-11eb-8b79-4a04ddcc0094.jpg)


### listener.service

Due to a lack of CUDA capabilites on RPi4, inference and model loading is a slow process. To ensure due processing, the main process spawns multiple __recognition_worker__ processes and a __upload_worker__ to delegate tasks. The processes are syncronized through two Queue ADTs that abstract over the pipe inter-process communication pattern.

The model used for speech to text task is [facebook/wav2vec2-base-960h](https://huggingface.co/facebook/wav2vec2-base-960h).

### Mobile application

The mobile application is quite straightforward architecture-wise. A noticeable thing is the realtime capabilities of the Firebase client. Two Observers design pattern objects are used to keep the views in sync as RPi4 publishes its updates. The mobile application was written in Flutter, ensuring cross-platform capabilities. 

## Possible improvements

* Automate setup using bash script
* Leverage RPi4 GPU. Despite the RPi4 GPU not supporting CUDA there are options for accelerating the on-board inferance. The approach should simplify the multi-process listener.service while also providing superior computation speed. A worflow sketch is presented below:
  * ONNX open standard could be used to [extract a library-independent neural network model + weights out of the torch implementation](https://pytorch.org/tutorials/advanced/super_resolution_with_onnxruntime.html).
  * [The PlaidML library includes an OpenCL backend and accepts ONNX models](https://github.com/plaidml/onnx-plaidml)
  * [There is an OpenCL implementation that covers all RaspberryPi devices](https://github.com/doe300/VC4CL)
  * Check if PlaidML library can access the GPU via OpenCL and modify the lister_service.py to use the ONNX model.
* Alternative to above: Swap RPi4 for a [Nvidia Jetson device](https://developer.nvidia.com/buy-jetson). This baby runs a Pascal-class GPU architecture, and should work out-of-the-box with Tensorflow and Torch.

## Screenshots

![image](https://user-images.githubusercontent.com/20412697/116463119-fbd96a80-a872-11eb-8d64-ac4f90a36791.png)
![image](https://user-images.githubusercontent.com/20412697/116463147-0693ff80-a873-11eb-84a2-ae3b36ff3559.png)

