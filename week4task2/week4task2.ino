int tmp36 = A2;


void setup() {

// Initialize serial communication at 9600 baud rate
Serial.begin(9600);

// Wait for serial port to connect and be ready
while(!Serial);

// set ADC resolution to 12-bit
analogReadResolution(12);
}


void loop() {

// read ADC value 
uint16_t rawADC = analogRead(tmp36);

// Convert raw ADC value to voltage
float voltage = 3.3*rawADC/4095.0;

// Convert VOLTAGE to TEMPERATURE
float temperature = (voltage-0.5)*100;

// Print temperature result to Serial Monitor
Serial.print("Room Temperature = ");
Serial.print(temperature);
Serial.println(" degree celcius.");

// wait 1000 milliseconds before next reading
delay(1000);
}