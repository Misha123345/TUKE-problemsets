#include <EEPROM.h>

#include "states.h"
#include "config.h"
#include "lcd_wrapper.h"
#include "sensors.h"
#include "rtc_wrapper.h"
#include "stdio.h"
#include "melodies.h"
#include "IRremote.h"

/// @brief Displays the current time and date on the screen, and updates every 0.5 seconds.
/// @param is_alarm - If true, indicates an active alarm.
/// @return CLOCK - Returns the clock state.
enum state state_clock(bool is_alarm) {
  char time[9], date[11];
  sprintf(time, "%02d:%02d:%02d", get_hours(), get_minutes(), get_seconds());
  sprintf(date, "%02d.%02d.%4d", get_day(), get_month(), get_year());
  // update information on the screen every 0.5 seconds
  delay(500);
  lcd_clear();
  lcd_print_at(0, 4, time);
  if (is_alarm) lcd_print_at(0, 15, 0);
  lcd_print_at(1, 3, date);
  return CLOCK;
}

/// @brief Resets all information to factory settings.
void factory_reset() {
  struct dt reset_time = FACTORY_RESET_TIME;
  EEPROM.put(IS_ALARM_ADRESS, false);
  EEPROM.put(MELODY_ADRESS, 0);
  EEPROM.put(ALARM_ADRESS, reset_time);
  set_datetime(reset_time.day, reset_time.month, reset_time.year, reset_time.hours, reset_time.minutes, reset_time.seconds);
}

/// @brief Performs a factory reset when button 4 is pressed for a set duration.
/// @return CLOCK - Returns the clock state after reset.
enum state state_factory_reset() {  
  long int last_time = millis();
  char buffer[2];
  lcd_clear();

  lcd_print_at(0, 1, "FACTORY RESET");
  while (!digitalRead(BTN4_PIN)) {
    if (millis() - last_time > FACTORY_RESET_INTERVAL) {
      factory_reset();
      return CLOCK;
    }
    sprintf(buffer, "%ld", 3 - round((millis() - last_time)) / 1000);
    lcd_print_at(1, 8, buffer);
    delay(250);
  }

  return CLOCK;
}

/// @brief Sets the alarm to snooze for 5 more minutes.
void snooze() {
  struct dt alarm_time = now();
  if ((alarm_time.minutes += 5) >= 60) {
    alarm_time.minutes %= 60;
    alarm_time.hours++;
  }
  EEPROM.put(ALARM_ADRESS, alarm_time);
  lcd_clear();
  lcd_print_at(0, 6, "Okay");
  lcd_print_at(1, 1, "Five More Mins");
  delay(2000);
}

/// @brief Handles the alarm state, playing a melody and checking for user inputs to stop or snooze the alarm.
/// @return CLOCK - Returns the clock state after handling the alarm.
enum state state_alarm() {
  struct dt alarm_time; EEPROM.get(ALARM_ADRESS, alarm_time);
  bool is_alarm; EEPROM.get(IS_ALARM_ADRESS, is_alarm);
  byte melody; EEPROM.get(MELODY_ADRESS, melody);
  
  lcd_clear();
  lcd_print_at(0,4, "ALARM!!!");

  enum IR_pressed ir_pressed  = IR_NOT_PRESSED;
  int current_note = 0;
  unsigned long last_time = 0;
  delay(200);
  while (digitalRead(BTN1_PIN) && digitalRead(BTN2_PIN) && digitalRead(BTN3_PIN) && (ir_pressed == IR_NOT_PRESSED || ir_pressed == IR_SIG_SNOOZE)) {
    ir_pressed = get_pressed_button();
    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_SNOOZE) {
      snooze();
      return CLOCK;
    }

    switch (melody){
    case DEFAULT_MELODY: play_default(&current_note, &last_time); break;
    case STAR_WARS: play_star_wars(&current_note, &last_time); break;
    case CALM_MELODY: play_calm_song(&current_note, &last_time); break;
    }
  }
  
  EEPROM.put(IS_ALARM_ADRESS, false);
  return CLOCK;
}

