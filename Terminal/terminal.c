#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include<conio.h>
#include<time.h>

/*
time_t datatype is a data type in the ISO C library defined for storing system time values
struct tm is a structure defined in the time.h header file
Each of the member objects of struct tm contains the time and date stored on a machine.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{ 
    time_t t = time(NULL);           // t is Hours since January 1, 1970   

    if (localtime(&t) == NULL)
        return WRONG_DATE;

    struct tm tm = *localtime(&t);   // filling tm_mday , tm_mon , tm_year
    // DD/MM/YYYY
    if (tm.tm_mday < 10 && (tm.tm_mon + 1) < 10)
        snprintf(termData->transactionDate, 11, "0%d/0%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // puts string into buffer
    else if (tm.tm_mday > 10 && (tm.tm_mon + 1) < 10)
        snprintf(termData->transactionDate, 11, "%d/0%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // puts string into buffer
    else if (tm.tm_mday < 10 && (tm.tm_mon + 1) > 10)
        snprintf(termData->transactionDate, 11, "0%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // puts string into buffer
    else
        snprintf(termData->transactionDate, 11, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // puts string into buffer
    return Ok;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    char cardYear[5];
    char currentYear[5];

    snprintf(cardYear, 5, "%c%c%c%c", '2', '0', cardData.cardExpirationDate[3], cardData.cardExpirationDate[4]); // puts string into buffer
    snprintf(currentYear, 5, "%c%c%c%c",termData.transactionDate[6],termData.transactionDate[7], termData.transactionDate[8], termData.transactionDate[9]); // puts string into buffer    

    if (atoi(cardYear) > atoi(currentYear))
        return Ok;
    else if (atoi(cardYear) < atoi(currentYear))
    {
        return EXPIRED_CARD;
    }
    else
    {
        char cardMonth[3];
        char currentMonth[3];
        snprintf(cardMonth, 3, "%c%c", cardData.cardExpirationDate[0], cardData.cardExpirationDate[1]); // puts string into buffer
        snprintf(currentMonth, 3,"%c%c", termData.transactionDate[3], termData.transactionDate[4]); // puts string into buffer
        if (atoi(cardMonth) < atoi(currentMonth))
            return EXPIRED_CARD;
    }
    return Ok;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Enter the transaction amount: ");
    float temp;
    scanf("%f", &temp);

    if (temp <= 0)
        return INVALID_AMOUNT;
    else
    {
        termData->transAmount = temp;
        return Ok;
    }
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return Ok;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    printf("Enter maximum transaction amount: ");
    float temp;
    scanf("%f", &temp);

    if (temp <= 0)
        return INVALID_MAX_AMOUNT;
    else
    {
        termData->maxTransAmount = temp;
        return Ok;
    }
}