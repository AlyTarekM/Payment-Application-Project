/*
 * Card.c
 *
 *  Created on: 22 Nov 2022
 *      Author: Aly Tarek
 */

#include <stdio.h>
#include"Card.h"
#include"string.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
	uint8_t Name_Size, Card_State;
	printf("Please Enter Card Holder's Name:\n");
	fflush(stdout);
	gets((char*)cardData->cardHolderName);
	Name_Size = strlen((char*)cardData->cardHolderName);
	if (Name_Size == NULL || Name_Size < 20 || Name_Size > 24) {
		Card_State = WRONG_NAME;
	} else {
		Card_State = CARD_OK;
	}
	return Card_State;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
	uint8_t Date_Size, Card_State;
	printf("Please Enter Card Expiry Date in Format MM/YY:\n");
	fflush(stdout);
	gets((char*)cardData->cardExpirationDate);
	Date_Size = strlen((char*)cardData->cardExpirationDate);
	if (Date_Size != 5) {
		Card_State = WRONG_EXP_DATE;

	}
	else if((cardData->cardExpirationDate[0]- '0')>1){
		Card_State= WRONG_EXP_DATE;
	}
	else {
		Card_State = CARD_OK;
	}

	return Card_State;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
	uint8_t PAN_Size, Card_State;
	printf("Please Enter Card PAN:\n");
	fflush(stdout);
	gets((char*)cardData->primaryAccountNumber);
	PAN_Size = strlen((char*)cardData->primaryAccountNumber);
	if (PAN_Size < 16 || PAN_Size > 19) {
		Card_State = WRONG_PAN;
	} else {
		Card_State = CARD_OK;
	}
	return Card_State;
}

