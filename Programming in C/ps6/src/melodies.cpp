#include <Arduino.h>

#include "melodies.h"
#include "config.h"

void play_star_wars(int* current_note, unsigned long* last_time) {
  unsigned int star_wars_notes[STAR_WARS_NOTES_NUMBER] = { 392, 392, 392, 311, 466, 392, 311, 466, 392, 587, 587, 587, 622, 466, 369, 311, 466, 392, 784, 392, 392, 784, 739, 698, 659, 622, 659, 415, 554, 523, 493, 466, 440, 466, 311, 369, 311, 466, 392 };
  unsigned int star_wars_durations[STAR_WARS_NOTES_NUMBER] = { 700, 700, 700, 500, 200, 700, 500, 200, 1400, 700, 700, 700, 500, 200, 700, 500, 200, 1400, 700, 500, 200, 700, 500, 200, 200, 200, 900, 300, 700, 500, 200, 200, 200, 900, 300, 700, 500, 200, 1500 };
  tone(BUZZER_PIN, star_wars_notes[*current_note], star_wars_durations[*current_note]);
  if (millis() - *last_time > star_wars_durations[*current_note]){
    *last_time = millis();
    noTone(BUZZER_PIN);
    if (++(*current_note) >= STAR_WARS_NOTES_NUMBER) *current_note = 0;
  }
}

void play_default(int* current_note, unsigned long* last_time) {
  unsigned default_notes[DEFAULT_NOTES_NUMBER] = {440, 880, 440, 880, 0};
  unsigned default_durations[DEFAULT_NOTES_NUMBER] = {200, 200, 200, 200, 1000};

  tone(BUZZER_PIN, default_notes[*current_note], default_durations[*current_note]);
  if (millis() - *last_time > default_durations[*current_note]){
    *last_time = millis();
    noTone(BUZZER_PIN);
    if (++(*current_note) >= DEFAULT_NOTES_NUMBER) *current_note = 0;
  }
}

void play_calm_song(int* current_note, unsigned long* last_time) {
  unsigned calm_notes[CALM_NOTES_NUMBER] = { 700, 700, 780, 700, 625, 590, 520, 460, 350, 350, 460, 520, 590, 625, 590, 520, 700, 700, 780, 700, 625, 590, 520, 460, 350, 350, 625, 590, 520, 700, 590, 520, 460, 0};
  unsigned calm_durations[CALM_NOTES_NUMBER] = { 300, 600, 150, 300, 450, 150, 150, 450, 450, 600, 450, 600, 150, 150, 450, 150, 150, 300, 300, 150, 150, 450, 150, 150, 450, 450, 600, 450, 150, 150, 450, 150, 150, 1350};

  tone(BUZZER_PIN, calm_notes[*current_note], calm_durations[*current_note]);
  if (millis() - *last_time > calm_durations[*current_note]){
    *last_time = millis();
    noTone(BUZZER_PIN);
    if (++(*current_note) >= CALM_NOTES_NUMBER) *current_note = 0;
  }
}

