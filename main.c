#include <stdio.h>
#include "card.h"
#include "terminal.h"


int main(void){
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	
	while( getCardHolderName(&cardData) == WRONG_NAME){
		printf("\nInvalid name.\nPlease, enter a name between 20 to 24 characters \n");		
	}
	
	while( getCardExpiryDate(&cardData) == WRONG_EXP_DATE){
		printf("\nInvalid expireation date.\nPlease, enter a date like this format MM/YY \n");		
	}
	
	while( getCardPAN(&cardData) == WRONG_PAN){
		printf("\nInvalid PAN .\nPlease, enter a PAN between 16 to 19 characters \n");		
	}
		
	while( getTransactionDate(&termData) == WRONG_DATE){
		printf("\nInvalid Date .\nPlease, enter transaction date as follows DD/MM/YYYY: \n");		
	}
	
	
	printf("\nExit Program. \n");
	
	return 0;
}