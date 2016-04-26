#include <stdio.h>
#include "time_utils.h"

int main(){

	printf("Hello world.\n");

	TIME_t t;
	TIME_dt d;
	make_time(&t, 2016, 4, 24, 16, 50, 30);
	printf("Current time: %d/%d/%d %d:%d:%d\n", t.year, t.mon, t.dom, t.hour, t.min, t.sec);

	make_dtime(&d,0,0,0,10,9,2);
	printf("Delta time  : %d/%d/%d %d:%d:%d\n", d.years, d.months, d.days, d.hours, d.mins, d.seconds);

	add_time(&t, &d);

	printf("New time    : %d/%d/%d %d:%d:%d\n", t.year, t.mon, t.dom, t.hour, t.min, t.sec);

	return 0;
}
