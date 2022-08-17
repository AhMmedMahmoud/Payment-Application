#include "Application/app.h"

int main()
{
    //  transactions' database is empty

    /* accounts' database  
    *        {1000, "100000020000003000"} , { 2000,"100000020000003001" } , { 3000,"100000020000003002" }
    */

    appStart();
    printAllTransactions();
    printAllAcounts();
    return 0;
}


// Tests

/* Test Data: Approved
        Holder Name               : ahmed mahomud mohamed  (21 characters)
        Expiry date               : 05/25                  (5 character in right format , after Transaction Date)
        Pan                       : 100000020000003002     (one of PANs stored in database)
        Transaction Date          : read from computer
        Max transaction Amount    : 5000                   (greater than 0)
        transaction Amount        : 2000                   (greater than 0,less than max amount,less than balance)
*/

/* Test Data: Exceed the maximum amount
        Holder Name               : ahmed mahomud mohamed   (21 characters)
        Expiry date               : 05/25                   (5 character in right format , after Transaction Date)
        Pan                       : 100000020000003002      (one of PANs stored in database)
        Transaction Date          : read from computer
        Max transaction Amount    : 5000                    (greater than 0)
        transaction Amount        : 6000                    (greater than max amount)
*/

/* Test Data: Insufficient fund
        Holder Name               : ahmed mahomud mohamed   (21 characters)
        Expiry date               : 05/25                   (5 character in right format, after Transaction Date)
        Pan                       : 100000020000003002      (one of PANs stored in database)
        Transaction Date          : read from computer
        Max transaction Amount    : 5000                    (greater than 0)
        transaction Amount        : 4000                    (less than max amount , greater than balance)
 */

 /* Test Data: Expired card
         Holder Name              : ahmed mahomud mohamed  (21 characters)
         Expiry date              : 05/17                  (5 character in right format , before Transaction Date)
         Pan                      : 100000020000003002     (one of PANs stored in database)
 */

/* Test Data: Invalid card
        Holder Name               : ahmed mahomud mohamed  (21 characters)
        Expiry date               : 05/25                  (5 character in right format , after Transaction Date)
        Pan                       : 100000020000003002     (not one of PANs stored in database)
        Transaction Date          : read from computer
        Max transaction Amount    : 5000                   (greater than 0)
        transaction Amount        : 2000                   (greater than 0,less than max amount,less than balance)
*/