/// @brief Displays the current temperature and humidity on the screen, updating every 0.5 seconds.
/// @return SHOW_ENV - Returns the environment display state.
enum state state_show_env() {
  // reads temperature and humidity values from the sensors every 0.5 seconds and displays them on the screen
  delay(500); 
  lcd_clear();
  char temp_buff[12], hum_buff[14];
  sprintf(temp_buff, "Temp: %.1f", get_temperature());
  sprintf(hum_buff, "Humidity: %d%%", get_humidity());
  lcd_print_at(0,0, temp_buff);
  lcd_print_at(1,0,hum_buff);
  return SHOW_ENV;
}

// checks whether the year is leap year
bool is_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// returns the number of days in a given month and year
short days_in_month(short month, int year) {
  switch (month) {
    case 4: case 6: case 9: case 11: return 30;
    case 2: return is_leap_year(year) ? 29 : 28;
    default: return 31;
  }
}


/// @brief print date on the LCD screen 
/// @param dt - date to be displayed
void print_date_string(struct dt dt) {
  char date_buffer[11];
  sprintf(date_buffer, "%4d.%02d.%02d", dt.year, dt.month, dt.day);
  lcd_clear();
  lcd_print_at(0, 3, date_buffer);
}

/// @brief changes a specific date component (year, month, or day)
/// @param dt - status of the current time setting
/// @param component - which date component should be changed
/// @return false - if the user wants to continue setting, otherwise true
bool set_date_component(struct dt* dt, enum date_component component) {
  // get days in current month
  short days = days_in_month(dt->month, dt->year);
  enum IR_pressed ir_pressed = IR_NOT_PRESSED;
  unsigned long last_time = 0;
  // pressing buttons 2 and 3 changes the specified date component (YEAR, MONTH, DAY), pressing button 1 saves the specified value
  // pressing button 4 exits the setting mode without saving
  while (digitalRead(BTN1_PIN) && ir_pressed != IR_BUTTON_ENTER) {
    ir_pressed = get_pressed_button();
    if ((!digitalRead(BTN2_PIN) || ir_pressed == IR_BUTTON_NEXT) && (millis() - last_time) > 200) {
      last_time = millis();
      switch (component) {
        case YEAR: if (dt->year < 2047) dt->year++; break;
        case MONTH: dt->month = (dt->month % 12) + 1; break;
        case DAY: dt->day = (dt->day % days) + 1; break;
      }
      print_date_string(*dt);
    }
    if ((!digitalRead(BTN3_PIN) || ir_pressed == IR_BUTTON_PREVIOUS) && (millis() - last_time) > 200) {
      last_time = millis();
      switch (component) {
        case YEAR: if (dt->year > 2000)dt->year--; break;
        case MONTH: dt->month = (dt->month - 1) < 1 ? dt->month + 11 : dt->month - 1; break;
        case DAY: dt->day = (dt->day - 1) < 1 ? dt->day + days - 1 : dt->day - 1; break;
      }
      print_date_string(*dt);
    }
    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_BUTTON_EXIT) return true; 
  }
  return false;
}

/// @brief print time on the LCD screen 
/// @param dt - time to be displayed
void print_time_string(struct dt dt) {
  char time_buffer[6];
  sprintf(time_buffer, "%02d:%02d", dt.hours, dt.minutes);
  lcd_clear();
  lcd_print_at(0, 5, time_buffer);
}

