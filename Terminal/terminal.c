#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	/*
	 This function will ask for cardholder's name and store it into terminal data 
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
	
	if ( (strncmp(tdate + 6, "202", 3) == 0) && (tdate[9] >= '3') && (tdate[9] <= '9') )
		year = 1;
		
	if (tdate[10] == '\0')											/*check for max string length = 5*/
		nulll = 1;

//	printf("REAL TIME DATE: %s\n", __DATE__);

//	getRealDate(termData);
	
	if (day && month && year && slash && nulll)
		return TERMINAL_OK;
	
	printf("\nday: %d month: %d slash: %d year: %d nulll: %d \n",day,month,slash,year,nulll);
	
	return WRONG_DATE;
}

void getRealDate(ST_terminalData_t *termData){
	/*
	 This function will read the date from your computer and store it into terminal data
	 with the mentioned size and format (DD/MM/YYYY)
	*/
	printf("The real date (formated):\n");
	strncpy(termData->transactionDate+6, __DATE__+7, 4); //set year
	termData->transactionDate[0] = __DATE__[4]; //set day 
	termData->transactionDate[1] = __DATE__[5]; //set day
	termData->transactionDate[2] = '/';
	termData->transactionDate[5] = '/';
	
	//month mapping
	if ( strncmp(__DATE__,"Jan",3) == 0 )
		strncpy(termData->transactionDate+3,"01",2);
	else if ( strncmp(__DATE__,"Feb",3) == 0 )
		strncpy(termData->transactionDate+3,"02",2);
	else if ( strncmp(__DATE__,"Mar",3) == 0 )
		strncpy(termData->transactionDate+3,"03",2);
	else if ( strncmp(__DATE__,"Apr",3) == 0 )
		strncpy(termData->transactionDate+3,"04",2);
	else if ( strncmp(__DATE__,"May",3) == 0 )
		strncpy(termData->transactionDate+3,"05",2);
	else if ( strncmp(__DATE__,"Jun",3) == 0 )
		strncpy(termData->transactionDate+3,"06",2);
	else if ( strncmp(__DATE__,"Jul",3) == 0 )
		strncpy(termData->transactionDate+3,"07",2);
	else if ( strncmp(__DATE__,"Aug",3) == 0 )
		strncpy(termData->transactionDate+3,"08",2);
	else if ( strncmp(__DATE__,"Sep",3) == 0 )
		strncpy(termData->transactionDate+3,"09",2);
	else if ( strncmp(__DATE__,"Oct",3) == 0 )
		strncpy(termData->transactionDate+3,"10",2);
	else if ( strncmp(__DATE__,"Nov",3) == 0 )
		strncpy(termData->transactionDate+3,"11",2);
	else if ( strncmp(__DATE__,"Dec",3) == 0 )
		strncpy(termData->transactionDate+3,"12",2);
	else 
		printf("Logical error\n");
														

	printf("DATE: %s SIZE: %d\n",termData->transactionDate, strlen(termData->transactionDate));
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
	/*
	 This function compares card expiry date with the transaction date 
	*/
	
	//str(n)cmp just compares the specified length of the two strings
	if ( strncmp(cardData->cardExpirationDate+3 ,termData->transactionDate+8 ,2) > 0 ) 
		return TERMINAL_OK;
	else if ( strncmp(cardData->cardExpirationDate+3 ,termData->transactionDate+8 ,2) == 0 ){
		if ( strncmp(cardData->cardExpirationDate ,termData->transactionDate+3 ,2) >= 0 )
			return TERMINAL_OK;
	}
	
	return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	/*
	 This function will ask for transaction amount and store it into terminal data 
	*/
	
	char check_amount[32] ;
	int dot = 0; //dot flag
	
	printf("Enter transaction amount: ");
	fflush(stdout); fflush(stdin);
	scanf("%s", check_amount);           /*To Do : Accept float formula like this 3.402823e+38 */
	
	//ADDITIONAL FEATURE: check if valid value
	for (int i = 0; i<strlen(check_amount); i++){
		
		//dot check
		if ( (check_amount[i] == '.') && (i != 0) && (i != strlen(check_amount)-1) ){
			if (dot == 0)	//check dot flag
				dot = 1;	// dot flag is up
			else
				return INVALID_AMOUNT;	//as '.' is valid for only one appearance (but not at start or end)
			
			continue; // to escape from numarical check below
		}
		
		//numarical check
		if( (check_amount[i] < '0') || (check_amount[i] > '9') )
			return INVALID_AMOUNT;
	}
	/*END OF ADDITIONAL FEATURE*/
	
	termData->transAmount = atof(check_amount);
	
	printf("\nYou entered: %f \n",termData->transAmount);
	
	// check for positive none-zero value compatible with 4-byte float upper bound 
	if ( (termData->transAmount <= 0) || (termData->transAmount >= FLT_MAX) )
		return INVALID_AMOUNT;

	return TERMINAL_OK;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
	/*
	 This function takes the maximum allowed amount and store it into terminal data 
	*/
	
	if (maxAmount <= 0)
		return INVALID_MAX_AMOUNT;
	
	termData->maxTransAmount = maxAmount;
	
	return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	/*
	 This function compares transaction amount with the terminal maximum allowed transaction amount 
	*/
	
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	
	return TERMINAL_OK;
	
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){   // Optional
	/*
	 This function will check if the PAN is a luhn number or not
	*/
	return WRONG_PAN;
} 

