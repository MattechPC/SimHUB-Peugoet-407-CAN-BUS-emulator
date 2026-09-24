# SimHUB Peugeot 407 CAN-BUS Emulator

The project was developed between 2021 and 2023. Its first publicly available version was a working instrument cluster from a Peugeot 207. Over time, I gradually gained a better understanding of CAN-BUS communication with the instrument cluster. Alongside adding support for new clusters, I continuously improved and fixed the code for the already supported ones.

<img width="600" height="338" alt="407_gif" src="https://github.com/user-attachments/assets/dd0b0cab-c7f0-4a87-bc22-da506cbfcffb" />


## Required Hardware

- Arduino Nano
- MCP2515
- 12V power supply
- Peugeot 407 instrument cluster (LCD display version)


## Installation

I strongly recommend uploading the code to the Arduino using the latest version of the Arduino IDE installed directly on your computer. I do **not** recommend using the Arduino IDE Portable included with SimHub.

### 1. Checking the connection between the computer and Arduino

Make sure that the Arduino is correctly detected by Windows. Open **Device Manager**, expand **Ports (COM & LPT)** and verify that your connected Arduino is listed correctly.

### 2. Installing the required libraries

Open the Arduino IDE libraries folder (by default `C:\Users\Your_User_Name\Documents\Arduino\libraries`) and copy all the libraries from the `arduino_libraries` ZIP file included in the downloaded package into this folder.

### 3. Compiling the code and uploading the NCalc formula

Compile and upload the code to the Arduino. Next, launch SimHub and go to **Arduino -> My Hardware**.

During the first launch, SimHub will ask whether you want to use a single Arduino board or whether your project will use multiple Arduino boards. I recommend selecting **Single Arduino**.

After a few seconds, verify that a device named **MattechPC Peugeot 407 V2.0** appears and connects successfully.

#### 4. Everything is ready

You can now launch your favorite game and enjoy the experience with a fully functional automotive instrument cluster.

**Note:** Some games require telemetry to be enabled, additional plugins to be installed, or other advanced configuration. All the necessary information regarding telemetry configuration can be found in the SimHub application.

## Debugging

The code includes a built-in debugging mechanism by default. Connect the anodes (+) of LEDs to outputs A0-A2.

The outputs indicate the following:

- A0 - Connection between the project and the instrument cluster
- A1 - Connection between the Arduino and SimHub
- A2 - Connection between the Arduino and MCP2515

If an error occurs, the corresponding output is pulled LOW and the LED turns off. **All LEDs ON = everything is working correctly.**

## PCB and 3D Printing

The project includes a dedicated PCB and a 3D-printed enclosure. Their use is optional. The STL files for the enclosure are included in the downloaded package.

The PCB features dedicated locations for the debugging LEDs, as well as an additional LED on the 12/24V power line, indicating that the power supply is operating correctly.

Behind the power connector, there are two positions for 1KΩ resistors. Behind the resistors, there are two solder jumpers. By soldering the jumper corresponding to the selected voltage, you configure the LED for either 12V or 24V operation.

<img width="500" alt="PCB" src="https://github.com/user-attachments/assets/d57e5b0a-54e0-4246-9746-a880db800608" />

<img width="500" alt="CLUSTER_PCB" src="https://github.com/user-attachments/assets/ca604e5d-b2c8-4450-81bf-3bca33a66298" />

#### ❗ WARNING ❗ Incorrect jumper configuration may cause the LED to operate incorrectly or may even result in permanent damage to the LED.

In the future, dedicated PCBs (either assembled or as DIY kits) and the enclosure will be available for purchase. For now: **work in progress.**

## YouTube Tutorials

I have created a complete tutorial covering how to connect and configure the instrument cluster. Check out the latest videos:

<a href="https://youtu.be/D8mY-5T7rYY"> <img width="640" alt="407_thumbnail" src="https://github.com/user-attachments/assets/d5760a96-43df-492e-a6d7-094b196952c6" /> </a>
<a href="https://youtu.be/9vEeve54UiU"> <img width="640" alt="207_thumbnail" src="https://github.com/user-attachments/assets/ae437022-710f-490d-be79-7bb75a509cc9" /> </a>
<a href="https://youtu.be/mzjBLN_IS14"> <img width="640" alt="207_update_thumbnail" src="https://github.com/user-attachments/assets/d4c24841-b09a-44ea-9b86-4edff9dcee9b" /> </a>
<a href="https://youtu.be/c1_7InaBueM"> <img width="640" alt="C3_thumbnail" src="https://github.com/user-attachments/assets/c591e6a1-2948-490f-bd2a-58c332c13f18" /> </a>
<a href="https://youtu.be/rEvpyTjFMHs"> <img width="640" alt="C3_update_thumbnail" src="https://github.com/user-attachments/assets/c0eb79a0-2e41-480e-ab2f-0a3e07f83af9" /> </a>
