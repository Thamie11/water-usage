/* Filename: calculations.c
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

#include "calculations.h"
#include "definingStuff.h"
#include "time.h"

/* ********************************************************************
* Function: getTotalWaterUsage
* Purpose: Calculate the total water usage for specified apartment
* Inputs: Water usage pattern for 30 days, hourly basis (Array)
* Outputs: Total usage in kl
* Operation: Count the water used in each hour of the month
*
**********************************************************************/

double getTotalWaterUsage(double waterUsage[])
{
	int i; //counter
	double total_waterUsage = 0;

	// loop to search through each element of the array
	for(i = 0; i < SIZE; i++)
	{
		total_waterUsage += waterUsage[i]; // add element to the previous
	}

	return total_waterUsage; // return sum of all the array elements
}

/* ********************************************************************
* Function: getTotalBill
* Purpose: Calculate the total bill for specified apartment
* Inputs: Water usage pattern (array)and tariff for specified apartment
* Outputs: Total bill in rands
* Operation: Multiply the total water used by the tariff plan
*
**********************************************************************/

double getTotalBill(double waterUsage[], double tariff)
{

	double monthlyBill;
	double total_waterUsage = 0;

	total_waterUsage = getTotalWaterUsage(waterUsage); // get total water used

	monthlyBill = tariff * total_waterUsage;

	return monthlyBill; // return total bill

}

/* ********************************************************************
* Function: checkForLeak
* Purpose: returns the day (1 to 30) on which the leak occurs, or 0 if
* there is no leak
* Inputs: Water usage pattern (array)
* Outputs: Leakage of certain apartment at a particular day
* Operation: Search for water used in the hours 1 - 4 AM
*
**********************************************************************/

int checkForLeak(double waterUsage[])
{
	int counter;
	int LeakDay; // day where there is a leak

	// loop to search all the elements of the water usage pattern
	for(counter = 0; counter < SIZE; counter++)
    {

    	// on the hours of 1 - 4 AM (included) check for leak
		// if there is a leak, return the day.
		if(waterUsage[counter]!=0 && monthHourToDailyHour(counter) > 0 && monthHourToDailyHour(counter) < 5 && waterUsage[counter]==waterUsage[counter+1] && waterUsage[counter+1]==waterUsage[counter+2] && waterUsage[counter]==waterUsage[counter+3])
        {
			LeakDay = monthHourToDay(counter);
			break; // break loop if all conditions have been satisfied
		}

		// hours outside 1 - 4 AM return 0
		else
        {
			LeakDay = 0;
		}
	}

	return(LeakDay);
}
