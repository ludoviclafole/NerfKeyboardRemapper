#include <hidboot.h>
#include <usbhub.h>

class KbdRptParser : public KeyboardReportParser
{
        void PrintKey(uint8_t mod);
        void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
protected:
        virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

	virtual void OnKeyDown	(uint8_t mod, uint8_t key);
	virtual void OnKeyUp	(uint8_t mod, uint8_t key);
	virtual void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m)
{
    MODIFIERKEYS mod;
    *((uint8_t*)&mod) = m;
    
    Serial.write((uint8_t*) m, 8);
};

void KbdRptParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    Serial.write(buf, 8);
}

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
    PrintKey(mod);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {
    PrintKey(after);
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
    PrintKey(mod);
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
};

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

    delay( 200 );

    next_time = millis() + 5000;

    HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
}

void loop()
{
    Usb.Task();
}

