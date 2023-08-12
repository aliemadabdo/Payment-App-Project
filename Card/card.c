#include <stdio.h>
#include <string.h>
#include "card.h"

//#define p(x) printf("x")

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
	/*
	 This function will ask for cardholder's name and store it into card data 
	*/
	
	printf("Enter your name: ");
	fflush(stdout);
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
	

	
	
	return CARD_OK
}