#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>


/*
reading characters from user
why fgets not scanf  --> to take input of string with spaces in between characters
why fgets not gets   --> gets()  suffers from buffer overflow (takes more input than it is supposed to take).
                     --> buffer overflow is solved using fgets().

fgets() is a safer version of gets() where you can provide limitation on input size.
You can also decide to take input from which stream(e.g. File or standard input).


fgets() keeps reading input until newline character and stop if maximum limit of input characters is reached

if user enter characters less than Maximum numbers of characters 
--->fgets will take these characters then add character whose value is (10) then null character
if user enter characters more than Maximum numbers of characters fgets add character whose value is (10) then null character
--->fgets will take n-1 characters then add null character

*/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{ 
    printf("Enter Card holder name: ");
    char bStr[26];
    fgets(bStr, 26, stdin);        
    if (!strchr(bStr, '\n'))            //remove extra characters from fgets
        while (fgetc(stdin) != '\n');
 
    /*
        ahmed                         'a' , 'h' , 'm' , 'e' , 'd', 10 ,'\0'
        ahmed mahmoud mohamed         'a' , 'h' , ............................ , 'e' , 'd' , 10 , '\0'
        ahmed mahmoud mohamed abc     'a' , 'h' , ............................ , 'e' , 'd' , 'a' , 'b' , 'c' , '\0'
    */

    int i;
    for (i = 0; bStr[i] != '\0'; i++);

    if (i < 21 || (i == 25 && bStr[i - 1] != 10))
        return WRONG_NAME;
    else
    {
        memcpy(cardData->cardHolderName, &bStr[0], i-1);
        cardData->cardHolderName[i-1] = '\0';
        return OK;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    printf("Enter card expiry date: ");
    char bStr[7];
    fgets(bStr, 7, stdin);        
    if (!strchr(bStr, '\n'))                 //remove extra characters from fgets
        while (fgetc(stdin) != '\n');

    int i;
    for (i = 0; bStr[i] != 0; i++);

    if (i <= 5 || bStr[i - 1] != 10 || bStr[2] != '/')
        return WRONG_EXP_DATE;
    else if (bStr[0] < 48 || bStr[0] > 49 || bStr[1] < 48 || bStr[1] > 57 || bStr[3] < 48 
        || bStr[3] > 57 || bStr[4] < 48 || bStr[4] > 57 || (bStr[0] == 49 && bStr[1] > 50) 
        || (bStr[0] == 48 && bStr[1] ==48))
        return WRONG_EXP_DATE;    
    else
    {
        int u;
        for (u = 0; u < 5; u++)
            cardData->cardExpirationDate[u] = bStr[u];
        cardData->cardExpirationDate[u] = 0;
        return OK;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    char bStr[21];
    printf("Enter Card Pan: ");
    fgets(bStr, 21, stdin);
    if (!strchr(bStr, '\n'))                 //remove extra characters from fgets
        while (fgetc(stdin) != '\n');

    int i;
    for (i = 0; bStr[i] != '\0'; i++)
    {
        if( !( bStr[i] == 10 || isdigit(bStr[i]) || isalpha(bStr[i]) )  )
            return WRONG_PAN;
    }

    if (i < 17 || (i == 20 && bStr[i - 1] != 10))
        return WRONG_PAN;
 
    else
    {
        memcpy(cardData->primaryAccountNumber, &bStr[0], i - 1);
        cardData->primaryAccountNumber[i - 1] = '\0';
        return OK;
    }
}