/// @brief change a specific time component (hours or minutes)
/// @param dt - status of the current time setting
/// @param component - which time element should be changed
/// @return false - if the user wants to continue setting, otherwise true
bool set_time_component(struct dt* dt, enum time_component component) {
  unsigned long last_time = 0;
  enum IR_pressed ir_pressed  = IR_NOT_PRESSED;
  while (digitalRead(BTN1_PIN) && ir_pressed != IR_BUTTON_ENTER) {
    ir_pressed = get_pressed_button();
    if ((!digitalRead(BTN2_PIN) || ir_pressed == IR_BUTTON_NEXT) && (millis() - last_time) > 200) {
      last_time = millis();
      switch (component) {
        case HOURS: dt->hours = (dt->hours +1 ) % 24; break;
        case MINUTES: dt->minutes = (dt->minutes + 1) % 60; break;
      }
      print_time_string(*dt);
    }
    if ((!digitalRead(BTN3_PIN) || ir_pressed == IR_BUTTON_PREVIOUS) && (millis() - last_time) > 200) {
      last_time = millis();
      switch (component) {
        case HOURS: dt->hours = (dt->hours - 1) < 0 ? dt->hours + 23 : dt->hours - 1; break;
        case MINUTES: dt->minutes = (dt->minutes - 1) < 0 ? dt->minutes + 59 : dt->minutes - 1; break;
      }
      print_time_string(*dt);
    }
    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_BUTTON_EXIT) return true;
  }
  return 0;
}

/// @brief Configures the current date by allowing the user to set the year, month, and day
enum state configure_date() {
  struct dt dt = now();
  print_date_string(dt);
  delay(200);
  if (set_date_component(&dt, YEAR)) return CLOCK;
  delay(200);
  if (set_date_component(&dt, MONTH)) return CLOCK;
  delay(200);
  if (set_date_component(&dt, DAY)) return CLOCK;
  set_date(dt.day, dt.month, dt.year);

  return CLOCK;
}

/// @brief Configures the current time by allowing the user to set the hours and minutes
enum state configure_time() {
  struct dt dt = now();
  print_time_string(dt);
  delay(200);
  if (set_time_component(&dt, HOURS)) return CLOCK;
  delay(200);
  if (set_time_component(&dt, MINUTES)) return CLOCK;
  set_time(dt.hours, dt.minutes, dt.seconds);

  return CLOCK;
}
/// @brief Configures the alarm by allowing the user to set the date and time for the alarm.
/// @return CLOCK - Returns the clock state after configuring the alarm.
enum state configure_alarm() {
  struct dt alarm_time; 
  EEPROM.get(ALARM_ADRESS, alarm_time);
  alarm_time = now();
  print_date_string(alarm_time);
  delay(200);
  if (set_date_component(&alarm_time, YEAR)) return CLOCK;
  delay(200);
  if (set_date_component(&alarm_time, MONTH)) return CLOCK;
  delay(200);
  if (set_date_component(&alarm_time, DAY)) return CLOCK;

  print_time_string(alarm_time);
  delay(200);
  if (set_time_component(&alarm_time, HOURS)) return CLOCK;
  delay(200);
  if (set_time_component(&alarm_time, MINUTES)) return CLOCK;

  EEPROM.put(ALARM_ADRESS, alarm_time);
  EEPROM.put(IS_ALARM_ADRESS, true);
  return CLOCK;
}

/// @brief Deletes the alarm if one is set, asking for user confirmation.
/// @return CLOCK - Returns the clock state after attempting to delete the alarm.
enum state delete_alarm() {
  lcd_clear();
  bool is_alarm; EEPROM.get(IS_ALARM_ADRESS, is_alarm);
  if (is_alarm == false) {
    lcd_print_at(0, 1, "You don't have");
    lcd_print_at(1, 1, "any alarms set");
    delay(2000);
    return CLOCK;
  }

  enum IR_pressed ir_pressed  = IR_NOT_PRESSED;

  lcd_print_at(0, 0, "Are you sure?");
  lcd_print_at(1, 0, " NO         yes ");
  bool yes = false;
  delay(200);
  while (digitalRead(BTN1_PIN) && ir_pressed != IR_BUTTON_ENTER) {
    ir_pressed = get_pressed_button();
    if(!digitalRead(BTN2_PIN) || ir_pressed == IR_BUTTON_NEXT) {
      yes = true;
      lcd_print_at(1, 0, " no         YES ");
    }

    if (!digitalRead(BTN3_PIN) || ir_pressed == IR_BUTTON_PREVIOUS) {
      yes = false;
      lcd_print_at(1, 0, " NO         yes ");
    }

    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_BUTTON_EXIT) return CLOCK;
  }
  if (yes) EEPROM.put(IS_ALARM_ADRESS, false);
  return CLOCK;
}

