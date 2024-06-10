#include "IRremote.h"

NecDecoder ir;

void irIsr() {
  ir.tick();
}

/// @brief return pressed button on the remote
enum IR_pressed get_pressed_button() {
  if (ir.available()) {
    switch (ir.readPacket())
      {
      case IR_SIG_1: return IR_BUTTON1;
      case IR_SIG_2: return IR_BUTTON2;
      case IR_SIG_3: return IR_BUTTON3;
      case IR_SIG_4: return IR_BUTTON4;
      case IR_SIG_EXIT: return IR_BUTTON_EXIT;
      case IR_SIG_ENTER: return IR_BUTTON_ENTER;
      case IR_SIG_NEXT: return IR_BUTTON_NEXT;
      case IR_SIG_PREVIOUS: return IR_BUTTON_PREVIOUS;
      case IR_SIG_SNOOZE: return IR_SNOOZE;
      default: return IR_UKNOWN;
    }
  } else return IR_NOT_PRESSED;
}
