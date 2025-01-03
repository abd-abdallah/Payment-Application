#include "server.h"
#include <string.h>

#define NULL  ((void*)0)

extern ST_cardData_t data_of_user;
extern ST_terminalData_t terminalData_of_user;




ST_accountsDB_t accountsDB[255] = { \
		{1000.0, RUNNING, "5369374605987451"},\
		{1500.0, RUNNING, "9632374605436851"},\
		{2000.0, BLOCKED, "5369374605436851"},\
		{500.0,  RUNNING, "6394374605556845"},\
		{70000.0,BLOCKED, "9569372205436555"},\
		{6500.0, RUNNING, "4555374441436851"},\
		{89000.0,BLOCKED, "5459379631436452"},\
		{2300.0, RUNNING, "9869374698736851"},\
		{20400.0,BLOCKED, "9876574963236854"},\
		{14170.0,RUNNING, "9632379865436895"} };

ST_accountsDB_t* reference_to_account = NULL;


ST_transaction arr[255] = { 0 };


ST_transaction* transDataB =arr;

//=================This function will take card data and validate if the account related to this card exists or not.=====================
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t i;
	for (i = 0; i < 10; i++)
	{
	
		if(strcmp(cardData->primaryAccountNumber,accountRefrence->primaryAccountNumber)==0)
		{
			reference_to_account = accountRefrence;
			return SERVER_OK;
		}
		accountRefrence++;
	}

	reference_to_account = NULL;
	return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)  //=====test function=========
{
	uint8_t caseNumber = 0;


	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: isValidAccount");

	caseNumber++;
		
	if (isValidAccount(&data_of_user, accountsDB)== SERVER_OK)
	{
		printf("Test Case %d:  \n", caseNumber);
		puts("Actual Result: SERVER_OK\n");

	}
	else
	{
		printf("Test Case %d:  \n", caseNumber);
		puts("Actual Result: ACCOUNT_NOT_FOUND\n");
	}

}
//============This function takes a reference to the account into the database and verifies if it is blocked or not.============
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
	{
		return SERVER_OK;
	}

	else
	{
		return BLOCKED_ACCOUNT;
	}
}

void isBlockedAccountTest(void) //=====test function=========
{
	uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: isBlockedAccoun");

	caseNumber++;
	if (isBlockedAccount(reference_to_account) == SERVER_OK)
	{
		printf("Test Case %d:  \n", caseNumber);
		puts("Actual Result: SERVER_OK\n");

	}
	else
	{
		printf("Test Case %d:  \n", caseNumber);
		puts("Actual Result: BLOCKED_ACCOUNT\n");
	}

}

//=============This function will take terminal data and a reference to the account in the database and check if the account================
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if ((termData->transAmount) < (accountRefrence->balance))
	{
		
		accountRefrence->balance -= termData->transAmount;
		return SERVER_OK;

	}
	else
	{
		return LOW_BALANCE;
	}

}

void isAmountAvailableTest(void) //=====test function=========
{
	uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name:isAmountAvailable");

	caseNumber++;
	if (isAmountAvailable(&terminalData_of_user, reference_to_account) == SERVER_OK)
	{
		printf("Test Case: %d  \n", caseNumber);
		puts("Actual Result: SERVER_OK\n");

	}
	else
	{
		printf("Test Case : %d \n", caseNumber);
		puts("Actual Result: LOW_BALANCE\n");
	}

}






//================This function will take all transaction data and validate its data, it contains all server logic.==================

EN_serverError_t saveTransaction(ST_transaction* transData)
{
	static uint8_t sequence = 1;
	if (sequence < 255)
	{
		transData->cardHolderData = data_of_user;
		transData->terminalData = terminalData_of_user;
		transData->transactionSequenceNumber = sequence;

		sequence++;
		transData++;
		return APPROVED;
	}
	else
	{
		return INTERNAL_SERVER_ERROR;
	}
	
	
}

void saveTransactionTest(void)
{

	uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: saveTransaction");

	caseNumber++;
	if (saveTransaction(transDataB)==APPROVED)
	{
		printf("Test Case: %d  \n", caseNumber);
		puts("Actual Result: APPROVED\n");

	}
	else
	{
		printf("Test Case : %d \n", caseNumber);
		puts("Actual Result:INTERNAL_SERVER_ERROR\n");
	}

}

//====================This function prints all transactions found in the transactions DB.========================
void listSavedTransactions(void)
{
	puts("#########################");
	printf("Transaction Sequence Number : %d\n", transDataB->transactionSequenceNumber);
	printf("Transaction Date :%s\n ", transDataB->terminalData.transactionDate);
	printf("Transaction Amount: %f\n", transDataB->terminalData.transAmount);
	printf("Transaction State : APPROVED\n");
	printf("Terminal Max Amount : %f\n", transDataB->terminalData.maxTransAmount);
	printf("The remaining balance : %f\n", reference_to_account->balance);
	printf("Cardholder Name : %s\n", transDataB->cardHolderData.cardHolderName);
	printf("PAN: %s\n", transDataB->cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date : %s\n", transDataB->cardHolderData.cardExpirationDate);
	puts("#########################");
}
