#include "app.h"

void appStart(void)
{
    ST_cardData_t mycard;
    while (getCardHolderName(&mycard) != OK) {}   // ask user for card holder name
    while (getCardExpiryDate(&mycard) != OK){}    // ask user for card expiry date
    while (getCardPAN(&mycard) != OK){}           // ask user for card PAN

    ST_terminalData_t myterminal;
    while (getTransactionDate(&myterminal) != Ok) {}         // read date from computer
    

    if( isCardExpired(mycard, myterminal) == EXPIRED_CARD )
        printf("\nOperation failed --> expired card\n\n");
    else
    {
        while (setMaxAmount(&myterminal) != Ok) {}               // ask user for max transaction amount
        while (getTransactionAmount(&myterminal) != Ok) {}       // ask user for  transaction amount
        ST_transaction_t myTransaction = { mycard,myterminal };

        if (isBelowMaxAmount(&myterminal) == EXCEED_MAX_AMOUNT)
            printf("\nOperation failed --> exceed max amount\n\n");
        else
        {
            switch ( recieveTransactionData(&myTransaction) )
            {
                case DECLINED_STOLEN_CARD:
                    printf("\nOperation failed --> not valid account\n\n");
                    saveTransaction(&myTransaction);
                    break;

                case DECLINED_INSUFFECIENT_FUND:
                    printf("\nOperation failed --> balance isnot enough\n\n");
                    saveTransaction(&myTransaction);
                    break;

                case APPROVED:
                    if (saveTransaction(&myTransaction) == oK)
                        printf("\noperation accomplished successfully\n\n");
                    break;
            }
        }
    }
}
