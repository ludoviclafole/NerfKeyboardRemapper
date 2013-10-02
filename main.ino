#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
uint8_t keys[21] = {0x5D, 0x9D, 0x1D, 0xDD, 0xFD, 0x3D, 0x1F, 0x57, 0x6F, 0x97, 0x67, 0x4F, 0xCF, 0xE7, 0x85, 0xEF, 0xC7, 0xA5, 0xBD, 0xB5, 0xAD};
uint8_t to[21] = {0x1A, 0x14, 0x04, 0x1B, 0x16, 0x1D, 0x06, 0x07, 0x08, 0x19, 0x09, 0x15, 0x05, 0x0A, 0x17, 0x11, 0x0B, 0x1C, 0x36, 0x0D, 0x18};

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}


uint8_t buf[8] = { 0 }; 	/* Keyboard report buffer */
  
void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFF) {
      buf[2] = getConvertedKey(results.value);
      Serial.write(buf, 8);
    } else {
      buf[2] = 0;
      Serial.write(buf, 8);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(200);
}

uint8_t getConvertedKey(int val){
  int value = val & 0x0000FF;
  for(int i = 0; i < 21; i++) {
    if(value == keys[i]) {
      return to[i];
    }
  }
  return 0;
}
