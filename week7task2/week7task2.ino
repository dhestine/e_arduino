#include<SPI.h>

#define CS 5 // Define the pin for the chip 
#define ADC_CLK 1600000 // Clock speed for the SPI communication
#define ADC_VREF 3300 // ADC reference voltage in millivolts

// Define the variable to stoe the temperature reading
float temp;

void setup() {

  // Set the CS pin as an output and set it high
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  // Set the SPI settings for the ADC
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  SPI.begin();
  SPI.beginTransaction(settings);

  // Initializie the serial communication at 115200 baud
  Serial.begin(115200);

  // Wait for the serial communication to be established
  while(!Serial);
}

void loop() {

  // Read the temperature from the ADC
  uint8_t ch = 0;
  uint16_t adc_value = spi_adc(ch);

  // Convert ADC value to voltage
  float volt = 3.3 * adc_value/4095.0;

  // Convert voltage to temperature
  temp = (volt-0.5) * 100;

  // Print the temperature reading to the console
  Serial.print("Temperature in the room is ");
  Serial.print(temp, 2);
  Serial.println("deg. C.");

  // wait for 1 seconds before reading the temperature again
  delay(1000);
}

// Read ADC value using SPI
uint16_t spi_adc(uint8_t channel){

  // Build the command bits needed by the ADC
  uint8_t channelMSB = (channel & 0b00000100) >> 2;
  uint8_t  firstByte = (0b00000110) | channelMSB;
  uint8_t  SecondByte = channel << 6;

  uint8_t  firstByteMsk = 0x0F;
  
  // Check if the channel number is valid 
  if(channel>7) {

    // Print an error messsage if the channel number is invalid
    Serial.print("Invalid channel number");
    return 0xFF;
  }

// Set the CS pin low to enable the ADC
digitalWrite(CS, LOW);


SPI.transfer(firstByte); // Send command byte 1
uint8_t firstResult = SPI.transfer(SecondByte); // Read high part of result
uint8_t secondResult = SPI.transfer(0x0); // Read low part of result

// Extract the final result  from the first and second bytes
uint16_t finalResult = (firstResult & firstByteMsk) << 8;
finalResult |= secondResult;

// Return the final result
return finalResult;
}
