/* Filename: linkedLists.c
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

#include "linkedLists.h"
#include <stdio.h>
#include <stdlib.h>

/* ********************************************************************
* Function: addNode
* Purpose: Populates a linked list with only the corresponding non-zero
* values in the array.
* Inputs: Pointer to the first node, monthHour and water usage pattern
* Outputs: None
* Operation: Formulate a linked list
*
**********************************************************************/

void addNode(ListNodePtr *startPtrPtr, int epoch, double usage)
{
	ListNodePtr newPtr, CurrentPtr;

	// check if the given prev_node is NULL
	if(*startPtrPtr == NULL)
	{
		// allocate new node
		CurrentPtr = malloc(sizeof(ListNode)); // create node

		// put in the relevant variables if type ListNodePtr
		// put in the data
		(*CurrentPtr).usage = usage;

		(*CurrentPtr).monthHour = epoch;
		(*CurrentPtr).nextPtr = NULL;

		*startPtrPtr = CurrentPtr;
	}

	// If the Linked List is empty, then make the new node as head
	else
	{
		while((*CurrentPtr).nextPtr != NULL)
		{
			CurrentPtr = (*CurrentPtr).nextPtr;
			newPtr = malloc(sizeof(ListNode)); // // create node

			// put in the relevant variables if type ListNodePtr
			// put in the data
			(*newPtr).usage = usage;

			(*newPtr).monthHour = epoch;
			(*newPtr).nextPtr = NULL;  // move the next of prev_node as new_node
			(*CurrentPtr).nextPtr = newPtr; //move the next of prev_node as new_node
		}
	}
	return;
}

/* ********************************************************************
* Function: printList
* Purpose: Debugging
* Inputs: Pointer to the first node
* Outputs: None
* Operation: Prints the content of the current linked list to screen
*
**********************************************************************/

void printList(ListNodePtr startPtr)
{
	// if there are no nodes
	if(startPtr == NULL)
	{
		printf("Empty.\n");
	}

	// if there are, keep track of the list
	else
	{
		printf("Monthly Hour: %d, hourly usage: %.3lf\n", (*startPtr).monthHour, (*startPtr).usage);
		while((*startPtr).nextPtr != NULL)
		{
			startPtr = (*startPtr).nextPtr;
			printf("Monthly Hour: %d, hourly usage: %.3lf\n", (*startPtr).monthHour, (*startPtr).usage);
		}
	}

	return;
}

/* ********************************************************************
* Function: monthHourOfMaxUsage
* Purpose: Find the maximum hourly usage of the water usage pattern
* Inputs: Pointer to the first node
* Outputs: None
* Operation: Compare list until reach maximum usage
*
**********************************************************************/

int monthHourOfMaxUsage(ListNodePtr startPtr)
{
    double PeakUsage = 0;
    int PeakHour = 0;

    // while not the end of the list
    while(startPtr != NULL)
    {
        // if 'current' node is greater than 'new' node, assign
    	// relevant variable of type ListNodePtr
    	if(startPtr->usage > PeakUsage)
        {
            PeakUsage = startPtr->usage;
            
            PeakHour = startPtr->monthHour;
        }
        
        // if not, move on to the next node
    	else
        {
        	startPtr = startPtr->nextPtr;
        }
    }

	return PeakHour; // return the max. hourly usage
}
