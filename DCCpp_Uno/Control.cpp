#include "Control.h"
#include "PacketRegister.h"
#include "SerialCommand.h"
#include "DCCpp_Uno.h"
#include "phi_interfaces.h"

volatile RegisterList *mRegs;
Control *controls[MAX_MAIN_REGISTERS-1];
bool control_enabled[MAX_MAIN_REGISTERS-1];
char control_mapping[]={'P'}; // This is a list of names for button
byte control_pins[]={21};
phi_button_groups control_btns(control_mapping, control_pins, 1);
//phi_button_groups *control_btns;

Control** getControls() {
  return controls;
}

void initControls(volatile RegisterList *_mRegs, int power_pin) {
  mRegs=_mRegs;
  for (int i=0; i < MAX_MAIN_REGISTERS-1; i++) {
    controls[i] = createControl();
  }
//  char control_mapping[]={'P'}; // This is a list of names for button
//  byte control_pins[]={power_pin};
//  control_btns = new phi_button_groups(control_mapping, control_pins, 1);
  control_btns.set_repeat(10000); // We don't want power flicking on and off so only let it repeat once every 10 seconds
//  control_btns = the_btns;
//  Serial.println(the_btns.getKey());
//  Serial.print("BLAH1");
//  Serial.println(control_btns.getKey());
//  Serial.print("/BLAH1");
}

Control* createControl() {
  Control *control = (Control*) calloc(1, sizeof(Control));
  control->dir = 1;
  control->spd = 0;
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    control->readings[thisReading] = 0;
  }
  control->readIndex = 0;
  control->total = 0;
  control->average = 0;
  control->enabled = false;
  return control;
}

void enableControl(int reg, int loco_address, int dir_pin, int speed_pin){
  Control *control = controls[reg-1];
  control->loco_address = loco_address;
  control->dir_pin = dir_pin;
  control->speed_pin = speed_pin;
  pinMode(dir_pin, INPUT_PULLUP);
  control->enabled = true;
}

void handleControlChanges() {
  char key_press=control_btns.getKey();
//  Serial.print("BLAH");
//  Serial.println(key_press);
//  Serial.print("/BLAH");
  switch(key_press) {
    case NO_KEY:
    break;

    case 'P':
    int new_power;
    if (digitalRead(SIGNAL_ENABLE_PIN_MAIN) == HIGH) {
      new_power = LOW;
    } else {
      new_power = HIGH;
    }
    digitalWrite(SIGNAL_ENABLE_PIN_PROG,new_power);
    digitalWrite(SIGNAL_ENABLE_PIN_MAIN,new_power);
    if (new_power == HIGH) {
      INTERFACE.print("<p1>");
    } else {
      INTERFACE.print("<p0>");
    }
    break;

    default:
    break;
  }

  for (int i=0; i < MAX_MAIN_REGISTERS-1; i++) {
    Control *control = controls[i];
    if (control->enabled) {
      bool changed = false;

      int new_dir = digitalRead(control->dir_pin);
      if (control->dir != new_dir) {
        control->dir=new_dir;
        changed = true;
      }

      control->total = control->total - control->readings[control->readIndex];
      // read from the sensor:
      control->readings[control->readIndex] = analogRead(control->speed_pin);
      // add the reading to the total:
      control->total = (control->total + control->readings[control->readIndex]);
      // advance to the next position in the array:
      control->readIndex = control->readIndex + 1;

      // if we're at the end of the array...
      if (control->readIndex >= numReadings) {
        // ...wrap around to the beginning:
        control->readIndex = 0;
      }

      // calculate the average:
      control->average = control->total / (numReadings);

      int new_speed = control->average/8.1;
      if (control->spd != new_speed) {
        control->spd=new_speed;
        changed = true;
      }

      if (changed) {
        char comString[MAX_COMMAND_LENGTH+1];
        sprintf(comString, "%d %d %d %d\n", i+1, control->loco_address, control->spd, control->dir);
    //    Serial.print("Running command: < ");
    //    Serial.print(comString);
    //    Serial.println(" >");
        mRegs->setThrottle(comString);
      }
    }
  }
}
