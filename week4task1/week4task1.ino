int potentiometer = A2;   // Analog pin connect to the potentiometer

void setup() {
  Serial.begin(9600);     // start serial communication

  // waiting for serial port to connect and be ready
  while (!Serial);        
}

 // run loop continuously
void loop() {

  // Read ADC value from Potentiomteter
  uint16_t rawADC = analogRead(potentiometer);

  // Convert ADC To VOLTAGE
  float voltage = 3.3 * rawADC / 1023.0;

  // Print the raw ADC value 
  Serial.print("ADC value = ");
  Serial.println(rawADC);

  // Print the calculated voltage
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.println(" V");

  // Delay for 1 seconds before reading again
  delay(1000);
}