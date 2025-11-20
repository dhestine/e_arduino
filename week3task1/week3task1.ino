int myLed = 6; //Pin number for the LED output
int input = 0; // variable to store incoming serial data

void setup() {

  // Configure the LED pin as an output
  pinMode(myLed,OUTPUT);

  // Initialize serial communication at 115200 buad rate
  Serial.begin(115200);

  //waiting for serial port to connect
  while(!Serial);

  // send confirmation that serial is ready
  Serial.println("Serial is ready!");
}

void loop() {
  
  //check if data has been receievd 
  if(Serial.available() > 0){
    
    // Read the receieved character
    input = Serial.read();

    // Check if input is a letter ( lowercase OR uppercase )
    if(input >= 'a' && input <= 'z' || input >= 'A' && input <= 'Z'){
      Serial.println("Character Pressed "); // Notify user that a number was detected
      digitalWrite(myLed,HIGH); // Turn LED ON for alphabetic input
    }

    // Check if input is a numeric digit (0-9)
    else if(input >= '0' && input <='9'){
      Serial.println("Number Pressed "); // Notify user that a number was detected
      digitalWrite(myLed,LOW); // Turn LED OFF for numeric input
    }

    // wait for outgoing serial data transmission to complete
    Serial.flush();
  }

  // delay to stabilize loop
  delay(5);
}

