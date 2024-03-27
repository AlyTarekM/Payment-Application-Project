/*
 * server.c
 *
 *  Created on: 23 Nov 2022
 *      Author: Aly Tarek
 */

#include"server.h"
#include<stdio.h>
#include<string.h>

/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/

ST_accountsDB_t accountsDB[255]= {1800.0, BLOCKED, "8989374615436851",5000.0, BLOCKED, "0123456789123456",3000.0, BLOCKED, "6134567894254521"};

ST_transaction_t transactionsDB[255]={0};

uint8_t PANindex=0;

/*******************************************************************************
 *                        Function Definitions                                 *
 *******************************************************************************/

EN_transStat_t recieveTransactionData(ST_transaction_t *transData){


			ST_accountsDB_t reference;
		 if((isValidAccount(&(transData->cardHolderData),&reference))==ACCOUNT_NOT_FOUND){
				{
					transData->transState=FRAUD_CARD;
					return FRAUD_CARD;
				}


		}
		else if((isBlockedAccount(&reference))==BLOCKED_ACCOUNT)
		{
			transData->transState=DECLINED_STOLEN_CARD;
			return DECLINED_STOLEN_CARD;
		}
		else if((isValidAccount(&(transData->cardHolderData),&reference))==ACCOUNT_NOT_FOUND)
		{
			transData->transState=FRAUD_CARD;
			return FRAUD_CARD;
		}
		else if((isAmountAvailable(&(transData->terminalData), &reference))==LOW_BALANCE)
			{

				transData->transState=DECLINED_INSUFFECIENT_FUND;
				return DECLINED_INSUFFECIENT_FUND;
			}
		else
		{

			transData->transState=APPROVED;
			for (int i=0;i<255;i++){
				if(	strcmp(((char *)reference.primaryAccountNumber),( (char *)accountsDB[i].primaryAccountNumber))==0){
			accountsDB[i].balance-=transData->terminalData.transAmount;
			break;
				}

		}
			return APPROVED;
		}
	/*accountsDB[PANindex].balance-=transData->terminalData.transAmount;
	transactionsDB[i]->terminalData.transAmount=transData->terminalData.transAmount;
	transData->transState=APPROVED;
	return APPROVED;*/
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
	uint8_t i;

	for (i=0;i<255;i++){
		if(	strcmp(((char *)cardData->primaryAccountNumber),( (char *)accountsDB[i].primaryAccountNumber))==0){

			accountRefrence->balance = accountsDB[i].balance;
			accountRefrence->state = accountsDB[i].state;

			PANindex=i;

			strcpy (((char *)accountRefrence->primaryAccountNumber),((char *)accountsDB[i].primaryAccountNumber));
			return SERVER_OK;
		}
	}

	accountRefrence=NULL;
	return  ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
	uint8_t If_Blocked;

	if(accountRefrence->state==BLOCKED){
		If_Blocked=BLOCKED_ACCOUNT;
	}
	else{
		If_Blocked=SERVER_OK;
	}
	return If_Blocked;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
	uint8_t If_Available;
	if((termData->transAmount) > accountRefrence->balance){
		If_Available=LOW_BALANCE;
	}
	else{
		If_Available=SERVER_OK;
	}
	return If_Available;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){


	static uint32_t sequence_number=256;
	if(sequence_number>255){
		return FRAUD_CARD;
	}
transData->transactionSequenceNumber=sequence_number;
transactionsDB[sequence_number]=*transData;
transactionsDB[sequence_number].terminalData.transAmount=transData->terminalData.transAmount;
sequence_number++;

listSavedTransactions();

	return SERVER_OK;
}
void listSavedTransactions(void){
	uint8_t i=0;
	while(transactionsDB[i].cardHolderData.cardHolderName[0])
	{
		printf("#############################\n");
		printf("Transaction Sequence Number: %ld\n",transactionsDB[i].transactionSequenceNumber);
		fflush(stdout);
printf("Transaction Date Is:");
puts((char*)transactionsDB[i].terminalData.transactionDate);
printf("Transaction Amount: %f \n",transactionsDB->terminalData.transAmount);
printf("Transaction State:%d \n",transactionsDB[i].transState);
printf("Terminal Max Amount: %f \n",transactionsDB[i].terminalData.maxTransAmount);
puts((const char *)transactionsDB[i].cardHolderData.cardHolderName);
printf("PAN : %s \n",transactionsDB[i].cardHolderData.primaryAccountNumber);
printf("Card Expiration Date:");
puts((char*)transactionsDB[i].cardHolderData.cardExpirationDate);
printf("\n#############################\n");
i++;
//printf("Amount= %f\n",accountsDB[0].balance);
	}
}
