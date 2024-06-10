#include <NecDecoder.h>

#define IR_SIG_1 0xFF30CF
#define IR_SIG_2 0xFF18E7
#define IR_SIG_3 0xFF7A85
#define IR_SIG_4 0xFF10EF
#define IR_SIG_EXIT 0xFFE21D
#define IR_SIG_ENTER 0xFFC23D
#define IR_SIG_PREVIOUS 0xFF22DD
#define IR_SIG_NEXT 0xFF02FD
#define IR_SIG_SNOOZE 0xFF906F

enum IR_pressed {
  IR_BUTTON1,
  IR_BUTTON2,
  IR_BUTTON3,
  IR_BUTTON4,
  IR_BUTTON_EXIT,
  IR_BUTTON_ENTER,
  IR_BUTTON_PREVIOUS,
  IR_BUTTON_NEXT,
  IR_NOT_PRESSED,
  IR_UKNOWN,
  IR_SNOOZE
};

void irIsr();

enum IR_pressed get_pressed_button();