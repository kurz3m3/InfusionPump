
/*
*   This project runs an infusion pump. Once started using a button, it will run for 5 seconds then stay off for 20 seconds, looping this process
*   until the user presses the button again.
*   
*   The pump will complete it's cycle even if the button is pressed in the middle of a loop.
*
* @author Harvey
* @date 11/7/2022
*/
int greenLED = 2; // LED set to pin 2
int redLED = 4;
int button = 3; // button set to pin 3
int motor = 5; // motor set to pin 6
int buttonInput = 0; // buttonInput set to 0 meaning not pressed
int thermPin = A0;
int thermValue = 0;

static bool pressedStatus;

/*
* Setup function.
* Initialize pins
*/
void setup() {
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(button,INPUT);
  pinMode(thermPin,INPUT);
  Serial.begin(9600);
  Serial.println("Program Reset"); 
}


/*
* Loop code
*/
void loop() {
  pumpMain();
  Serial.print("Temp:" + String(thermOutput()));
}


/*
* Checks if button was pressed, if so, run pump for 5 seconds, then turn pump off for 20 seconds and loop
* If pump wasn't pressed, keep pump OFF
*
* @author Harvey
* 11/05/2022
*/
void pumpMain(){
  if(isPressed()==true){
    pumpOn();
    delay(5000); // wait for 5 seconds with motor ON
    pumpOff();

    if(thermOutput()>=80){
      pressedStatus = false;
      Serial.println("EMERGENCY SHUTDOWN: TEMP EXCEEDED 80");
      pumpOff();
    }

    delay(20000); // Wait 20 seconds
  }
  else{
    pumpOff();
  }
}


/*
* Turn the pump on
* Turn the green LED on
*
*/
void pumpOn(){
  Serial.println("  Motor on  ");
  analogWrite(motor,255); // turn motor to max speed
  digitalWrite(greenLED,HIGH); // green LED ON
  digitalWrite(redLED,LOW);// red LED OFF
}


/**
* Turn the pump off
* Turn the green LED off, red LED ON
* Wait 20 seconds
*/
void pumpOff(){
  Serial.println("  Motor off");
  analogWrite(motor,0); // Turn motor OFF
  digitalWrite(greenLED,LOW); // turn green LED OFF
  digitalWrite(redLED,HIGH); // turn red LED ON
}


/*
* Check if button has been pressed
* If it has been pressed before, it will set it to false
*
*
*/
bool isPressed(){
  buttonInput = digitalRead(button); //. read button input
  
  if(buttonInput == 1 && pressedStatus == true){ // if button pressed and its already been pressed before
    Serial.println("pressed to false");
    pressedStatus = false; // set pressed to false
    return pressedStatus;
  }
  else if(buttonInput == 1 && pressedStatus == false){ // If button pressed
    Serial.println("pressed to true");
    pressedStatus = true; // set pressed to true
    return pressedStatus;
  }
  return pressedStatus;
}


float thermOutput(){
  thermValue=analogRead(thermPin);

  int R25 = 10000; //Ohms
	float a1 = 3.354016E-3;
	float b1 = 2.56985E-4;
	float c1 = 2.620131E-6;
	float d1 = 6.383091E-8;

  float voltage = float(thermValue)*(5000.0/1024.0); //units are milivolts
  float Rdivider = 10000; //Resistance in Ohms of the other resistor.
  float Rtherm = Rdivider*((5000.0/voltage) -1); //Voltage divider equation
	
  //Thermistor resistance-to-temperature conversion equation (from datasheet)
	float Tkelvin = 1/(a1 + b1*log(Rtherm/R25) \
		+ c1*log(Rtherm/R25)*log(Rtherm/R25) \
		+ d1*log(Rtherm/R25)*log(Rtherm/R25)*log(Rtherm/R25));

  //Temperature conversions
	float Tcelsius = Tkelvin - 273.15;
	float Tfahren = (Tcelsius*(9.0/5.0))+32.0;

  return Tfahren;
}
