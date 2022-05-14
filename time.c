/*Filename: time.c
* Date: 2017/10/11
* Name: Gcwensa T.L
* Student number: 18407420
* ------------------------------------------------------
* By submitting this file electronically, I declare that
* it is my own original work, and that I have not copied
* any part of it from another source.
* ------------------------------------------------------
* This file contains function definitions for displaying
* menu three and four: Monthly water usage for a specified
* apartment and monthly bill.
* ------------------------------------------------------
*/

#include "definingStuff.h"
#include "time.h"

/* ********************************************************************
* Function: monthHourToDay
* Purpose: takes the hour of the month, and converts that to the day
* Inputs: Hour over a month period
* Outputs: Day of the month
* Operation: Divide the hours in a month by 24 hours in a one day,
* and then add one
*
**********************************************************************/

int monthHourToDay(int monthHour)
{
	int Day;

	Day =  1 + (monthHour)/HOURS;

	return (Day);

}

/* ********************************************************************
* Function: monthHourToDailyHour
* Purpose: takes the hour of the month, and converts that to the
* specific hour on that day of the month
* Inputs: Hour over a month period
* Outputs: Daily Hour (<24)
* Operation: Subtract the hours (a multiple of 24) from the hours over
* a month and the remainder will give you the hours of that day (<24)
*
**********************************************************************/

int monthHourToDailyHour(int monthHour)
{
	int DailyHour;

	DailyHour = monthHour - (monthHourToDay(monthHour)-1) * HOURS;

	return (DailyHour);
}



