#include <stdio.h>
#include "card.h"

//extern ST_cardData_t;

int main(void){
	ST_cardData_t cardData;
	
	while( getCardHolderName(&cardData) == WRONG_NAME){
		printf("Invalid name.\nPlease, enter a name between 20 to 24 characters \n");		
	}
	
	
	printf("Exit Program. \n");
	
	return 0;
}