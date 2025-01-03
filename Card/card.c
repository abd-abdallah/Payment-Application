#include"card.h"
#include<stdio.h>

ST_cardData_t data_of_user;

//===========This function will ask for the cardholder's name and store it into card data.=======
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t i = 0, size = 0;
	while ((cardData->cardHolderName[i]) != '\0')
	{
		size++;
		i++;
	}
	if ((size >= 20) && (size <= 24)) return CARD_OK;
	else return WRONG_NAME;
}

void getCardHolderNameTest(void)//=====test function ======
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: getCardHolderName");
	while (1)
	{
		caseNumber++;
		printf("Enter your name as in your card: \n");
		gets(data_of_user.cardHolderName);

		if (getCardHolderName(&data_of_user) == CARD_OK)
		{
			printf("\nTest caseNumber :%d  \n", caseNumber);
			printf("Input Data: %s\n", data_of_user.cardHolderName);
			puts("Actual Result: CARD_OK\n");
			break;
		}
		else
		{
			printf("\nTest caseNumber: %d\n", caseNumber);
			printf("Input Data: %s\n", data_of_user.cardHolderName);
			puts("Actual Result: WRONG_NAME\n");
		}

	}
}


//=========This function will ask for the card expiry date and store it in card data.================
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t i = 0, size = 0;
	while ((cardData->cardExpirationDate[i]) != '\0')
	{
		size++;
		i++;
	}

	if ((size == 5) && ((cardData->cardExpirationDate[2]) == '/')) return CARD_OK;
	else return WRONG_EXP_DATE;
}

void getCardExpiryDateTest(void)  //test function
{
	static uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: getCardExpiryDate");
	while (1)
	{
		caseNumber++;
		printf("Enter your Card Expiry Date: \n");
		gets(data_of_user.cardExpirationDate);
		
		if (getCardExpiryDate(&data_of_user) == CARD_OK)
		{
			printf("Test caseNumber: %d  \n", caseNumber);
			printf("Input Data: %s\n", data_of_user.cardExpirationDate);
			puts("Actual Result: CARD_OK\n");
			break;
		}
		else
		{
			printf("Test caseNumber :%d \n", caseNumber);
			printf("Input Data: %s\n", data_of_user.cardExpirationDate);
			puts("Actual Result: WRONG_EXP_DATE\n");
		}

	}

}

//==========his function will ask for the card's Primary Account Number and store it in card data.============
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t i = 0, size = 0;
	while ((cardData->primaryAccountNumber[i]) != '\0')
	{
		size++;
		i++;
	}

	if ((size >= 16) && (size <= 19)) return CARD_OK;
	else return WRONG_PAN;
}

void getCardPANTest(void) //====test function=======
{
	uint8_t caseNumber = 0;

	puts("Tester Name: Abdelrahman Abdallah");
	puts("Function Name: getCardPAN");
	while (1)
	{
		caseNumber++;
		printf("Enter The card's Primary Account Number: \n");
		gets(data_of_user.primaryAccountNumber);
		if (getCardPAN(&data_of_user) == CARD_OK)
		{
			printf("Test caseNumber: %d \n", caseNumber);
			printf("Input Data: %s\n", data_of_user.primaryAccountNumber);
			puts("Actual Result: CARD_OK\n");
			break;
		}
		else
		{
			printf("Test caseNumber: %d \n", caseNumber);
			printf("Input Data: %s\n", data_of_user.primaryAccountNumber);
			puts("Actual Result: WRONG_PAN\n");
		}

	}

}


