#include <stdio.h>
#include <string.h>
#include "card.h"

//#define p(x) printf("x")

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	/*
	 This function will ask for cardholder's name and store it into card data 
	*/
	
	printf("Enter your name: ");
	fflush(stdout); fflush(stdin);
	gets(cardData->cardHolderName);
	//fgets: provides better protection against buffer overflows
	
	if (cardData->cardHolderName == NULL || 
	strlen(cardData->cardHolderName) > 24 ||
	strlen(cardData->cardHolderName) < 20)  
		return WRONG_NAME;
		
	return CARD_OK;
	
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	/*
	 This function will ask for card expiry date and store it into card data 
	*/
	int month = 0, year = 0, slash = 0 , nulll = 0;
	
	printf("Enter card expiry date MM/YY: ");
	fflush(stdout); fflush(stdin);
	scanf("%s",cardData->cardExpirationDate);
	
	#define exp cardData->cardExpirationDate  //just to simple writing the code
	
	if ( ( (exp[0] == '0') && (exp[1] >= '1') && (exp[1] <= '9') ) || ( (exp[0] == '1') && (exp[1] >= '0') && (exp[1] <= '2') ) )
		month = 1;												/*check month 01 - 12*/

	if (exp[2] == '/')											/*check front slash*/
		slash = 1;
		
	if ((exp[3] == '2') && (exp[4] >= '3') && (exp[4] <= '9')) 	/*check years between 2023 to 2029*/ 
		year = 1;
	
	if (exp[5] == '\0')											/*check for max string length = 5*/
		nulll = 1;
	
	//printf("\nmonth: %d slash: %d year: %d nulll: %d \n",month,slash,year,nulll);
	
	if (month && year && slash && nulll)
		return CARD_OK;
	
//  Other formating:
//	if( ( ((exp[0] == '0') && (exp[1] >= 1) && (exp[1] <= 9)) || ( (exp[0] == '1') && (exp[1] >= 0) && (exp[1] <= 2)) )&& 
//		 /*check if month 01 to 09*/                       /*check if month 10 to 12*/
//		(  exp[2] == '/'					 /*check front slash*/									      )&&
//		(  exp[3] == '2'					 /*years between 20(2)3 to 20(2)9*/ 				          )&&
//		( (exp[4] >= '3') && (exp[4] <= '9') /*years between 202(3) to 202(9)*/ 						  )&&
//		(  exp[5] == '\0') )				 
//		return CARD_OK;
	
	return WRONG_EXP_DATE;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	/*
	 This function will ask for the card's Primary Account Number (PAN) and store it in card data
	*/
	
	printf("Enter your PAN: ");
	fflush(stdout); fflush(stdin);
	gets(cardData->primaryAccountNumber);
	
	if (cardData->primaryAccountNumber == NULL || 
	strlen(cardData->primaryAccountNumber) > 19 ||
	strlen(cardData->primaryAccountNumber) < 16)  
		return WRONG_PAN;
		
	return CARD_OK;
}

