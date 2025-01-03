#include "app.h"

//======================== Cord Module. ======================================
/* structure for hold Card Data */
extern ST_cardData_t data_of_user;

/* Card Module Functions  */
extern EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
extern EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
extern EN_cardError_t getCardPAN(ST_cardData_t* cardData);
//=============================================================================

//======================== Terminal Module. ======================================
/* structure for hold Terminal Data */
extern ST_terminalData_t terminalData_of_user;

float maxAmount = 0; // for max amount

/* Terminal Module Functions  */
extern EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
extern EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
extern EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
extern EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
extern EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
//=============================================================================

//======================== Server Module. ======================================
extern ST_accountsDB_t accountsDB[255];
extern ST_accountsDB_t* reference_to_account;
extern ST_transaction* transDataB;

extern EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
extern EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
extern EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);
extern EN_serverError_t saveTransaction(ST_transaction* transData);
extern void listSavedTransactions(void);
//==============================================================================



void appStart(void)
{
	uint8_t number_of_try = 0;
	while (1)
	{   /*Cord Module.*/
		/*This function will ask for the cardholder's name and store it into card data.*/
		
		while (number_of_try < 3)
		{
			puts("Enter your name as in your card: ");
			gets(data_of_user.cardHolderName);

			if (getCardHolderName(&data_of_user) != CARD_OK)
			{
				number_of_try++;
				puts("your name as in your card is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}

		if (number_of_try == 3) break;

		/*This function will ask for the card expiry date and store it in card data.*/
		while (number_of_try < 3)
		{
			puts("Enter your Card Expiry Date: ");
			gets(data_of_user.cardExpirationDate);

			if (getCardExpiryDate(&data_of_user) != CARD_OK)
			{
				number_of_try++;
				puts("your Card Expiry Date is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}

		if (number_of_try == 3) break;

		/*This function will ask for the card's Primary Account Number and store it in card data.*/
		while (number_of_try < 3)
		{
			printf("Enter The card's Primary Account Number: ");
			gets(data_of_user.primaryAccountNumber);
			if (getCardPAN(&data_of_user) != CARD_OK)
			{
				number_of_try++;
				puts("The card's Primary Account Number is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}
		if (number_of_try == 3) break;

		/*Terminal Module.*/
		/*This function will ask for the transaction date and store it in terminal data.*/
		while (number_of_try < 3)
		{
			printf("Enter the transaction date by using this format DD/MM/YYYY: ");
			gets(terminalData_of_user.transactionDate);

			if (getTransactionDate(&terminalData_of_user) != TERMINAL_OK)
			{
				number_of_try++;
				puts("The transaction date is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}
		if (number_of_try == 3) break;

		/*This function compares the card expiry date with the transaction date.*/
		if (isCardExpired(&data_of_user, &terminalData_of_user) != TERMINAL_OK)
		{
			puts("Declined Expired Card.\n");
			break;

		}

		/*This function asks for the transaction amount and saves it into terminal data.*/
		while (number_of_try < 3)
		{
			printf("Enter the transaction amount: ");
			scanf_s("%f", &terminalData_of_user.transAmount);

			if (getTransactionAmount(&terminalData_of_user) != TERMINAL_OK)
			{
				number_of_try++;
				puts("The the transaction amount is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}
		if (number_of_try == 3) break;

		/*This function takes the maximum allowed amount and stores it into terminal data.*/
		while (number_of_try < 3)
		{
			printf("Enter the  max allowed amount: ");
			scanf_s(" %f", &maxAmount);
			if (setMaxAmount(&terminalData_of_user, maxAmount) != TERMINAL_OK)
			{
				number_of_try++;
				puts("The max allowed amount is not correct.\n");

			}
			else
			{
				number_of_try = 0;
				break;
			}
		}
		if (number_of_try == 3) break;

		/*This function compares the transaction amount with the terminal max allowed amount.*/
		if (isBelowMaxAmount(&terminalData_of_user) != TERMINAL_OK)
		{
			puts("Declined Amount Exceeding Limit.\n");
			break;
		}

		/*Server Module*/
		/*This function will take card data and validate if the account related to this card exists or not.*/
		if (isValidAccount(&data_of_user, accountsDB) != SERVER_OK)
		{
			puts("Declined Invalid account.\n");
			break;
		}

		/*This function takes a reference to the account into the database and verifies if it is blocked or not.*/
		if (isBlockedAccount(reference_to_account) != SERVER_OK)
		{
			puts("Declined blocked account.\n");
			break;
		}

		/*This function will take terminal data and a reference to the account in the database and check if the account*/
		if (isAmountAvailable(&terminalData_of_user, reference_to_account) != SERVER_OK)
		{
			puts("Declined insuffecient funds.\n");
			break;
		}

		/*This function will store all transaction data in the transactions database.*/
		if (saveTransaction(transDataB) != APPROVED)
		{
			puts("INTERNAL_SERVER_ERROR.\n");
			break;

		}
		else
		{
			listSavedTransactions();  /*This function prints all transactions found in the transactions DB.*/
		}
		
	}

}