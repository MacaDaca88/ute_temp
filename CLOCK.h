void clock() {

  timeClient.update();


  int hours = timeClient.getHours();
  if (hours >= 24) {
    hours -= 24;
  }

  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  String period = "AM";
  if (hours >= 12) {
    period = "PM";
    if (hours > 12) hours -= 12;
  } else if (hours == 0) {
    hours = 12;
  }

  char timeBuffer[9];
  sprintf(timeBuffer, "%02d:%02d:%02d", hours, minutes, seconds);

  String dayOfWeek;
  int day = timeClient.getDay();
  switch (day) {
    case 0: dayOfWeek = "Sunday"; break;
    case 1: dayOfWeek = "Monday"; break;
    case 2: dayOfWeek = "Tuesday"; break;
    case 3: dayOfWeek = "Wednesday"; break;
    case 4: dayOfWeek = "Thursday"; break;
    case 5: dayOfWeek = "Friday"; break;
    case 6: dayOfWeek = "Saturday"; break;
  }
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int date = timeInfo->tm_mday;
  int month = timeInfo->tm_mon;  // 0 = Jan, 3 = April, etc.

  String suffix = "th";
  if (date % 10 == 1 && date != 11) suffix = "st";
  else if (date % 10 == 2 && date != 12) suffix = "nd";
  else if (date % 10 == 3 && date != 13) suffix = "rd";

  const char* months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  String fullDate = String(date) + suffix + " " + months[month];

  u8g2.setFont(u8g2_font_osr18_tf);

  u8g2.setCursor(3, 23);
  u8g2.print(timeBuffer);

  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.print(period);
  u8g2.setCursor(5, 40);
  u8g2.setFont(u8g2_font_timR10_tf);
  u8g2.print(dayOfWeek);
  u8g2.setFont(u8g2_font_timR10_tf);
  u8g2.setCursor(65, 40);
  u8g2.print(fullDate);
}