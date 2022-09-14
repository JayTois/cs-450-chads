#ifndef CS_450_CHADS_COMMANDS_H
#define CS_450_CHADS_COMMANDS_H

void welcome(void);

void version(void);

void help(void);

// Shutdown is part of comhand in comhand.c.

void getdate(void);

void setdate(int mm, int dd, int yy);

void gettime(void);

void settime(int hh, int mm, int ss);

#endif //CS_450_CHADS_COMMANDS_H
