# PAN9520 ETU Webserver Camera Stream
[![Version badge](https://img.shields.io/badge/Version-0.0.1-green.svg)]()
[![Generic badge](https://img.shields.io/badge/Made_with-VSCode_/_PlatformIO-orange.svg)]()
[![Generic badge](https://img.shields.io/badge/Target-PAN9520_ETU-blue.svg)]()

This application for the PAN9520 ETU demonstrates a webserver that serves a camera live stream.

## Installation
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Open the "Extensions" menu - using the icon in the left vertical menu bar or by pressing CTRL+SHIFT+X
3. Search and start installation of the "PlatformIO IDE" extension. 
4. Wait for the installation to finish. This takes a while. Visual Studio Code must be restarted for the installation to take effect.
5. Clone this project with:
```
git clone --recursive $OUR_GIT_URL$
```
6. Use "File" -> "Open Folder" and select the project folder containing this application
7. Wait for all dependencies to be downloaded and installed automatically. This takes a while.

## Hardware setup
For this application a OV2640 camera must be connected to the camera interface labelled CAM.
https://www.seeedstudio.com/OV2640-Fisheye-Camera-p-4048.html

## Firmware build
1. Open the PlatformIO project task menu by clicking on the corresponding icon on the left side (Alien Head)
2. Navigate to "Project Tasks" -> "esp32-s2-kaluga-1" -> "General" and select "Build"
3. Wait until the project has been built. For the very first build the build time is huge because a lot of files from the SDK will be build. Following builds will be much faster.

## Flashing the firmware
1. Connect the PAN9520 ETU via the "USB Module" connector on the top left corner of the development board to the development PC.
2. Activate the download mode by pressing the "RST" button while holding the SW1 button pressed down. After releasing the "RST" button a new USB device may be recognized by the PC.
3. Open the PlatformIO project task menu by clicking on the corresponding icon on the left side (Alien Head)
4. Navigate to "Project Tasks" -> "esp32-s2-kaluga-1" -> "General" and select "Upload"
5. After upload the following error message is displayed in the terminal: "esptool.py can not exit the download mode over USB. To run the app, reset the chip manually." The development board needs to be reset manually by pressing the "RST" button to exit the download mode and start the application.

## Running the demo
1. Connect the PAN9520 ETU via the "USB Module" connector on the top left corner of the development board to the development PC.
2. Scan for WiFi access points on any remote device like mobile phone or PC.
3. Look out for the WiFi access point SSID "PAN9520LiveStream" and connect to it.
4. Open a webbrowser and access http://192.168.4.1 
5. Enjoy the video stream.

## Troubleshooting
If the application does not work as expected it is possible to inspect the setup by looking at the debug output of the system.

1. Connect the PAN9520 ETU via the "USB Debug/Serial" connector on the bottom left corner of the development board to the development PC.
2. Use a terminal applicaion like HTerm, Putty or Termite and open the debug COM port - this is usually the one with the highest COM port number - with 115200,8,N,1 configuration.
3. Carefully analyze the debug output.

# Camera not connected
If you receive the following message the camera is not connected to the development board correctly:
```
camera: Camera probe failed with error 0x105(ESP_ERR_NOT_FOUND)<27>[0m<\r><\n>
ESP_ERROR_CHECK failed: esp_err_t 0x105 (ESP_ERR_NOT_FOUND)
```
Solution: Please connect the camera correctly.
