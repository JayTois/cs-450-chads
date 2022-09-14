#include <core/io.h>

#include "helpers.h"
#include "string.h"

#define RTC_IN_PORT 0x70
#define RTC_OUT_PORT 0x71

#define RTC_MONTH_REGISTER 0x08
#define RTC_DAY_REGISTER 0x07
#define RTC_YEAR_REGISTER 0x09

#define RTC_HOURS_REGISTER 0x04
#define RTC_MINUTES_REGISTER 0x02
#define RTC_SECONDS_REGISTER 0x00

void welcome(void) {
    print("⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠈⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿\n"
          "⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿\n"
          "⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿\n"
          "⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿\n"
          "⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿\n"
          "⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿\n"
          "⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼\n"
          "⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼\n"
          "⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿\n"
          "⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿\n"
          "⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿\n"
          "⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿\n"
          "⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⡄⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
          "⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉\n"
          "⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄⠀\n"
          " ________  ___  ___  ________  ________       ________  ________      \n"
          "|\\   ____\\|\\  \\|\\  \\|\\   __  \\|\\   ___ \\     |\\   __  \\|\\   ____\\     \n"
          "\\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\_|\\ \\  __\\ \\  \\|\\  \\ \\  \\___|_    \n"
          " \\ \\  \\    \\ \\   __  \\ \\   __  \\ \\  \\ \\\\ \\|\\__\\ \\  \\\\\\  \\ \\_____  \\   \n"
          "  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\_\\\\ \\|__|\\ \\  \\\\\\  \\|____|\\  \\  \n"
          "   \\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\ \\_______\\    \\ \\_______\\____\\_\\  \\ \n"
          "    \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|     \\|_______|\\_________\\\n"
          "                                                          \\|_________|\n");
}

void version(void) {
    print("R1\n");
}

void help(void) {
    print("The following commands are available:\n"
          "  COMMAND   DESCRIPTION                             USAGE\n"
          "  ————————————————————————————————————————————————————————————————————\n"
          "  version   Display the version of chadOS           version\n"
          "  help      Display the list of available commands  help\n"
          "  shutdown  Shutdown chadOS                         shutdown\n"
          "  getdate   Display the system date                 getdate\n"
          "  setdate   Change the system date                  setdate mm/dd/yy\n"
          "  gettime   Display the system time                 gettime\n"
          "  settime   Change the system time                  settime hh:mm:ss\n");
}

// Binary Coded Decimal (BCD) uses 4 bits to represent each digit.
// e.g., 45 => 0100 (4) 0101 (5)
void getdate(void) {
    outb(RTC_IN_PORT, RTC_MONTH_REGISTER);
    unsigned char month_bcd = inb(RTC_OUT_PORT);

    outb(RTC_IN_PORT, RTC_DAY_REGISTER);
    unsigned char day_bcd = inb(RTC_OUT_PORT);

    outb(RTC_IN_PORT, RTC_YEAR_REGISTER);
    unsigned char year_bcd = inb(RTC_OUT_PORT);

    int month = month_bcd - (6 * (month_bcd >> 4));
    int day = day_bcd - (6 * (day_bcd >> 4));
    int year = year_bcd - (6 * (year_bcd >> 4));

    char month_s[3] = {0};
    char day_s[3] = {0};
    char year_s[3] = {0};

    itoa(month_s, month);
    itoa(day_s, day);
    itoa(year_s, year);

    print(month_s);
    print("/");
    print(day_s);
    print("/");
    print(year_s);
    print("\n");
}

void setdate(int mm, int dd, int yy) {
    if (mm < 1 || mm > 12) {
        print("Invalid month\n"
              "Month must be between 1 (inclusive) and 12 (inclusive)\n");
        return;
    }

    if (dd < 1 || dd > 31) {
        print("Invalid day\n"
              "Day must be between 1 (inclusive) and 31 (inclusive)\n");
        return;
    }

    if (yy < 0 || yy > 99) {
        print("Invalid year\n"
              "Year must be between 0 (inclusive) and 99 (inclusive)\n");
        return;
    }

    unsigned char month_bcd = dectobcd(mm);
    unsigned char day_bcd = dectobcd(dd);
    unsigned char year_bcd = dectobcd(yy);

    outb(RTC_IN_PORT, RTC_MONTH_REGISTER);
    outb(RTC_OUT_PORT, month_bcd);

    outb(RTC_IN_PORT, RTC_DAY_REGISTER);
    outb(RTC_OUT_PORT, day_bcd);

    outb(RTC_IN_PORT, RTC_YEAR_REGISTER);
    outb(RTC_OUT_PORT, year_bcd);
}

void gettime(void) {
    outb(RTC_IN_PORT, RTC_HOURS_REGISTER);
    unsigned char hours_bcd = inb(RTC_OUT_PORT);

    outb(RTC_IN_PORT, RTC_MINUTES_REGISTER);
    unsigned char minutes_bcd = inb(RTC_OUT_PORT);

    outb(RTC_IN_PORT, RTC_SECONDS_REGISTER);
    unsigned char seconds_bcd = inb(RTC_OUT_PORT);

    int hours = hours_bcd - (6 * (hours_bcd >> 4));
    int minutes = minutes_bcd - (6 * (minutes_bcd >> 4));
    int seconds = seconds_bcd - (6 * (seconds_bcd >> 4));

    char hours_s[3] = {0};
    char minutes_s[3] = {0};
    char seconds_s[3] = {0};

    itoa(hours_s, hours);
    itoa(minutes_s, minutes);
    itoa(seconds_s, seconds);

    print(hours_s);
    print(":");
    print(minutes_s);
    print(":");
    print(seconds_s);
    print("\n");
}

void settime(int hh, int mm, int ss) {
    if (hh < 0 || hh >= 24) {
        print("Invalid hours\n"
              "Hours must be between 0 (inclusive) and 24 (exclusive)\n");
        return;
    }

    if (mm < 0 || mm >= 60) {
        print("Invalid minutes\n"
              "Minutes must be between 0 (inclusive) and 60 (exclusive)\n");
        return;
    }

    if (ss < 0 || ss >= 60) {
        print("Invalid seconds\n"
              "Seconds must be between 0 (inclusive) and 60 (exclusive)\n");
        return;
    }

    unsigned char hours_bcd = dectobcd(hh);
    unsigned char minutes_bcd = dectobcd(mm);
    unsigned char seconds_bcd = dectobcd(ss);

    outb(RTC_IN_PORT, RTC_HOURS_REGISTER);
    outb(RTC_OUT_PORT, hours_bcd);

    outb(RTC_IN_PORT, RTC_MINUTES_REGISTER);
    outb(RTC_OUT_PORT, minutes_bcd);

    outb(RTC_IN_PORT, RTC_SECONDS_REGISTER);
    outb(RTC_OUT_PORT, seconds_bcd);
}
