
/* Filename: main.c
* Date: 2017/10/11
* Name: Gcwensa T.L
* Student number: 18407420
* ------------------------------------------------------
* By submitting this file electronically, I declare that
* it is my own original work, and that I have not copied
* any part of it from another source.
* ------------------------------------------------------
* This file contains the main function for developing a
* water usage application for an apartment building
* consisting of three apartments.
* ------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include "calculations.h"
#include "time.h"
#include "apartments.h"
#include "week1Usages.h"
#include "definingStuff.h"
#include "fileHandling.h"
#include "linkedLists.h"

int GatewayFunc(double apartmentUsage[]); // function prototype to aid in menu 8
void printApartmentReport(double waterUsage[], ApartmentData data);//function prototype for a function displaying menu 4

int main(void)

{
	 //Arrays for water usage patterns for each apartment
	 double apartment1Usage[SIZE];
	 double apartment2Usage[SIZE];
	 double apartment3Usage[SIZE];

	 int apartmentNUM; // Just a dummy input variable for each apartment
	 int i = 0, option; // counter and menu selection variables
	 int leakage;
	 int Print_Save;
	 int PeakHour;
	 char FileName[30]; // array to store text file name
	 double Output_Usage;

	 FILE *PtrFile;

	 // Apartment data:
	 // The apartment data is allocated space in memory
	 ApartmentData *APARTMENTnum1 = malloc(sizeof(ApartmentData));
	 ApartmentData *APARTMENTnum2 = malloc(sizeof(ApartmentData));
	 ApartmentData *APARTMENTnum3 = malloc(sizeof(ApartmentData));

	 readMetadataFromFile(APARTMENTnum1, APARTMENTnum2, APARTMENTnum3);
	 readUsageFromFile(apartment1Usage, apartment2Usage, apartment3Usage);

	 setbuf(stdout, 0); // fix eclipse

	 // Print the menu of options
	 printf("RP143 Water Calculator\n");
	 printf("1. Print usage pattern for apartment\n2. Calculate and print total usage for apartment (in kl)\n");
	 printf("3. Calculate and print total bill for apartment (in R)\n4. Print apartment usage report to screen\n");
     printf("5. Check building for leaks and print leak report\n6. Write building water usage report to text file\n");
	 printf("7. Save or print compact binary usage file for apartment\n8. Determine and print hour with greatest usage for apartment\n");
     printf("10. Exit\n");

     printf("\nChoose an item from the menu: \n"); //user enters which menu to display
     scanf("%d", &option);

     while(option != 10) // Loop to Repeat the menu
     {
    	switch(option)
    	{
    	    // menu 1
    	    case 1:
    		   printf("\nChoose apartment (1, 2 or 3): \n"); //user enters which apartment to display water usage report for
    		   scanf("%d", &apartmentNUM);
    		   printf("\nActive water usage report:\n");

    		   if(apartmentNUM == 1)
    		   {
    			   for(i = 0; i < SIZE; i++) // loop to check for water consumption per month on a hourly basis
    			   {
    				     // only display the water usage when the consumption is not zero
    				    if(apartment1Usage[i] != 0)
    					{
    				    	// display the day, time and amount of water used in a month
    				    	printf("Day %02d %02d:00 : %.3lf kl\n", monthHourToDay(i), monthHourToDailyHour(i), apartment1Usage[i]);
    					}
    			   }
    		   }

    		   else if(apartmentNUM == 2)
    		   {
    			   for(i = 0; i < SIZE; i++) // loop to check for water consumption per month on a hourly basis
    			   {
    				     // only display the water usage when the consumption is not zero
    				    if(apartment2Usage[i] != 0)
    					{
    				    	// display the day, time and amount of water used in a month
    				    	printf("Day %02d %02d:00 : %.3lf kl\n", monthHourToDay(i), monthHourToDailyHour(i), apartment2Usage[i]);
    					}
    			   }
    		   }

    		   else if(apartmentNUM == 3)
    		   {
    			   for(i = 0; i < SIZE; i++) // loop to check for water consumption per month on a hourly basis
    			   {
    				     // only display the water usage when the consumption is not zero
    				    if(apartment3Usage[i] != 0)
    					{
    				    	// display the day, time and amount of water used in a month
    				    	printf("Day %02d %02d:00 : %.3lf kl\n", monthHourToDay(i), monthHourToDailyHour(i), apartment3Usage[i]);
    					}
    			   }
    		   }

    		break;

    	    //menu 2
    		case 2:
    	       printf("\nChoose apartment (1, 2 or 3): \n"); //user enters which apartment to display the total water usage for
    	       scanf("%d", &apartmentNUM);
    	       printf("\nTotal usage for apartment %d: ", apartmentNUM);

    	    //print the monthly water usage for user's choice of apartment
    	       if(apartmentNUM == 1)
    	       {
    	    	   printf("%.3lf kl\n", getTotalWaterUsage(apartment1Usage));

    	       }

    	       else if(apartmentNUM == 2)
    	       {
    	    	   printf("%.3lf kl\n", getTotalWaterUsage(apartment2Usage));
    	       }

    	       else if(apartmentNUM == 3)
    	       {
    	    	   printf("%.3lf kl\n", getTotalWaterUsage(apartment3Usage));
    	       }

    	    break;

    	    //menu 3
    	    case 3:
    	       printf("\nChoose apartment (1, 2 or 3): \n"); //user enters which apartment to display the total bill for
    	       scanf("%d", &apartmentNUM);
    	       printf("\nTotal bill for apartment %d for this month: R", apartmentNUM);

    	    //print the total bill for user's choice of apartment
    	       if(apartmentNUM == 1)
    	       {
    	    	   printf("%.2lf\n", getTotalBill(apartment1Usage, (*APARTMENTnum1).tariff));
    	       }

    	       else if(apartmentNUM == 2)
    	       {
    	    	   printf("%.2lf\n", getTotalBill(apartment2Usage, (*APARTMENTnum2).tariff));
    	       }

    	       else if(apartmentNUM == 3)
    	       {
    	    	   printf("%.2lf\n", getTotalBill(apartment3Usage, (*APARTMENTnum3).tariff));
    	       }

    	    break;

    	    //menu 4
    	    case 4:
    	       printf("\nChoose apartment (1, 2 or 3): \n"); //user enters which apartment to display the water usage report for
    	       scanf("%d", &apartmentNUM);

    	    // Display the summary information of the specified apartment by calling the relevant function
    	       if(apartmentNUM == 1)
    	       {
    	    	   printApartmentReport(apartment1Usage, *APARTMENTnum1);
    	       }

    	       else if(apartmentNUM == 2)
    	       {
    	    	   printApartmentReport(apartment2Usage, *APARTMENTnum2);
    	       }

    	       else if(apartmentNUM == 3)
    	       {
    	    	   printApartmentReport(apartment3Usage, *APARTMENTnum3);
    	       }

    	    break;

    	    //menu 5
    	    case 5:
    	    
    	       leakage = checkForLeak(apartment1Usage);

    	    // Print the leak day of apartment if there is a leak
    	       if (leakage == 0)
    	       {
    	    	   printf("Apartment 1: No leak\n");
    	       }
    	    	
    	       else
    	       {
    	    	   printf("Apartment 1: Leak on day %d\n", leakage);
    	       }
    	    
    	       leakage = checkForLeak(apartment2Usage);
    	    
    	       if (leakage == 0)
    	       {
    	    	   printf("Apartment 2: No leak\n");
    	       }
    	    	
    	       else
    	       {
    	    	   printf("Apartment 2: Leak on day %d\n", leakage);
    	       }
    	    
    	    
    	       checkForLeak(apartment3Usage);
    	    
    	       if (leakage == 0)
    	       {
    	    	   printf("Apartment 3: No leak\n");
    	       }
    	    	
    	       else
    	       {
    	    	   printf("Apartment 3: Leak on day %d\n", leakage);
    	       }

    	    break;

    	    // menu 6
    	    case 6:

    	    // prompt user to enter the file name (of extension .txt)
    	       printf("Filename of text file: \n");
    	       scanf("%s", FileName);

    	    // write the building report on the text file with the name given by the user
    	       writeBuildingReport(apartment1Usage, apartment2Usage, apartment3Usage, *APARTMENTnum1, *APARTMENTnum2, *APARTMENTnum3, FileName);

    	    break;

    	    // menu 7
    	    case 7:
        	   printf("\nChoose apartment (1, 2 or 3): \n");
        	   scanf("%d", &apartmentNUM);

        	   printf("Save (1) or print (2) compact usage file:\n");
        	   scanf("%d", &Print_Save);

               if(Print_Save == 1)
               {
           		    if(apartmentNUM == 1)
           	        {
        		       saveCompactUsage(apartment1Usage, apartmentNUM);
        	        }

        	        else if (apartmentNUM == 2)
        	        {
        		       saveCompactUsage(apartment2Usage , apartmentNUM);
        	        }

        	        else if (apartmentNUM == 3)
        	        {
        		       saveCompactUsage(apartment3Usage , apartmentNUM);
        	        }

               }

               else if(Print_Save == 2)
               {
            	    sprintf(FileName, "compact_usage_%d.bin", apartmentNUM);

           		    //---------------------------------------------------------------------
           		   // Read information from the already existing binary file

           		    PtrFile = fopen(FileName, "rb"); // open a file for read only in binary mode

           		    // if file does not exist print a warning
           		    if(PtrFile == NULL)
           		    {
           			    printf("File could not be opened! Try to save the compact file first\n");
           		    }

           		    else
           		    {
           		    	printf("\nActive water usage report: \n");
           		    	while(!feof(PtrFile)) // loop until reach end of file
           			    {
           				    fread(&i, sizeof(int),1 , PtrFile); // read the hour over a month period
           			        fread(&Output_Usage, sizeof(double),1 , PtrFile); // read the hourly usage

           			        // display the day, time and amount of water used (non-zero entries)
           			        printf("Day %02d %02d:00 : %.3lf kl\n", monthHourToDay(i) , monthHourToDailyHour(i), Output_Usage);

           	            }
           		    }

           			 fclose(PtrFile); //close file
                }

       	    break;

    	    // menu 8
    	    case 8:
               printf("\nChoose apartment (1, 2 or 3): \n");
               scanf("%d", &apartmentNUM);

               // Find the maximum hourly usage of the user's choice of apartment
               if (apartmentNUM == 1)
               {
            	   PeakHour = GatewayFunc(apartment1Usage);
               }

               else if (apartmentNUM == 2)
               {
            	   PeakHour = GatewayFunc(apartment2Usage);
               }

               else if (apartmentNUM == 3)
               {
            	   PeakHour = GatewayFunc(apartment3Usage);
               }

               // Display on screen the maximum hourly usage of the user's choice of apartment
               printf("\nMaximum usage for apartment %d: \n", apartmentNUM);
               printf("Day %02d %02d:00 : %.3lf kl\n", monthHourToDay(PeakHour), monthHourToDailyHour(PeakHour), apartment2Usage[PeakHour]);

    	    break;

    	    default:
    	    printf("\nEnter a valid option:\n");
    	    break;

    	

	       // free the memory allocated to apartment data of each apartment
	       free(APARTMENTnum1);
	       free(APARTMENTnum2);
	       free(APARTMENTnum3);

           //Repeat the menu again
           printf("\nRP143 Water Calculator\n");
   	       printf("1. Print usage pattern for apartment\n2. Calculate and print total usage for apartment (in kl)\n");
           printf("3. Calculate and print total bill for apartment (in R)\n4. Print apartment usage report to screen\n");
           printf("5. Check building for leaks and print leak report\n6. Write building water usage report to text file\n");
   	       printf("7. Save or print compact binary usage file for apartment\n8. Determine and print hour with greatest usage for apartment\n");
           printf("10. Exit\n");

           printf("\nChoose an item from the menu: \n");
           scanf("%d", &option);
        }

     
    }
    
    return 0; // indicates successful termination

} //end main

/* ********************************************************************
* Function: printApartmentReport
* Purpose: Print a summary of information from a specified apartment
* Inputs: ApartmentData data (apartment info) and water usage pattern
* Outputs: None
* Operation: Print the report by calling other functions
*
**********************************************************************/

