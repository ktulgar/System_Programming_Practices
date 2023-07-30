#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>



int hour;
int minute;
int day;
int month;
int year;

struct tm* today_alarm;
struct tm future_alarm;

time_t t;

int minute_interval;
int choice ;

const char *alarm_handler_message = "\n"
                                    "Wakeup... Alarm...!!!\n"
                                    "1. Snooze\n"
                                    "2. Freeze\n"
                                    "What would you like to do: ";


const char colon = ':';
const char slash = '/';

void alarm_handler() {

    printf("%s",alarm_handler_message);
    scanf("%d",&choice);
    if(choice == 1) {
        printf("Snooze Interval (Minutes): ");
        scanf("%d",&minute_interval);
        alarm(minute_interval*60);
    }
    else if(choice == 2) {
        exit(0);
    }
    else {
        printf("You did not enter the valid option.\nSnooze Interval (Minutes): 1 as Default\n");
        alarm(60);
    }


}

int main(int argc,char *argv[]){

    if(argc == 1 ||  argc > 3) {
        printf("Usage: ./main <hh:mm> [dd/mm/yy]\n");
    }

    else{

        char *token = strtok(argv[1],&colon);
        int numbers = 0;
        while(token != NULL ) {
            if(numbers == 0) {
                hour = atoi(token);
                if(hour > 23 || hour < 0) {
                    printf("Invalid Time\n");
                    exit(0);
                }
                numbers++;
            }
            else if(numbers == 1) {
                minute = atoi(token);
                if(minute > 59 || minute < 0) {
                    printf("Invalid Time\n");
                    exit(0);
                }
                numbers++;
            }
            else{
                printf("Usage: ./main <hh:mm> [dd/mm/yy]\n");
                exit(0);
            }

            token = strtok(NULL,&colon);
        }


        t = time(NULL);

        if(argc == 2) {
            printf("Alarm set for today %02d:%02d\n",hour,minute);

            today_alarm = localtime(&t);
            today_alarm->tm_hour = hour;
            today_alarm->tm_min = minute;
            today_alarm->tm_sec = 0;
            time_t alarm_time = mktime(today_alarm);
            int alarm_seconds = alarm_time - t;
            signal(SIGALRM,alarm_handler);
            alarm(alarm_seconds);
            while (1);
        }

        else {
            token = strtok(argv[2],&slash);
            numbers = 0;
            while(token != NULL ) {
                if(numbers == 0) {
                    day = atoi(token);
                    if(day < 1 || day  > 31) {
                        printf("Invalid Time\n");
                        exit(0);
                    }
                    numbers++;
                }
                else if(numbers == 1) {
                    month = atoi(token);
                    if(month > 12 || minute < 0) {
                        printf("Invalid Time\n");
                        exit(0);
                    }
                    numbers++;
                }

                else if(numbers == 2) {
                    year = atoi(token);
                    if(year < 23) {
                        printf("Invalid Time\n");
                        exit(0);
                    }
                    numbers++;
                }

                else{
                    printf("Usage: ./main <hh:mm> [dd/mm/yy]\n");
                    exit(0);
                }

                token = strtok(NULL,&slash);
            }


            printf("Alarm set for %02d:%02d %02d/%02d/%02d\n",hour,minute,day,month,year);

            future_alarm.tm_year = 100 + year;
            future_alarm.tm_mon = month - 1;
            future_alarm.tm_mday = day;
            future_alarm.tm_hour = hour;
            future_alarm.tm_min = minute;
            future_alarm.tm_sec = 0;
            future_alarm.tm_isdst = -1;

            time_t alarm_time = mktime(&future_alarm);
            int alarm_seconds = alarm_time - t;
            signal(SIGALRM,alarm_handler);
            alarm(alarm_seconds);
            while (1);

        }

    }

}








