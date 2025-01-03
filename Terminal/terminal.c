#include <stdio.h>
#include "terminal.h"

extern data_of_user;
ST_terminalData_t terminalData_of_user;


//===========This function will ask for the transaction date and store it in terminal data.==========================
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t i = 0, size = 0;
	while ((termData->transactionDate[i]) != '\0')
	{
		size++;
		i++;
	}

	if ((size == 10) && ((termData->transactionDate[2]) == '/') && ((termData->transactionDate[5]) == '/')) return TERMINAL_OK;
	else return WRONG_DATE;
}

void getTransactionDateTest(void) //=====test function=========
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: getTransactionDate");
	while (1)
	{
		caseNumber++;
		printf("Enter the transaction date by using this format DD/MM/YYYY: \n");
		gets(terminalData_of_user.transactionDate);

		if (getTransactionDate(&terminalData_of_user) == TERMINAL_OK)
		{
			printf("Test Case: %d  \n", caseNumber);
			printf("Input Data: %s\n", terminalData_of_user.transactionDate);
			puts("Actual Result: TERMINAL_OK\n");
			break;
		}
		else
		{
			printf("Test Case :%d  \n", caseNumber);
			printf("Input Data: %s\n", terminalData_of_user.transactionDate);
			puts("Actual Result: WRONG_EXP_DATE\n");
		}

	}

}



//======================This function compares the card expiry date with the transaction date.==================

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (cardData->cardExpirationDate[3] < termData->transactionDate[8])
	{
		return EXPIRED_CARD;
	}
	else if (cardData->cardExpirationDate[3] == termData->transactionDate[8])
	{
			if (cardData->cardExpirationDate[4] < termData->transactionDate[9])
			{
				return EXPIRED_CARD;
			}
			else return TERMINAL_OK; 
	}

	else return TERMINAL_OK; 
}

void isCardExpriedTest(void)   //=====test function=========
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: isCardExpired");

	caseNumber++;
	if (isCardExpired(&data_of_user, &terminalData_of_user) == TERMINAL_OK)
	{
		printf("Test Case :%d   \n", caseNumber);
		puts("Actual Result: TERMINAL_OK\n");

	}
	else
	{
		printf("Test Case :%d   \n", caseNumber);
		puts("Actual Result: EXPIRED_CARD\n");
	}



}


//===========This function asks for the transaction amount and saves it into terminal data.========

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

	if ((termData->transAmount) <= 0) return INVALID_AMOUNT;
	else return TERMINAL_OK; 
}

void getTransactionAmountTest(void)  //=====test function=========
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: getTransactionAmount");
	while (1)
	{
		caseNumber++;
		printf("Enter the transaction amount: \n");
		scanf_s("%f", &terminalData_of_user.transAmount);

		if (getTransactionAmount(&terminalData_of_user) == TERMINAL_OK)
		{
			printf("Test Case:%d   \n", caseNumber);
			printf("Input Data: %f\n", terminalData_of_user.transAmount);
			puts("Actual Result: TERMINAL_OK\n");
			break;

		}
		else
		{
			printf("Test Case :%d   \n", caseNumber);
			printf("Input Data: %f\n", terminalData_of_user.transAmount);
			puts("Actual Result: INVALID_AMOUNT\n");
		}

	}

}


//================This function takes the maximum allowed amount and stores it into terminal data.================
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}

void setMaxAmountTest(void) //=======test function======
{
	uint8_t caseNumber = 0;
	float maxAmount = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: setMaxAmount");
	while (1)
	{
		caseNumber++;
		printf("Enter the  max allowed amount: \n");
		scanf_s(" %f", &maxAmount);
		if (setMaxAmount(&terminalData_of_user, maxAmount) == TERMINAL_OK)
		{
			printf("Test Case :%d  \n", caseNumber);
			printf("Input Data: %f\n", maxAmount);
			puts("Actual Result: TERMINAL_OK\n");
			break;
		}
		else
		{
			printf("Test Case :%d  \n", caseNumber);
			printf("Input Data: %f\n", maxAmount);
			puts("Actual Result: INVALID_MAX_AMOUNT\n");
		}
	}

}




//===========This function compares the transaction amount with the terminal max allowed amount.============
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	
	if ((termData->transAmount) > (termData->maxTransAmount)) return  EXCEED_MAX_AMOUNT;
	else return TERMINAL_OK;
}

void isBelowMaxAmountTest(void) //=======test function======
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: isBelowMaxAmount");
	

	caseNumber++;
	
	if (isBelowMaxAmount(&terminalData_of_user) == TERMINAL_OK)
	{
		printf("Test Case:%d  \n", caseNumber);
		puts("Actual Result: TERMINAL_OK\n");
	}
	else
	{
		printf("Test Case :%d   \n", caseNumber);
		puts("Actual Result: EXCEED_MAX_AMOUNT\n");
	}


}



