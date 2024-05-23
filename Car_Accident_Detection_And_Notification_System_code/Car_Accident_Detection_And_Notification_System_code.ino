
// include the library code:
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <LiquidCrystal.h>
#define kpa2atm 0.00986923267  //conversion factor from kilopascals to atmospheres.

// dellaring the vabratin value variable
int  VibrationReading ;
// the maximum number of passengers a car can fit
int maxPassengers = 3;
// the current number of passengers in a car
int numPassengers = 0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 6, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// intializing counter so that the an accident will not be detected due to intial acceleration 
bool counter = false;

// intializing the pin for the pressure sensor
int pressurePin = A5;

int  val;
float pkPa; // pressure in kPa(kilo pascals)
float pAtm; // pressure in Atm (atmosphere)

// intializing the pins for the three potentiometer accelerometer
 const int  X_PIN = A2;
 const int  Y_PIN = A3;
 const int  Z_PIN = A4;

// the array to store recent and curerent acceleration value readings
   float Recent_ax[2]= {0,0}; // array of size 2 for Recent_ax
   float Recent_ay[2]= {0,0};// array of size 2 for Recent_ay
   float Recent_az[2]= {0,0};// array of size 2 for Recent_az
   int i = 0; // an iterator for the recent value arrays

// Temperature sensor pin
const int Temperature_sensor = A0;

// Temperature sensor pin
const int Vibration_sensor = A1;

const int SWITCH = 3; // the cancel switch
volatile bool State = LOW;// state of the interrupt to be updated by the interrupt
volatile bool ButtonIsPressed = LOW;


float Temperature_reading;
float Voltage_reading;

// intializing acceleration burst data
float difference_ax; 
float difference_ay;
float difference_az;

// a function to get the current time
char* get_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char *time_str = malloc(sizeof(char) * 9);  // Allocate memory for time string

    // Get the current time in UTC
    time(&rawtime);
    timeinfo = gmtime(&rawtime);

    // Adjust for South African Standard Time (UTC+2)
    timeinfo->tm_hour = (timeinfo->tm_hour + 2) % 24;
    if (timeinfo->tm_hour < 0) {
        timeinfo->tm_hour += 24;  // Handle negative hours
        timeinfo->tm_mday += 1;   // Increment the day
    }

    sprintf(time_str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    return time_str;
}


void ContactingEmergencyServices(){
  lcd.setCursor(0,1);
    lcd.print("calling Emergency Services");
   // Serial.print("Temperature: ");   remeber to fix this 
    Serial.println(Temperature_reading);
   // Serial.print("Burst in x_axis: ");
    Serial.println(difference_ax);
   // Serial.print("Burst in Z_axis: ");
    Serial.println(difference_ay);
   // Serial.print("Burst in x_axis: ");
    Serial.println(difference_az);
   // Serial.print("Vibration Value: ");
    Serial.println(VibrationReading);
    //Serial.print("The number of passengers is: ");
    Serial.println(numPassengers);
    char *time = get_time();
    Serial.println(time);
    free(time);
    Serial.print("end");
    
    delay(1000);
    
     lcd.clear();
     
}

void Normal(){
   lcd.setCursor(0,0);
    lcd.print("Normal");
     delay(1000);
     lcd.clear();
}

void stopProgram() {
    // Stop the program with an exit status of 0
    exit(0);
}

// interrupt switch fuction
void switchPressed ()
{
 State = digitalRead(SWITCH);
 if(State == HIGH)
  ButtonIsPressed = HIGH;
  else
  ButtonIsPressed = LOW;
  
}



void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:

 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("CADNS");
  
  //configuring pin A0 as an input for the temerature sensor
  pinMode(Temperature_sensor,INPUT);

  pinMode( pressurePin, INPUT);
  
  // configuring pin 3 as input for the delay switch
   pinMode (SWITCH, INPUT);
   
   // configuring pin A1 as an input for the vibration sensor
   pinMode(Vibration_sensor,INPUT);

    // attach interrupt handler for the delay switch
  attachInterrupt (digitalPinToInterrupt (SWITCH), switchPressed, CHANGE); 
  
  // Accelerometer pins
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(Z_PIN, INPUT);
}

