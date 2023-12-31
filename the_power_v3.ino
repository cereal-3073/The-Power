#include "MIDIUSB.h"
#include <Keypad.h>

const byte ROWS = 5;
const byte COLS = 8;
// Funciona al revez 
// TODO: Corregir notas al revez
char keys[ROWS][COLS] = {
  {36,37,38,39,40,41,42,43},
  {44,45,46,47,48,49,50,51},
  {52,53,54,55,56,57,58,59},
  {60,61,62,63,64,65,66,67},
  {68,69,70,71,72,73,74,75}
};
byte rowPins[ROWS] = {A3,A2,A1,A0,15}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {2,3,4,5,6,7,8,9}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
}


void loop() {
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {
                    case PRESSED:
                    //digitalWrite(MIDI_LED, HIGH);
                    //Serial.print(kpd.key[i].kchar,DEC);
                    //MIDI.sendNoteOn(kpd.key[i].kchar, 127, MIDI_CHANNEL);
                    //Serial.println(" Pressed");

                    noteOn(0, kpd.key[i].kchar, 64);
                break;
                    case HOLD:
                break;
                    case RELEASED:
                    noteOff(0, kpd.key[i].kchar, 64);
                break;
                    case IDLE:
                break;
                }
            }
        }
    }
    MidiUSB.flush();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
