/*
*   This project runs an infusion pump. Once started using a button, it will run for 5 seconds then stay off for 20 seconds, looping this process
*   until the user presses the button again.
*   
*   The pump will complete it's cycle even if the button is pressed in the middle of a loop.
*
* @author Harvey
* @date 11/7/2022
*/


int LED = 2; // LED set to pin 2
int button = 3; // button set to pin 3
int motor = 6; // motor set to pin 6
int buttonInput = 0; // buttonInput set to 0 meaning not pressed

/*
* Setup function.
* Initialize pins
*/
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT);
}


/*
* Loop code
*/
void loop() {
  pumpMain();
}




/*
* Turn motor ON for 5 seconds then OFF for 20 seconds, this will loop.
*
* @author Harvey
* 11/05/2022
*/

void pumpMain(){
  if(isPressed()==true){
    analogWrite(motor,255); // turn motor to max speed
    digitalWrite(LED,HIGH); // LED ON
    delay(5000); // wait for 5 seconds withh motor ON
    anaglogWrite(motor,0); // Turn motor OFF
    delay(20000); // Wait 20 seconds
  }
  else{
    analogWrite(motor,0); // motor off
    digitalWrite(LED,LOW); // LED OFF
  }
}



/*
* Check if button has been pressed
* If it has been pressed before, it will set it to false
*
* TLDR: Toggles ON / OFF
*/

bool isPressed(){
  static bool pressedStatus = false; // One copy of pressed status, initialize to false
  buttonInput = digitalRead(button); //. read button input

  if(buttonInput == 1){ // If button pressed
    pressedStatus = true; // set pressed to true
  }
  else if(buttonInput == 1 && pressedStatus == true){ // if button pressed and its already been pressed before
    pressedStatus = false; // set pressed to false
  }
  return pressedStatus;
}

