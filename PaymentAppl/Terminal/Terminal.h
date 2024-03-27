/*
 * Terminal.h
 *
 *  Created on: 22 Nov 2022
 *      Author: Aly Tarek
 */

#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "std_types.h"
#include "../Card/Card.h"

/*******************************************************************************
 *                                Typedefs                                  *
 *******************************************************************************/

typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;


/*******************************************************************************
 *                        Function Prototypes                                  *
 *******************************************************************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);




#endif /* TERMINAL_TERMINAL_H_ */