/// @brief Displays the current and adjacent options on the LCD screen with an arrow indicating the current selection.
/// @param current_option - The index of the current option to be displayed.
/// @param options - An array of option strings to be displayed.
void print_options(byte current_option, char** options) {
  lcd_clear();
  bool arrow_pos = (current_option == 0) ? 0 : 1;
  lcd_print_at(arrow_pos, 0, options[current_option]); lcd_print(" <");
  if (arrow_pos == 0) lcd_print_at(1, 0, options[current_option + 1]);
  else lcd_print_at(0, 0, options[current_option - 1]);
}

/// @brief Allows the user to select and set a new alarm melody from a list of available melodies.
/// @return The next state to transition to after setting the melody, which is typically CLOCK.
enum state set_melody() {
  char* all_melodies[NUMBER_OF_MELODIES] = {"Default Melody", "STAR WARS", "Calm Melody"};
  unsigned long last_time = 0;
  enum IR_pressed ir_pressed  = IR_NOT_PRESSED;
  byte new_melody; EEPROM.get(MELODY_ADRESS, new_melody);
  print_options(new_melody, all_melodies);
  delay(200);

  while (digitalRead(BTN1_PIN) && ir_pressed != IR_BUTTON_ENTER) {
    ir_pressed = get_pressed_button();
    if ((!digitalRead(BTN2_PIN) || ir_pressed == IR_BUTTON_NEXT) && new_melody < NUMBER_OF_MELODIES - 1 && (millis() - last_time) > 200) { 
      last_time = millis(); 
      print_options(++new_melody, all_melodies); 
    }
    if ((!digitalRead(BTN3_PIN) || ir_pressed == IR_BUTTON_PREVIOUS) && new_melody > 0 && (millis() - last_time) > 200) { 
      last_time = millis(); 
      print_options(--new_melody, all_melodies); 
    }
    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_BUTTON_EXIT) return CLOCK;
  }
  EEPROM.put(MELODY_ADRESS, new_melody);
  return CLOCK;
}

/// @brief Displays the settings menu and allows the user to select and execute a specific setting function.
/// @return The next state to transition to after executing the selected setting function, typically CLOCK.
enum state state_settings() {
  char* options[NUMBER_OF_OPTIONS] = {"Set Date", "Set Time", "Alarm", "Set Melody", "Delete Alarm"};
  unsigned long last_time = 0;
  byte current_option = SET_DATE;
  enum IR_pressed ir_pressed  = IR_NOT_PRESSED;
  print_options(current_option, options);
  while (digitalRead(BTN1_PIN) && ir_pressed != IR_BUTTON_ENTER) {
    ir_pressed = get_pressed_button();
    if ((!digitalRead(BTN2_PIN) || ir_pressed == IR_BUTTON_NEXT) && current_option < NUMBER_OF_OPTIONS - 1 && (millis() - last_time) > 200) { 
      last_time = millis(); 
      print_options(++current_option, options); 
    }
    if ((!digitalRead(BTN3_PIN) || ir_pressed == IR_BUTTON_PREVIOUS) && current_option > 0 && (millis() - last_time) > 200) { 
      last_time = millis(); 
      print_options(--current_option, options); 
    }

    if (!digitalRead(BTN4_PIN) || ir_pressed == IR_BUTTON_EXIT) return CLOCK;
  }
  switch (current_option) {
    case SET_DATE: return configure_date();
    case SET_TIME: return configure_time();
    case SET_ALARM: return configure_alarm();
    case SET_MELODY: return set_melody();
    case DELETE_ALARM: return delete_alarm();
  }
  return CLOCK;
}