/*
 * Terminal.c
 *
 *  Created on: 22 Nov 2022
 *      Author: Aly Tarek
 */

#include"Terminal.h"
#include<stdio.h>
#include<string.h>


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){

	uint8_t count=0;

	printf("Please Enter Transaction Date:\n");
	printf("in format of DD/MM/YYYY\n");
	fflush(stdout);
	gets((char*)termData->transactionDate);
	while(termData->transactionDate[count]!='\0'){
		count++;
	}
	if (count==0)
	{
		return WRONG_DATE;
	}

	else if((count<9) )
	{
		return WRONG_DATE;
	}
	else if(((termData->transactionDate[0]-'0')>3) ||
			((termData->transactionDate[1]<0) && (termData->transactionDate[1]>9) )||
			(termData->transactionDate[2]!='/')     ||
			(((termData->transactionDate[3] - '0') != 0) && ((termData->transactionDate[3]-'0')!=1)) ||
			((termData->transactionDate[4]<0) && (termData->transactionDate[4]>9) )||
			(termData->transactionDate[5]!='/')  ||
			((termData->transactionDate[6]<0) && (termData->transactionDate[6]>9) )||
			((termData->transactionDate[7]<0) && (termData->transactionDate[7]>9) )||
			((termData->transactionDate[8]<0) && (termData->transactionDate[8]>9) )||
			((termData->transactionDate[9]<0) && (termData->transactionDate[9]>9) ))

	{
		return WRONG_DATE;
	}
	else
		return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	if((((cardData->cardExpirationDate[3])*10)+(cardData->cardExpirationDate[4]))<
			(((termData->transactionDate[8])*10)+(termData->transactionDate[9])))
	{
		return EXPIRED_CARD;
	}
	else if (((cardData->cardExpirationDate[3]*10)+(cardData->cardExpirationDate[4]))==
			((termData->transactionDate[8]*10)+(termData->transactionDate[9])))
	{
		if(((cardData->cardExpirationDate[0]*10)+(cardData->cardExpirationDate[1]))<
				((termData->transactionDate[3]*10)+(termData->transactionDate[4])))
		{
			return EXPIRED_CARD;
		}
	}
	return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	uint8_t Transaction_State;
	printf("Please Enter Transaction Amount:\n");
	fflush(stdout);
	scanf("%f",&(termData->transAmount));
	if((termData->transAmount)<=0){
		Transaction_State=INVALID_AMOUNT;
	}
	else{
		Transaction_State=TERMINAL_OK;
	}
	return Transaction_State;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){
	uint8_t MaxAmount_State;
	if(maxAmount>0){
		termData->maxTransAmount=maxAmount;
		MaxAmount_State= TERMINAL_OK;
	}
	else{
		MaxAmount_State= INVALID_MAX_AMOUNT;
	}
	return MaxAmount_State;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	uint8_t State;
	if((termData->transAmount) > (termData->maxTransAmount)){
		State= EXCEED_MAX_AMOUNT;
	}
	else{
		State= TERMINAL_OK;
	}
	return State;
}

