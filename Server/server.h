#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef struct ST_accountsDB_t           // account structure
{
	float balance;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef enum EN_transState_t         
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
	oK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;             // card information
	ST_terminalData_t terminalData;           // terminal information      
	EN_transState_t transState;               // respone of bank of card
	uint32_t transactionSequenceNumber;       // serial number of operation done by terminal
}ST_transaction_t;

EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
void printAllAcounts();
void printAllTransactions();

#endif // SERVER_H_INCLUDED
