#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <stdint.h>
#include <stdbool.h>

#define JANUARY 0
#define FEBRUARY 1
#define MARCH 2
#define APRIL 3
#define MAY 4
#define JUNE 5
#define JULY 6
#define AUGUST 7
#define SEPTEMBER 8
#define OCTOBER 9
#define NOVEMBER 10
#define DECEMBER 11

#define YEAR_S 31536000
#define MON31 2678400
#define MON30 2592000
#define MON29 2505600
#define MON28 2419200
#define IS_LEAP_YEAR(year) (year % 4 == 0)
#define DAY_S 86400
#define HOUR_S 3600
#define MIN_S 60

// TODO: make offset for timestamp - eg instead of starting at 1970, start at 2015

typedef enum DayOfWeek{
	sunday,
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday
} day_of_week;

typedef union DayOfWeekUnion{
	uint8_t d;
	day_of_week de;
} day_of_week_u;

typedef struct TIME{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	day_of_week_u dow;
	uint16_t dom;
	uint8_t mon;
	uint16_t year;
} TIME_t;

typedef struct TIME_DELTA{
	uint8_t seconds;
	uint8_t mins;
	uint8_t hours;
	uint16_t days;
	uint8_t months;
	uint16_t years;
} TIME_dt;

uint64_t make_timestamp(TIME_t * t);
TIME_t timestamp_to_struct(uint64_t timestamp);
void make_time(TIME_t * t, uint16_t year, uint8_t month, uint8_t day_of_month, uint8_t hour, uint8_t min, uint8_t sec);
void make_dtime(TIME_dt * dt, uint16_t years, uint8_t months, uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs);
void add_time(TIME_t * base, TIME_dt * a);

#endif