void printApartmentReport(double waterUsage[], ApartmentData data)
{
	 printf("\nApartment water usage report\n");
	 printf("Owner: %s %s\n", data.ownerName, data.ownerSurname);
	 printf("Tariff for apartment: R%.2lf per kl\n", data.tariff);
	 printf("Total usage for this month: %.3lf kl\n", getTotalWaterUsage(waterUsage));
	 printf("Total bill for this month: R%.2lf\n", getTotalBill(waterUsage, data.tariff));

	 return; // no return value
}

/* ********************************************************************
* Function: GatewayFunc
* Purpose: To aid in developing menu 8
* Inputs: Water usage pattern for apartment
* Outputs: Maximum usage hourly usage over a month
* Operation: Populates the nodes and find maximum usage
* by calling the relevant functions
*
**********************************************************************/

int GatewayFunc(double apartmentUsage[])
{
	int i, PeakHour; // counter and max hourly usage
	ListNodePtr startPtr = NULL;

	// populates a linked list for the relevant water usage
	for(i = 0; i < SIZE; i++)
	{
		if(apartmentUsage[i] != 0)
		{
			addNode(&startPtr, i, apartmentUsage[i]);
		}
	}

	// printList(startPtr); // Its purpose has been fulfilled

	// check for max. hourly usage
	PeakHour = monthHourOfMaxUsage(startPtr);

	return PeakHour; // return max usage
}



