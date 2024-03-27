/*
 * App.c
 *
 *  Created on: 22 Nov 2022
 *      Author: Aly Tarek
 */

#include"App.h"
#include"stdio.h"

/*******************************************************************************
 *                        Function Definitions                                 *
 *******************************************************************************/
ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_accountsDB_t accountRefrence;
	ST_transaction_t transData;
void appStart(void) {

	while (WRONG_NAME == getCardHolderName(&cardData)) {
		printf("Card Holder Name Is Wrong!\n");
	}
	while (WRONG_EXP_DATE == getCardExpiryDate(&cardData)) {
		printf("Wrong Expiry Date!\n");
	}
	while (WRONG_PAN == getCardPAN(&cardData)) {
		printf("Wrong PAN!\n");
	}
	while (WRONG_DATE == getTransactionDate(&termData)) {
		printf("Wrong Transaction Date!\n");
	}
	while (isCardExpired(&cardData, &termData) == EXPIRED_CARD) {
		printf("Declined Expired Card!\n");
		return;
	}
	setMaxAmount(&termData, 9000.0);
	while (INVALID_AMOUNT == getTransactionAmount(&termData)) {
		printf("Invalid Amount!\n");
	}
	while (EXCEED_MAX_AMOUNT == isBelowMaxAmount(&termData)) {
		printf("Declined Amount Exceeding Limit\n");
		return;
	}
	transData.cardHolderData=cardData;
	transData.terminalData=termData;

	while ((recieveTransactionData(&transData) == FRAUD_CARD)
			|| (recieveTransactionData(&transData) == DECLINED_STOLEN_CARD)) {
		printf("Declined Invalid Account!\n");
		return;
	}
	while ((recieveTransactionData(&transData) == DECLINED_INSUFFECIENT_FUND)) {
		printf("Declined Insuffecient funds!\n");
		return;
	}
	while(ACCOUNT_NOT_FOUND == isValidAccount(&cardData, &accountRefrence)){
		printf("Declined Invalid Account!!!\n");
		return;
	}
	while(LOW_BALANCE == isAmountAvailable(&termData, &accountRefrence)){
		printf("Declined Insuffecient funds!\n");
	}
	//saveTransaction(&transData);

}

void getCardPANTest(void){
	if(getCardPAN(&cardData)==CARD_OK){
		printf("Card Holder Name is Correct\n");
	}
	else {
		printf("Card Holder Name is not correct ERROR!\n");
	}
}
void getTransactionDateTest(void){
	if(getTransactionDate(&termData)==TERMINAL_OK){
		printf("Correct Date!\n");
	}
	else printf("Incorrect Date!\n");
}
void isCardExpriedTest(void){
	if(isCardExpired(&cardData, &termData)==TERMINAL_OK){
		printf("Card Not Expired!");
	}
	else printf("Card is Expired!\n");
}
void getTransactionAmountTest(void){
	if(getTransactionAmount(&termData)==TERMINAL_OK){
		printf("Amount is Correct!");
	}
	else{
		printf("Amount is not Correct!\n");
	}
}
void isBelowMaxAmountTest(void){
	setMaxAmount(&termData, 9000.0);
	printf("\nEnter Transaction Amount\n");
	fflush(stdout);
	scanf("%f",&termData.transAmount);
	if(isBelowMaxAmount(&termData)==TERMINAL_OK){
		printf("Below Max Amount!\n");

	}
	else printf("Error Exceed!");
}
void setMaxAmountTest(void){
	if(setMaxAmount(&termData, 100)==TERMINAL_OK){
		printf("Set Max Amount Success!\n");
	}
	else printf("Set Max Amount Failed :(\n");
}
void recieveTransactionDataTest(void){
	if(recieveTransactionData(&transData)==FRAUD_CARD){
		printf("Account Does not exist!\n");
	}
	else if(recieveTransactionData(&transData)==DECLINED_INSUFFECIENT_FUND){
		printf("Insuffecient Fund Error!\n");
	}
	else if(recieveTransactionData(&transData)==DECLINED_STOLEN_CARD){
		printf("Card Is stolen!\n");
	}
	else printf("Approved!!");
}
void isValidAccountTest(void){
	if(isValidAccount(&cardData, &accountRefrence)==SERVER_OK){
		printf("Account is Valid!\n");
	}
	else printf("Account Invalid!\n");
}
void isBlockedAccountTest(void){
	printf("Enter PAN:\n");
		fflush(stdout);
		scanf("%f",&accountRefrence.primaryAccountNumber);
	if(isBlockedAccount(&accountRefrence)==SERVER_OK){
		//printf("Account is not Blocked!(Running Account)\n");
		printf("Account is Blocked!\n");

	}
	else {
		//printf("Account is Blocked!\n");
	}
}
void isAmountAvailableTest(void){
	if(isAmountAvailable(&termData, &accountRefrence)==SERVER_OK){
		printf("Amount Available!\n");
	}
	else printf("Amount Unavailable!!\n");
}
void saveTransactionTest(void){
	if(saveTransaction(&transData)==SERVER_OK){
		printf("Transaction Saved!\n");
	}
	else printf("Transaction Error!\n");
}
void listSavedTransactionsTest(void){
	listSavedTransactions();
}

int main(void) {
	//appStart();
	//getCardPANTest();
	//getTransactionDateTest();
	//isCardExpriedTest();
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();
	//recieveTransactionDataTest();
	//isValidAccountTest();
	//isAmountAvailableTest();
	//isBlockedAccountTest();
	saveTransactionTest();
	//listSavedTransactionsTest();
	//appStart();
}


