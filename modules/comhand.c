#include "helpers.h"
#include <string.h>
#include "mpx_supt.h"
#include "commands.h"

#define INPUT_BUFFER_SIZE 32
#define RESPONSE_BUFFER_SIZE 2

void comhand(void) {
    welcome();

    while (1) {
        // Command syntax: command arg_1 arg_2 arg_n
        print(">>> ");

        char input_buffer[INPUT_BUFFER_SIZE] = {0};
        int input_buffer_size = INPUT_BUFFER_SIZE;
        sys_req(READ, DEFAULT_DEVICE, input_buffer, &input_buffer_size);

        print("\n");

        char *delim_cmd = " ";
        char *cmd = strtok(input_buffer, delim_cmd);

        // **************************************************

        if (strcmp(cmd, "version") == 0) {
            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"version\"\n"
                      "Usage: version\n");

                continue;
            }

            version();
        }

        // **************************************************

        else if (strcmp(cmd, "help") == 0) {
            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"help\"\n"
                      "Usage: help\n");

                continue;
            }

            help();
        }

        // **************************************************

        else if (strcmp(cmd, "shutdown") == 0) {
            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"shutdown\"\n"
                      "Usage: shutdown\n");

                continue;
            }

            print("Are you sure you want to shutdown [Y/n]? ");

            char response_buffer[RESPONSE_BUFFER_SIZE] = {0};
            int response_buffer_size = RESPONSE_BUFFER_SIZE;
            sys_req(READ, DEFAULT_DEVICE, response_buffer, &response_buffer_size);

            print("\n");

            if (strcmp(response_buffer, "Y") == 0) {
                break;
            }
        }

        // **************************************************

        else if (strcmp(cmd, "getdate") == 0) {
            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"getdate\"\n"
                      "Usage: getdate\n");

                continue;
            }

            getdate();
        }

        // **************************************************

        // Date syntax: mm/dd/yyyy
        else if (strcmp(cmd, "setdate") == 0) {
            char *date = strtok(NULL, delim_cmd);

            if (date == NULL) {
                print("Too few arguments for command \"setdate\"\n"
                      "Usage: setdate mm/dd/yyyy\n");

                continue;
            }

            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"setdate\"\n"
                      "Usage: setdate mm/dd/yyyy\n");

                continue;
            }

            char *delim_date = "/";
            char *mm_s = strtok(date, delim_date);
            char *dd_s = strtok(NULL, delim_date);

            if (dd_s == NULL) {
                print("Syntax error on parameter mm/dd/yyyy for command \"setdate\"\n"
                      "Usage: setdate mm/dd/yyyy\n");

                continue;
            }

            char *yy_s = strtok(NULL, delim_date);

            if (yy_s == NULL) {
                print("Syntax error on parameter mm/dd/yyyy for command \"setdate\"\n"
                      "Usage: setdate mm/dd/yyyy\n");

                continue;
            }

            if (strtok(NULL, delim_date) != NULL) {
                print("Syntax error on parameter mm/dd/yyyy for command \"setdate\"\n"
                      "Usage: setdate mm/dd/yyyy\n");

                continue;
            }

            // TODO: Check if mm, dd, and yy can be converted from atoi.

            int mm = atoi(mm_s);
            int dd = atoi(dd_s);
            int yy = atoi(yy_s);

            setdate(mm, dd, yy);
        }

        // **************************************************

        else if (strcmp(cmd, "gettime") == 0) {
            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command name \"gettime\"\n"
                      "Usage: gettime\n");

                continue;
            }

            gettime();
        }

        // **************************************************

        // Time syntax: hh:mm:ss
        else if (strcmp(cmd, "settime") == 0) {
            char *time = strtok(NULL, delim_cmd);

            if (time == NULL) {
                print("Too few arguments for command \"settime\"\n"
                      "Usage: settime hh:mm:ss\n");

                continue;
            }

            if (strtok(NULL, delim_cmd) != NULL) {
                print("Too many arguments for command \"settime\"\n"
                      "Usage: settime hh:mm:ss\n");

                continue;
            }

            char *delim_time = ":";
            char *hh_s = strtok(time, delim_time);
            char *mm_s = strtok(NULL, delim_time);

            if (mm_s == NULL) {
                print("Syntax error on parameter hh:mm:ss for command \"settime\"\n"
                      "Usage: settime hh:mm:ss\n");

                continue;
            }

            char *ss_s = strtok(NULL, delim_time);

            if (ss_s == NULL) {
                print("Syntax error on parameter hh:mm:ss for command \"settime\"\n"
                      "Usage: settime hh:mm:ss\n");

                continue;
            }

            if (strtok(NULL, delim_time) != NULL) {
                print("Syntax error on parameter hh:mm:ss for command \"settime\"\n"
                      "Usage: settime hh:mm:ss\n");

                continue;
            }

            // TODO: Check if hh, mm, and ss can be converted from atoi.

            int hh = atoi(hh_s);
            int mm = atoi(mm_s);
            int ss = atoi(ss_s);

            settime(hh, mm, ss);
        }

        // **************************************************

        else {
            print("Unrecognized command\n");
            help();
        }

        // **************************************************
    }
}
