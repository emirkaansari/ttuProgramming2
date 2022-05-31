#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T2_Emir_Kaan.h"
int main (void)
{
	employee *employees = NULL;
	log *logs = NULL;
	char employeesFileName[] = EMPLOYEES_INPUT_FILE;
	int empLen = ReadEmployees(&employees, employeesFileName);
	char logsFileName[] = LOGS_INPUT_FILE;
	int logLen = ReadLogs(&logs,logsFileName);
	CalculatePayment(employees, empLen, logs, logLen);
	free(employees);
	free(logs);
	return EXIT_SUCCESS;
}
int ReadEmployees(employee **pData, char *fileName)
{
	int count;
	int empCode;
	char name[BUFFER_LEN];
	char position[BUFFER_LEN];
	float wage;
	
	employee *pArr = NULL;
	employee *pTemp = NULL;
	
	FILE *fp = fopen(fileName, "r");
	
	if (fp == NULL)
    {
        perror("Error opening input file:");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    count = 0;
    while (fscanf(fp, "%d %s %s %f", &empCode, name, position, &wage) == 4)
    {
		pTemp = realloc(pArr, sizeof(employee)*(count + 1));
		
		if (pTemp == NULL)
		{
			free(pTemp);
			free(pArr);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		pArr = pTemp;
		
		(pArr + count)->empCode = empCode;
		(pArr + count)->name = strdup(name);
		if ((pArr + count)->name == NULL)
		{
			fclose(fp);
			free(pTemp);
			free(pArr);
		}
		(pArr + count)->position = strdup(position);
		if ((pArr + count)->position == NULL)
		{
			fclose(fp);
			free(pTemp);
			free(pArr);
		}
		(pArr + count)->wage = wage;
		count++;
	}
	*pData = pArr;
	fclose(fp);
	return count;
}
int ReadLogs(log **pData, char *fileName)
{
	int count;
	int entry_ID;
	int empCode;
	int day;
	int month;
	int year;
	int hours;
	
	log *pArr = NULL;
	log *pTemp = NULL;
	
	FILE *fp = fopen(fileName, "r");
	
	if (fp == NULL)
    {
        perror("Error opening input file:");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    count = 0;
    while (fscanf(fp, "%d %d %d.%d.%d %d ", &entry_ID, &empCode,&day,&month,&year, &hours) == 6)
    {
		pTemp = realloc(pArr, sizeof(log)*(count + 1));
		
		if (pTemp == NULL)
		{
			free(pTemp);
			free(pArr);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		pArr = pTemp;
		
		(pArr + count)->entry_ID = entry_ID;
		(pArr + count)->empCode = empCode;
		(pArr + count)->hours = hours;
		(pArr + count)->day = day;
		(pArr + count)->month = month;
		(pArr + count)->year = year;
		count++;
	}
	*pData = pArr;
	fclose(fp);
	return count;
	
}
void CalculatePayment(employee *pEmp, int empLen, log *pLog, int logLen)
{
	int i, j;

	for (i = 0; i < empLen; i++)
	{
		//printf("\n%d %s %s %f\n", (pEmp + i)->empCode,
			//(pEmp + i)->name, (pEmp + i)->position, (pEmp + i)->wage);
		(pEmp + i)->totalHours = 0;
		(pEmp + i)->totalPay = 0;
		for (j = 0; j < logLen; j++)
		{
			if((pEmp + i)->empCode == (pLog + j)->empCode)
			{
				 (pEmp + i)->totalHours += (pLog + j)->hours;
				 //printf("%d %d %d.%d.%d %d\n", (pLog + j)->entry_ID,
					//(pLog + j)->empCode, (pLog + j)->day,
						//(pLog + j)->month, (pLog + j)->year, 
							//(pLog + j)->hours);
			}
		}
	}
	for (i = 0; i < empLen; i++)
	{
		if (strcmp((pEmp + i)->position, "Intern") != 0 && (pEmp + i)->totalHours > 100)
		{
			(pEmp + i)->totalPay = (pEmp + i)->totalHours * (pEmp + i)->wage + BASE_PAY;
				printf("\n%02d %s %s %.2f %d Total Pay: %d\n", (pEmp + i)->empCode,
					(pEmp + i)->name, (pEmp + i)->position, (pEmp + i)->wage, (pEmp + i)->totalHours, (pEmp + i)->totalPay);
			printf("Base pay is applied!\n");
		}
		else
		{
			(pEmp + i)->totalPay = (pEmp + i)->totalHours * (pEmp + i)->wage;
			printf("\n%02d %s %s %.2f %d Total Pay: %d\n", (pEmp + i)->empCode,
				(pEmp + i)->name, (pEmp + i)->position, (pEmp + i)->wage, (pEmp + i)->totalHours, (pEmp + i)->totalPay);
		}
			
	}
}

