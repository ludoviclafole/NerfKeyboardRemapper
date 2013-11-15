#include <hidboot.h>
#include <usbhub.h>
#include <LiquidCrystal.h>

#define FORCE_SHIFT 0x100
#define FORCE_ALTGR 0x200
#define PURIFY 0xFF
#define LETTERS_START 0x04
#define LETTERS_END 0x1D
#define LETTERS_CNT 26
#define NUMBERS_START 0x1E
#define NUMBERS_END 0x27
#define NUMBERS_CNT 10
#define SPE_START 0x2D
#define SPE_END 0x38
#define SPE_CNT 12
#define SHIFT 0x02
#define UNSHIFT 0xDD
#define GRR 0x40
#define UNGRR 0xBF


uint16_t invShift(uint16_t v) {
  return v + FORCE_SHIFT;
}
uint16_t grr(uint16_t v){
  return v + FORCE_ALTGR;
}

boolean isShifted(uint16_t v){
  return (v & FORCE_SHIFT);
}

boolean isGrr(uint16_t v){
  return (v & FORCE_ALTGR);
}

uint8_t purify(uint8_t v){
  return v & PURIFY;
}

LiquidCrystal lcd(2,3,4,5,6,7);
uint16_t letters[LETTERS_CNT] = { 0x14, 0x1B, 0x0D, 0x08, invShift(0x36), 0x18, 0x0C, 0x07, 0x06, 0x0B, 0x17, 0x11, 0x33, 0x05, 0x15, 0x0F, 0x21, 0x13, 0x12, 0x1C, 0x0A, 0x0E, 0x10, 0x04, 0x09, 0x36};
uint16_t shiftLetters[LETTERS_CNT] = { 0x14, 0x1B, 0x0D, 0x08, 0x64, 0x18, 0x0C, 0x07, 0x06, 0x0B, 0x17, 0x11, 0x33, 0x05, 0x15, 0x0F, invShift(0x20), 0x13, 0x12, 0x1C, 0x0A, 0x0E, invShift(0x64), 0x04, 0x09, invShift(0x37)};
uint16_t numbers[NUMBERS_CNT] = {invShift(0x1E), invShift(0x1F), invShift(0x20), invShift(0x21), invShift(0x22), invShift(0x23), invShift(0x24), invShift(0x25), invShift(0x26), invShift(0x27)};
uint16_t shiftNumbers[NUMBERS_CNT] = {invShift(0x38), grr(0x27), grr(0x20), invShift(0x30), 0x34, invShift(0x2F), invShift(0x1E), invShift(0x31), invShift(0x22), invShift(0x2D)};
uint16_t specials[SPE_CNT] = {grr(0x22), grr(0x2D), invShift(0x37), 0x2E, grr(0x25), 0x32, 0x16, 0x23, grr(0x24), 0x1D, 0x19, 0x1A};
uint16_t shiftSpecials[SPE_CNT] = {grr(0x21), grr(0x2E), 0x10, 0x2E, grr(0x23), 0x32, 0x16, invShift(0x25), grr(0x1F), 0x1D, 0x19, 0x1A};

void printOnScreen(uint8_t *buf,uint8_t line) {
  for(uint8_t i = 0; i < 8; i++) {
      lcd.setCursor(i*2,line);
      lcd.print(buf[i],HEX);
  }
}

void putKey(uint8_t *buf,uint16_t array[],uint16_t shiftArray[], uint8_t i, uint8_t start) {
      if(buf[0] & 0x22) {
        uint16_t t = shiftArray[buf[i]-start];
        buf[i] = purify(t);
        if(isGrr(t)) {
          buf[0] = buf[0] | GRR;
          buf[0] = buf[0] & UNSHIFT;
        } else if(isShifted(t)) {
          buf[0] = buf[0] & UNSHIFT;
        }
      } else {
        uint16_t t = array[buf[i]-start];
        buf[i] = purify(t);
        if(isGrr(t)) {
          buf[0] = buf[0] | GRR;
          buf[0] = buf[0] & UNSHIFT;
        } else if(isShifted(t)) {
          buf[0] = buf[0] | SHIFT;
        }
      }
}

void mapKeys(uint8_t *buf){
  for(int i = 2; i < 8; i++) {
    uint8_t v = buf[i];
    if(v >= LETTERS_START && v <= LETTERS_END) {
      putKey(buf, letters, shiftLetters, i, LETTERS_START);
    } else if(v >= NUMBERS_START && v <= NUMBERS_END) {
      putKey(buf, numbers, shiftNumbers, i, NUMBERS_START);
    } else if(v >= SPE_START && v <= SPE_END) {
      putKey(buf, specials, shiftSpecials, i, SPE_START);
    }
  }
}

class KbdRptParser : public KeyboardReportParser
{
  public:
        void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

void KbdRptParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    lcd.clear();
    // Input
    printOnScreen(buf,0);
    
    lcd.setCursor(2,0);
    lcd.print(len, HEX);
    
    mapKeys(buf);
    
    // Output
    printOnScreen(buf,1);
    Serial.write(buf,8);
}

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);


uint32_t next_time;

KbdRptParser Prs;

void setup()
{
    Serial.begin( 9600 );
    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");
    lcd.begin(16, 2);  
    lcd.write("Start");
    
    delay( 200 );

    next_time = millis() + 5000;
    HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
}

void loop()
{
    Usb.Task();
}



