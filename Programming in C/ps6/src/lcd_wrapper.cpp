#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
  lcd.createChar(0, bell);
}

void lcd_clear() {
  lcd.clear();
}

void lcd_set_cursor(int y, int x) {
  lcd.setCursor(x, y);
}

void lcd_print(char* text) {
  if (text >=0 && (int)text < 8) lcd.write(text);
  lcd.print(text);
}

void lcd_print_at(int y, int x, char* text) {
  lcd_set_cursor(y, x);
  lcd_print(text);
}

void lcd_backlight(bool state) {
  (state) ? lcd.backlight() : lcd.noBacklight();
}