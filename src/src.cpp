#include <OneWire.h>

OneWire ibutton (2); // iButton connected on PIN 2.

byte buffer[8];

void setup(){
  Serial.begin(115200);
  Serial.println("Hello"); // print new line
}

void loop(){
  // Wait for a 1-Wire Device and, as soon as present, assign the RXed bytes to the buffer.
  while (!ibutton.search(buffer)){
     ibutton.reset_search();
     delay(250);
  }
  
  // At this point, a 1-Wire Device is found.
  Serial.println("1-Wire Device Detected, ID is:");
  for (int x=0; x<8; x++){
    Serial.print(buffer[x],HEX);
    Serial.print(" ");
  }
  Serial.print("\n");
  
  // Check if this is an iButton
  if (buffer[0] != 0x01 && buffer[0] != 0x33) {
    Serial.println("Device is not an iButton");
  } else {
    Serial.println("Device is an iButton");
  }
  
  // Check if CRC matches in RXed bytes
  if (ibutton.crc8(buffer, 7) != buffer[7]) {
      Serial.println("CRC is not valid!");
  }
  
  Serial.println("Done.\n\n");  
}
