#include <stdio.h>
#include "card.h"

//extern ST_cardData_t;

int main(void){
	ST_cardData_t cardData;
	
	while( getCardHolderName(&cardData) == WRONG_NAME){
		printf("\nInvalid name.\nPlease, enter a name between 20 to 24 characters \n");		
	}
	
	while( getCardExpiryDate(&cardData) == WRONG_EXP_DATE){
		printf("\nInvalid expireation date.\nPlease, enter a date like this format MM/YY \n");		
	}
	
	printf("Exit Program. \n");
	
	return 0;
}