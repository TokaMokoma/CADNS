# This project implements a Car Accident Detection and Notification System (CADNS) using Arduino and Python.

## Prerequisites
Proteus Professional (https://getintopc.com/softwares/electrical-engineering/proteus-professional-2022-free-download/)

Arduino IDE (https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)

Jupyter Notebook (https://jupyter.org/install)

Twilio Account (Free Signup: https://www.twilio.com/try-twilio)
## Setup
Download and Install Software:

Install Proteus Professional.

Install Arduino IDE.

Install Jupyter Notebook.

Create a free Twilio account.

### Download Project Files:

Download the project source code (ZIP file named CADNS-main).

Extract the downloaded ZIP file.

### Configure Twilio Credentials:

Create a Python file named twilio_numbers.py inside the project directory.

In twilio_numbers.py, replace the following placeholders with your Twilio account information:

 account_sid = 'YOUR_ACCOUNT_SID'
 
 auth_token = 'YOUR_AUTH_TOKEN'
 
 twilio_number = 'YOUR_TWILIO_NUMBER'
 
 target_number = 'YOUR_TARGET_PHONE_NUMBER'
## Run Python Script:
Open Jupyter Notebook.

Locate and open the file named "MAIN_MAIN".

Run the Python script within the notebook.
### Arduino Setup
Open the folder named "Car_Accident_Detection_And_Notification_System_code".

Open the file named "Car_Accident_Detection_And_Notification_System_code.ino" with Arduino IDE.

Run (compile) the code in the Arduino IDE.

Copy the generated HEX file location displayed in the Arduino terminal.
### Configure Proteus Simulation:
Open the file named "Car_Accident_Detection_And_Notification_System_Circuit" in Proteus.

Right-click on the Arduino UNO microcontroller in the schematic.

Select "Properties".

In the properties window, locate the "Program File" field.

Paste the HEX file location you copied from Arduino IDE.

Run Simulation:

Run the simulation in Proteus.

Trigger Accident Simulation:

Adjust the sensor values in the Arduino code (refer to the thresholds within the code) to simulate an accident scenario. This will trigger the notification process.
