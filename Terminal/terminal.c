#include <stdio.h>
#include <string.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	/*
	 This function will ask for cardholder's name and store it into card data 
	*/
	
	int day = 0, month = 0, year = 0, slash = 0 , nulll = 0;
	
	printf("Enter transaction date DD/MM/YYYY: ");
	fflush(stdout); fflush(stdin);
	scanf("%s",termData->transactionDate);
	
	#define tdate termData->transactionDate  //just to simple writing the code
	if ( ( (tdate[0] == '0') && (tdate[1] >= '1') && (tdate[1] <= '9') ) || 
		 ( (tdate[0] == '1') && (tdate[1] >= '0') && (tdate[1] <= '9') ) ||
		 ( (tdate[0] == '2') && (tdate[1] >= '0') && (tdate[1] <= '9') ) ||		 
		 ( (tdate[0] == '3') && (tdate[1] >= '0') && (tdate[1] <= '1') ) )
		day = 1;
	
	if ( ( (tdate[3] == '0') && (tdate[4] >= '1') && (tdate[4] <= '9') ) || 
		 ( (tdate[3] == '1') && (tdate[4] >= '0') && (tdate[4] <= '2') ) )
		month = 1;												/*check month 01 - 12*/

	if ((tdate[2] == '/') && (tdate[5] == '/'))											/*check front slash*/
		slash = 1;
	
	if (strncmp(tdate + 6, "2023", 4) == 0)
		year = 1;
		
	if (tdate[10] == '\0')											/*check for max string length = 5*/
		nulll = 1;
	
	printf("\nday: %d month: %d slash: %d year: %d nulll: %d \n",day,month,slash,year,nulll);
	printf("REAL TIME DATE: %s\n", __DATE__);
	
	if (day && month && year && slash && nulll)
		return TERMINAL_OK;
	
	return WRONG_DATE;
}
	
//	if ((tdate[6] == '2') && (tdate[7] == '0') && (tdate[8] == '2') && (tdate[9] <= '9') && (tdate[9] >= '3')) 	/*check years between 2023 to 2029*/ 
//		year = 1;
	
