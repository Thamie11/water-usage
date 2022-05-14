/* Filename: fileHandling.c
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

#include <stdio.h>
#include <stdlib.h>
#include "fileHandling.h"
#include "apartments.h"
#include "stringHandling.h"
#include "definingStuff.h"
#include "calculations.h"
#include "time.h"

/* ********************************************************************
* Function: readMetadataFromFile
* Purpose: Extract information, Apartment data on the text file
* Inputs: Pointer variable that points to the structure Apartment data
* Outputs: None
* Operation: Read from the apartments_metadata.txt file
*
**********************************************************************/

void readMetadataFromFile(ApartmentData *data1, ApartmentData *data2, ApartmentData *data3)
{

	FILE *PtrToFile; // pointer to file

	PtrToFile = fopen("apartments_metadata.txt", "r"); // open the file for reading

	// scan through the first line, store first string before space to 'OwnerName',
	// second string until reach space to OwnerSurname and so on
	fscanf(PtrToFile, "%s%s%lf", (*data1).ownerName, (*data1).ownerSurname, &(*data1).tariff);

	fscanf(PtrToFile, "%s%s%lf", (*data2).ownerName, (*data2).ownerSurname, &(*data2).tariff);

	fscanf(PtrToFile, "%s%s%lf", (*data3).ownerName, (*data3).ownerSurname, &(*data3).tariff);

	fclose(PtrToFile); // close file

	return;
}

/* ********************************************************************
* Function: readUsageFromFile
* Purpose: Extract information, water usage pattern on the csv file
* Inputs: Water usage pattern for 30 days, hourly basis (Array) for 3
* apartments
* Outputs: None
* Operation: Read from the water_usage.csv file
*
**********************************************************************/

void readUsageFromFile(double usage1[], double usage2[], double usage3[])
{
	 FILE *PtrToFile; // pointer to file

	 PtrToFile = fopen("water_usage.csv", "r"); // open the file for reading

	 int i; // counter variable

	 // constituent parts of the water usage pattern is allocated space in memory
	 // and their address is pointed with relevant pointer variable
	 char *day = malloc(sizeof(char) * 2);
	 char *time = malloc(sizeof(char) * 6);
	 char *use1 = malloc(sizeof(char) * 6);
	 char *use2 = malloc(sizeof(char) * 6);
	 char *use3 = malloc(sizeof(char) * 6);

	 char StoreHeader[60]; // Just a dummy array to store the first line of the csv file
	 char String[50]; // Array to store each line after the first one as a string of characters

	 fscanf(PtrToFile, "%s", StoreHeader); // Read the first line of the file and store it

	 for(i = 0; i < SIZE; i++) // loop to read each line of the csv file until 30 days
	 {
	   	fscanf(PtrToFile, "%s", String); // Store the block as string of characters

	   	csvToStrings(String, day, time, use1, use2, use3); // pass to separate the 'string' to its constituent parts

	   	// Convert the string to a double and assign to each element 'i' of the array
	   	usage1[i] = strtod(use1, NULL);
		usage2[i] = strtod(use2, NULL);
		usage3[i] = strtod(use3, NULL);

	 }

	 // free the memory allocated to 'water usage pattern' constituent parts
	 free(day);
	 free(time);
	 free(use1);
	 free(use2);
	 free(use3);

	 fclose(PtrToFile); // close file

	 return;
}

/* ********************************************************************
* Function: writeBuildingReport
* Purpose: Write the apartment report on the text file
* Inputs: Water usage pattern for 30 days, hourly basis (Array)
* and apartment data
* Outputs: None
* Operation: Write on a new text file
*
**********************************************************************/

void writeBuildingReport(double apartment1Usage[], double apartment2Usage[], double apartment3Usage[], ApartmentData apartment1Data, ApartmentData apartment2Data, ApartmentData apartment3Data, char *filename)
{
	FILE *PointTofile; // pointer to a file

	PointTofile = fopen("awesome_report.txt", "w"); // open a new text file to write on

	double TotalWaterUsed;
	double TotalBill;
	double CompareUsage; // find apartment that used most water

	// Add total water used for all three apartments
	TotalWaterUsed = getTotalWaterUsage(apartment1Usage) + getTotalWaterUsage(apartment2Usage) + getTotalWaterUsage(apartment3Usage);
	// Add total bill of all three apartments
	TotalBill = getTotalBill(apartment1Usage, apartment1Data.tariff) + getTotalBill(apartment2Usage, apartment2Data.tariff) + getTotalBill(apartment3Usage, apartment3Data.tariff);

	// Compare which apartment used most water
	CompareUsage = getTotalWaterUsage(apartment1Usage);

	if (CompareUsage < getTotalWaterUsage(apartment2Usage))
	{
		CompareUsage = getTotalWaterUsage(apartment2Usage);
	}

	else if (CompareUsage < getTotalWaterUsage(apartment3Usage))
	{
		CompareUsage = getTotalWaterUsage(apartment3Usage);
	}

	// Write the building report on the opened textfile
	fprintf(PointTofile, "Total usage: %.3lf kl\n", TotalWaterUsed);
	fprintf(PointTofile, "Total bill: R%.2lf\n", TotalBill);

	// Write the user who used most water on the opened file
	if (CompareUsage == getTotalWaterUsage(apartment1Usage))
	{
		fprintf(PointTofile, "Most usage: %s %s (%.3lf kl)\n", apartment1Data.ownerName, apartment1Data.ownerSurname , CompareUsage);
	}

	else if(CompareUsage == getTotalWaterUsage(apartment2Usage))
	{
		fprintf(PointTofile, "Most usage: %s %s (%.3lf kl)\n", apartment2Data.ownerName, apartment2Data.ownerSurname , CompareUsage);
	}

	else if(CompareUsage == getTotalWaterUsage(apartment3Usage))
	{
		fprintf(PointTofile, "Most usage: %s %s (%.3lf kl)\n", apartment3Data.ownerName, apartment3Data.ownerSurname , CompareUsage);
	}

	fclose(PointTofile); // close file

	return;
}

/* ********************************************************************
* Function: saveCompactUsage
* Purpose: Save compact usage on a binary format to save space
* Inputs: Water usage pattern for 30 days, hourly basis (Array)
* and apartment number
* Outputs: None
* Operation: Write water usage pattern (non-zeros) on a new binary file
*
**********************************************************************/

void saveCompactUsage(double usage[], int apartment)
{
	 int i; // counter
	 char FileName[25]; // array to store filename
	 double WriteorNot = 0.001; // minimum water used, our reference point
	
	 FILE *PtrFile; // file pointer

	 // Store the name of the binary file into array 'FileName' as string
	 sprintf(FileName, "compact_usage_%d.bin", apartment);

	 PtrFile = fopen(FileName, "wb"); // open a file for writing in binary mode

   	 // Write information to the binary file
	 for(i = 0; i < SIZE; i++)
   	 {
   		 // only write the non-zero entries (hourly usage)
		 if (usage[i] >= WriteorNot)
   		 {
			fwrite(&i, sizeof(int),1 , PtrFile); // write the hour over a month period
   			fwrite(&usage[i], sizeof(double),1 , PtrFile); // write the the hourly usage
   		 }
     }

	 fclose(PtrFile); //close file after writing information

     return; // no return value
}
