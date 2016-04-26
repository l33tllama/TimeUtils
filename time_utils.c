#include "time_utils.h"
#include <stdio.h>

unsigned long seconds_per_month_no_leap[12] = {
	MON31,	MON28,	MON31,	MON30,	MON31,	MON30,
	MON31,	MON31,	MON30,	MON31,	MON30,	MON31
};

unsigned long seconds_per_month_leap[12] = {
	MON31,	MON29,	MON31,	MON30,	MON31,	MON30,
	MON31,	MON31,	MON30,	MON31,	MON30,	MON31
};

const uint8_t daysInMonth []  = { 31,28,31,30,31,30,31,31,30,31,30,31 };

/* uint64_t make_timestamp(TIME_t * t)
 *
 * Takes a TIME_t data struct (date and time) and converts it into
 * seconds since Jan 1 1970.
 *
 */

uint64_t make_timestamp(TIME_t * t){

	uint8_t i;
	// final return value
	uint64_t time_since_epoch = 0;

	// convert year to years since Jan 1 1970
	uint16_t year = t->year - 1970;
	if(IS_LEAP_YEAR(t->year))
		printf("It's a leap year..\n");

	// Add seconds for this year since Jan 1 1970
	uint16_t iy;
	for(iy = 1970; iy < t->year; ++iy){
		time_since_epoch += YEAR_S + (IS_LEAP_YEAR(iy)? DAY_S : 0);
	}

	// Accumulatively add seconds per month since beginning of the year
	for(i = 1; i < t->mon; i++){
		time_since_epoch += daysInMonth[i-1] * DAY_S;
		if(IS_LEAP_YEAR(t->year) && i == 2)
			time_since_epoch += DAY_S;
	}

	// add seconds for each day per month
	time_since_epoch += (1 + t->dom) * DAY_S;

	// add seconds per hour in the day
	time_since_epoch += t->hour * HOUR_S;

	// add seconds per minute in the hour
	time_since_epoch += t->min * MIN_S;

	// add final seconds per minute
	time_since_epoch += t->sec;

	return time_since_epoch;
}

TIME_t timestamp_to_struct(uint64_t timestamp){
	TIME_t t;

	uint16_t year = 0;
	uint8_t month = 0;
	uint8_t day_of_month = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t seconds = 0;

	uint64_t seconds_count = 0;
	uint64_t last_seconds_count = 0;

	seconds = timestamp % 60;
	timestamp /= 60;
	minute = timestamp % 60;
	timestamp /= 60;
	hour = timestamp % 24;
	uint16_t days = timestamp / 24;
	uint16_t leap;
	uint8_t yOff, m, d;

	for (yOff = 0; ; ++yOff) {
		leap = yOff % 4 == 0;
		if (days < 365 + leap)
			break;
		days -= 365 + leap;
	}
	for (m = 1; ; ++m) {
		uint8_t daysPerMonth = daysInMonth[m - 1];
		if (leap && m == 2)
			++daysPerMonth;
		if (days < daysPerMonth)
			break;
		days -= daysPerMonth;
	}
	d = days + 1;

	/*

	// Get seconds since beginning of the year (and find the current year)
	while(1){
		seconds_count += (year * YEAR_S) + IS_LEAP_YEAR(year)? DAY_S : 0;
		if (seconds_count > timestamp){
			break;
		}
		last_seconds_count = seconds_count;
		year++;
	}

	// Get seconds since the beginning of the month (and find current month)
	unsigned long mon_seconds[12];
	if(IS_LEAP_YEAR(year))
		memcpy(mon_seconds, seconds_per_month_leap, sizeof(unsigned long) * 12);
	else
		memcpy(mon_seconds, seconds_per_month_no_leap, sizeof(unsigned long) * 12);

	seconds_count = last_seconds_count;
	last_seconds_count = 0;

	while(1){
		seconds_count += mon_seconds[month];
		if(seconds_count > timestamp){
			break;
		}
		month++;
		last_seconds_count = seconds_count;
	}

	// Get seconds since the start of the day (and find day of month)
	seconds_count = last_seconds_count;
	last_seconds_count = 0;

	while(1){
		seconds_count += (day_of_month * DAY_S);
		if(seconds_count > timestamp){
			break;
		}
		day_of_month++;
		last_seconds_count = seconds_count;
	}

	// Get seconds since the start of the current hour (and find current hour)
	seconds_count = last_seconds_count;
	last_seconds_count = 0;

	while(1){
		seconds_count += (hour * HOUR_S);
		if(seconds_count > timestamp){
			break;
		}
		hour++;
		last_seconds_count = seconds_count;
	}

	seconds_count = last_seconds_count;
	last_seconds_count = 0;

	// Get seconds since the start of the current minute (and find the current minute)
	while(1){
		seconds_count += (minute * MIN_S);
		if(seconds_count > timestamp){
			break;
		}
		minute++;
		last_seconds_count = seconds_count;
	} */

	t.year = yOff;
	t.mon = m;
	t.dom = d;
	t.hour = hour;
	t.min = minute;
	t.sec = seconds;


	return t;
}
void make_time(TIME_t * t, uint16_t year, uint8_t month, uint8_t day_of_month, uint8_t hour, uint8_t minute, uint8_t second){
	t->year = year;
	t->mon = month;
	t->dom = day_of_month;
	t->hour = hour;
	t->min = minute;
	t->sec = second;
}

void make_dtime(TIME_dt * dt, uint16_t years, uint8_t months, uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs){
	dt->years = years;
	dt->months = months;
	dt->days = days;
	dt->hours = hours;
	dt->mins = mins;
	dt->seconds = secs;
}

void add_time(TIME_t * base, TIME_dt * a){
	uint64_t t_stamp = make_timestamp(base);
	printf("Current timestamp: %u\n", t_stamp);
	uint64_t delta_s = 0;

	if (a->years > 0){
		printf("Years addition not implemented yet!\n");
	}
	if(a->months > 0){
		printf("Months addition not implemented yet!\n");
	}
	delta_s += a->days * DAY_S;
	delta_s += a->hours * HOUR_S;
	delta_s += a->mins * MIN_S;
	delta_s += a->seconds;
	printf("New timestamp    : %u\n", t_stamp + delta_s);

	(*base) = timestamp_to_struct(t_stamp + delta_s);
}
