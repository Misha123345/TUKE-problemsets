#include <Arduino.h>
#include <EEPROM.h>

#include "rtc_wrapper.h"
#include "sensors.h"
#include "lcd_wrapper.h"
#include "states.h"
#include "config.h"
#include "melodies.h"
#include "IRremote.h"

bool check_alarm();

/**
 * Holds combination of pressed buttons.
 */
volatile byte btn_state;

/**
 * ISR for button press.
 *
 * This function is executed, when button is pressed. The global variable
 * `btn_state` is then set according to the combination of pressed buttons.
 */
void on_button_press()
{
  btn_state = 0;

  if (digitalRead(BTN1_PIN) == LOW)
  {
    btn_state |= BTN1_PRESSED;
  }

  if (digitalRead(BTN2_PIN) == LOW)
  {
    btn_state |= BTN2_PRESSED;
  }

  if (digitalRead(BTN3_PIN) == LOW)
  {
    btn_state |= BTN3_PRESSED;
  }

  if (digitalRead(BTN4_PIN) == LOW)
  {
    btn_state |= BTN4_PRESSED;
  }
}

void setup()
{
  // needed from original main() function
  init();

  Serial.begin(9600);
  // while(!Serial.available()){
  //     delay(100);
  // }

  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);
  pinMode(BTN4_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), on_button_press, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), irIsr, FALLING);

  // init alarm clock modules
  lcd_init();
  clock_init();
  sensors_init();
}


int main()
{
  setup();

  // init
  enum state state = CLOCK;
  bool is_alarm;
  enum IR_pressed ir_pressed = IR_NOT_PRESSED;

  // main loop
  for (;;)
  {
    ir_pressed = get_pressed_button();
    if (ir_pressed == IR_BUTTON1) btn_state = BTN1_PRESSED;
    if (ir_pressed == IR_BUTTON2) btn_state = BTN2_PRESSED;
    if (ir_pressed == IR_BUTTON3) btn_state = BTN3_PRESSED;

    if (btn_state == BTN1_PRESSED) state = CLOCK;
    else if (btn_state == BTN2_PRESSED) state = SHOW_ENV;
    else if (btn_state == BTN3_PRESSED) state = SETTINGS;
    else if (btn_state == BTN4_PRESSED) state = FACTORY_RESET;
    
    EEPROM.get(IS_ALARM_ADRESS, is_alarm);
    if (is_alarm && check_alarm()) state = ALARM; 

    switch (state)
    {
    case CLOCK: {
      state = state_clock(is_alarm); 
      break;
    }

    case SHOW_ENV: {
      state = state_show_env(); 
      break;
    }

    case FACTORY_RESET: {
      state = state_factory_reset(); 
      btn_state = BTN1_PRESSED;
      break;
    }

    case ALARM: {
      state = state_alarm(); 
      btn_state = BTN1_PRESSED; 
      break;
    }

    case SETTINGS: {
      state = state_settings(); 
      btn_state = BTN1_PRESSED; 
      break;
    }
    }
  }
}

/// @brief Checks if the current time matches the stored alarm time.
/// @return True if the current time matches the alarm time, otherwise false.
bool check_alarm() {
  struct dt time_now = now();
  struct dt alarm_time;
  EEPROM.get(ALARM_ADRESS, alarm_time);
  if (alarm_time.year == time_now.year &&
      alarm_time.month == time_now.month &&
      alarm_time.day == time_now.day &&
      alarm_time.hours == time_now.hours &&
      alarm_time.minutes == time_now.minutes
  ) return true;
  else return false;
}