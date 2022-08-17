#include "server.h"

ST_accountsDB_t accounts[255] ={{1000,"100000020000003000"},{2000,"100000020000003001"},{3000,"100000020000003002"}};
ST_transaction_t transactions[255] = {0};

int currnentsizeOfAccounts = 3;
int currnentsizeOfTransactions = 0;
int indexOfAccount;
char* state[] = { "approved", "insufficient fund", "stolen card",  "internal server error" };      
static int seqNumber = 1;


EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int i;
	for (i = 0; i < currnentsizeOfAccounts; i++)
	{
		if (strcmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber) == 0)
			break;
	}

	if (i == currnentsizeOfAccounts)         // account isnot exist in database
		return ACCOUNT_NOT_FOUND;
	else
	{
		indexOfAccount = i;
		return oK;
	}
}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount > accounts[indexOfAccount].balance)     // transAmount > balance
		return LOW_BALANCE;
	else
		return oK;
}


/*
this function will take all transaction data and validate its data.
It checks the account details and amount availability.
If the account does not exist return DECLINED_STOLEN_CARD
if the amount is not available will return DECLINED_INSUFFECIENT_FUND
if transaction database is full will return INTERNAL_SERVER_ERROR and will not save the transaction
else It will update the database with the new balance and returns APPROVED.
*/

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND )    // account isnot exist in database
	{
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}  
	else if (isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE )     // transAmount > balance
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (currnentsizeOfTransactions > 254)                                 // transactions reaches 255
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else
	{
		accounts[indexOfAccount].balance -= transData->terminalData.transAmount;
		transData->transState = APPROVED;
		return APPROVED;
	}
}


/*
It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
It saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
If transaction can't be saved will return SAVING_FAILED, else will return OK
*/

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (transData->transState == APPROVED || transData->transState == DECLINED_INSUFFECIENT_FUND || transData->transState == DECLINED_STOLEN_CARD)
	{
		transData->transactionSequenceNumber = seqNumber++;
		transactions[currnentsizeOfTransactions] = *transData;
		transData->transactionSequenceNumber = currnentsizeOfTransactions;
		currnentsizeOfTransactions++;
		return oK;
	}
	if (transData->transState == INTERNAL_SERVER_ERROR)
		return SAVING_FAILED;
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	int i;
	for ( i = 0; i < currnentsizeOfTransactions; i++)
	{
		if ( i == transactionSequenceNumber && (& transactions[i] == transData) )
			return oK;
	}
	return TRANSACTION_NOT_FOUND;
}


void printAllTransactions()
{
	printf("Transactions\n");
	if (currnentsizeOfTransactions == 0)
		printf("transactions' database is empty\n\n");
	else
	{
		int i;
		for (i = 0; i < currnentsizeOfTransactions; i++)
		{
			printf("Transaction Sequence Number   :%d\n", transactions[i].transactionSequenceNumber);
			printf("Expiry date                   :%s\n", transactions[i].cardHolderData.cardExpirationDate);
			printf("Holder Name                   :%s\n", transactions[i].cardHolderData.cardHolderName);
			printf("Pan                           :%s\n", transactions[i].cardHolderData.primaryAccountNumber);
			printf("Transaction Date              :%s\n", transactions[i].terminalData.transactionDate);
			printf("Max transaction Amount        :%.2f\n", transactions[i].terminalData.maxTransAmount);
			printf("transaction Amount            :%.2f\n", transactions[i].terminalData.transAmount);
			printf("Transaction state             :%s\n", state[transactions[i].transState]);
			printf("------------------------------------------------------------\n\n\n");
		}
	}
}

void printAllAcounts()
{
	printf("accounts\n");
	int i;
	for (i = 0; i < currnentsizeOfAccounts; i++)
	{
		printf("            balance :%.2f\n", accounts[i].balance);
		printf("            PAN     :%s\n", accounts[i].primaryAccountNumber);
		printf("----------------------------------------\n");
	}
	printf("\n\n");
}
