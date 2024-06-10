#include <RtcDS1302.h>
#include "rtc_wrapper.h"
#include "config.h"

ThreeWire myWire(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN); // IO, SCLK, CE
RtcDS1302<ThreeWire> rtc(myWire);

void clock_init() {
  rtc.Begin();
}

void set_date(const byte day, const byte month, const int year) {
  RtcDateTime currentTime = rtc.GetDateTime();
  RtcDateTime newTime(year, month, day, currentTime.Hour(), currentTime.Minute(), currentTime.Second());
  rtc.SetDateTime(newTime);
}

void set_time(const byte hours, const byte minutes, const byte seconds) {
  RtcDateTime currentTime = rtc.GetDateTime();
  RtcDateTime newTime(currentTime.Year(), currentTime.Month(), currentTime.Day(), hours, minutes, seconds);
  rtc.SetDateTime(newTime);
}

void set_datetime(const byte day, const byte month, const int year, const byte hours, const byte minutes, const byte seconds) {
  RtcDateTime newTime(year, month, day, hours, minutes, seconds);
  rtc.SetDateTime(newTime);
}

byte get_day() {
  return rtc.GetDateTime().Day();
}

byte get_month() {
  return rtc.GetDateTime().Month();
}

int get_year() {
  return rtc.GetDateTime().Year();
}

byte get_hours() {
  return rtc.GetDateTime().Hour();
}

byte get_minutes() {
  return rtc.GetDateTime().Minute();
}

byte get_seconds() {
  return rtc.GetDateTime().Second();
}

struct dt now() {
  RtcDateTime currentTime = rtc.GetDateTime();
  struct dt time_now = {
    .day = currentTime.Day(),
    .month = currentTime.Month(),
    .year = currentTime.Year(),
    .hours = currentTime.Hour(),
    .minutes = currentTime.Minute(),
    .seconds = currentTime.Second()
  };
  return time_now;
}