void loop() {

val = analogRead(pressurePin); // reading the pressure sensor rawvalue
pkPa = ((float)val/(float)1023+0.095)/0.009; //converting pressure to kilo pascals
pAtm = kpa2atm*pkPa; //converting pressure to atmosphere

//for(int num = 0; num <= maxPassengers; num++){
  if( pkPa >= 100.0)
    numPassengers = 1;
//}
  // Reading the vibration Value
 VibrationReading = analogRead(Vibration_sensor);

// Reading the voltage from the LM35
Voltage_reading = analogRead(Temperature_sensor);
// converting Volatage into degreees celcius
 Temperature_reading = (Voltage_reading*500)/1023;

// Reading the X,Y,Z values from the three potentiometers
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  int z = analogRead(Z_PIN);

//Calculating the current acceleration value reading
float ax = ((float)x / 1023 * 90)- 45; // map this to -45 to 45 m/s^2
float ay = ((float)y / 1023) * 90 - 45; // map this to -45 to 45 m/s^2
float az = ((float)z / 1023) * 90 - 45; // map this to -45 to 45 m/s^2

  
// storing the current acceleration values as recent in the recent array at index i
   Recent_ax[i] = ax;
   Recent_ay[i] = ay;
   Recent_az[i] = az;
  i = (i+1) % 2; // making i to be between 0 and one;

  // calculating the difference in accelation every second between current and recent
   difference_ax =abs(Recent_ax[1] - Recent_ax[0]); 
   difference_ay =abs(Recent_ay[1] - Recent_ay[0]); 
   difference_az =abs(Recent_az[1] - Recent_az[0]); 

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // printing the number of passengers in the car
  lcd.print("# of passe:");
  lcd.print(numPassengers);
  delay(1000);
  lcd.clear();
   
  // printing the Temperature reading
  lcd.print("Temp");
  lcd.print(Temperature_reading);
  delay(1000);
  lcd.clear(); 

  // printing the vibration reading
  lcd.print("Vibration");
  lcd.print(VibrationReading);
  delay(1000);
  lcd.clear();
  
  // printing the X axix acceleration reading reading
   lcd.print("Acel in X: ");
  lcd.print(ax);
  lcd.setCursor(0, 1);
  lcd.print("Burst in X: ");
  lcd.print(difference_ax);
  delay(1000);
  lcd.clear();

  // printing the Y axix acceleration reading
   lcd.print("Acel in Y: ");
  lcd.print(ay);
  lcd.setCursor(0, 1);
  lcd.print("Burst in Y: ");
  lcd.print(difference_ay);
  delay(1000);
  lcd.clear();

  // printing the Z axix acceleration reading
   lcd.print("Acel in Z: ");
  lcd.print(az);
  lcd.setCursor(0, 1);
  lcd.print("Burst in z: ");
  lcd.print(difference_az);
  delay(1000);
  lcd.clear();


 //Serial.println(Temperature_reading);
   
 

  delay(2000); // wait for a second
  
  // definate accident
  if(difference_ax >= 10 || difference_ay >= 10 || difference_az >= 10 || Temperature_reading >= 60||VibrationReading >= 1023){
    
     
    if( counter == true){
      lcd.setCursor(0,0);
    lcd.print("accident detected");
     delay(1000);
      ContactingEmergencyServices();
       stopProgram();}
     else
      counter = true;  
  }
// not a definate acciden
  else if ((Temperature_reading >= 50 && Temperature_reading < 60)||(VibrationReading >= 576 && VibrationReading < 1023)){
    lcd.setCursor(0,0);
    lcd.print("Posiible accident");
     delay(1000);
     lcd.clear();
     
     lcd.setCursor(0,0);
     lcd.print("contacting emergency");
     lcd.setCursor(0,1);
     lcd.print("in 2 minutes");
     delay(1000);
     lcd.clear();
     
  // from the interrupt if the button is pressed
     if(ButtonIsPressed == HIGH){
      Normal();
      
     }
     
  //  from the interrupt if the button is NOT pressed  
     else{
      delay(2000);
     ContactingEmergencyServices();
     
     }
     
      
  }
  
  else{
   Normal();
  }

 
}
