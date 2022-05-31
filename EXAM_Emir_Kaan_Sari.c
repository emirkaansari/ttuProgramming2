#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EXAM_Emir_Kaan_Sari.h"

int main(void)
{
	energyProfile *pData = NULL;
	char fileName[] = INPUT_FILE;
	int totalProfiles = ReadFromFile(&pData, fileName);
	int menu;
	while (1)
    {
        menu = GetInput();
        switch (menu)
        {
            case 0:
                puts("Case 0: Exiting...");
                exit(EXIT_SUCCESS);
                break;
            case 1:
				ShowAllData(pData, totalProfiles);
                break;
            case 2:
                FindImporterExporter(pData, totalProfiles);
                break;
            case 3:
                FindCountry(pData, totalProfiles);
                break;
            case 4:
                DisplayOverallStat(pData, totalProfiles);
                break;
            default:
                puts("You should not be here.. this is sabotage!");
                break;
        }
    }
    free(pData);
	return EXIT_SUCCESS;
}
int ReadFromFile(energyProfile **pData, char *fileName)
{
	int count;
	char name[BUFFER_LEN];
	float consumption;
	int coal;
	int gas;
	int wind;
	int solar;
	int hydro;
	
	energyProfile *pArr = NULL;
	energyProfile *pTemp = NULL;
	
	FILE *fp = fopen(fileName, "r");
	
	if (fp == NULL)
    {
        perror("Error opening input file:");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    count = 0;
    
    while (fscanf(fp, "%s %f %d %d %d %d %d", name, &consumption, &coal, &gas, &wind, &solar, &hydro) == 7)
	{
		pTemp = realloc(pArr, sizeof(energyProfile)*(count + 1));
		
		if (pTemp == NULL)
		{
			free(pTemp);
			free(pArr);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		
		pArr = pTemp;
		(pArr + count)->name = strdup(name);
		if ((pArr + count)->name == NULL)
		{
			fclose(fp);
			free(pTemp);
			free(pArr);
		}
		(pArr + count)->consumption = consumption;
		(pArr + count)->coal = coal;
		(pArr + count)->gas = gas;
		(pArr + count)->wind = wind;
		(pArr + count)->solar = solar;
		(pArr + count)->hydro = hydro;
		count++;
	}
	*pData = pArr;
	fclose(fp);
	
	return count;
}
int GetInput(void)
{
    int input;
    puts("");
    while (1)
    {
        puts("Make your selection. Press the corresponding number and the enter key");
        puts("0 - Exit.");
        puts("1 - Show all the data.");
        puts("2 - Group all the countries.");
        puts("3 - Find Country");
        puts("4 - Display Overall Statistics.");
        printf("> ");
        scanf("%d", &input);
        puts("");
        if (input <= 4 && input >= 0)
            return input;
        printf("Input error!\n\n");
		return 0;
    }
}
void ShowAllData(energyProfile *pData, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%10s|%6.2f|%-7d|%-7d|%-7d|%-7d|%-7d\n",(pData+i)->name,(pData+i)->consumption,
			(pData+i)->coal,(pData+i)->gas,
				(pData+i)->wind,(pData+i)->solar,(pData+i)->hydro);
	}
	
}
void FindImporterExporter(energyProfile *pData, int len)
{
	int i;
	float temp;
	printf("Exporters:\n");
	for(i = 0;i < len; i++)
	{
		temp = (pData+i)->coal + (pData+i)->gas + 
			(pData+i)->wind + (pData+i)->solar + (pData+i)->hydro;
		if(temp <= ((pData+i)->consumption) * 1000) //mwh to gwh
		{
			printf("%s Net Export %.0f MWh\n",(pData+i)->name,((pData+i)->consumption)*1000 -temp);
		}
	}
	printf("Importers:\n");
	for(i = 0; i < len; i++)
	{
		temp = (pData+i)->coal + (pData+i)->gas + (pData+i)->wind + (pData+i)->solar + (pData+i)->hydro;
		if(temp > ((pData+i)->consumption)*1000)
		{
			printf("%s Net Import %.0f MWh\n",(pData+i)->name ,temp - ((pData+i)->consumption)*1000 );
		}
	}
}
void FindCountry(energyProfile *pData, int len)
{
	int i;
	char Input[BUFFER_LEN];
	printf("Please input country name:");
	scanf("%s", Input);
	for(i = 0; i<len ; i++)
	{
		if(strcmp(Input,(pData + i)->name) == 0)
		{
			break;
		}
	}
	if( i < len)
	{
		DisplayTwoMostUsed(*( pData + i));
	}
	else
	{
		printf("Unable to find\n");
	}
}
void DisplayTwoMostUsed(energyProfile profile)
{
	int mostUsed, secondMostUsed;
	char mostUsed_type[BUFFER_LEN],secondMostUsed_type[BUFFER_LEN];
	mostUsed = profile.coal;
	strcpy(mostUsed_type,"Coal");
	
	if( profile.gas > mostUsed)
	{
		mostUsed = profile.gas;
		strcpy(mostUsed_type,"Gas");
	}
	if( profile.wind > mostUsed)
	{
		mostUsed = profile.wind;
		strcpy(mostUsed_type,"Wind");
	}
	if( profile.solar > mostUsed)
	{
		mostUsed = profile.solar;
		strcpy(mostUsed_type,"Solar");
	}
	if( profile.hydro > mostUsed)
	{
		mostUsed = profile.hydro;
		strcpy(mostUsed_type,"Hydro");
	}

	secondMostUsed = 0;
	if( profile.coal > secondMostUsed && profile.coal != mostUsed )
	{
		secondMostUsed = profile.coal;
		strcpy(secondMostUsed_type,"Coal");
	}
	if( profile.gas > secondMostUsed && profile.gas != mostUsed )
	{
		secondMostUsed = profile.gas;
		strcpy(secondMostUsed_type,"Gas");
	}
	if( profile.wind > secondMostUsed && profile.wind != mostUsed )
	{
		secondMostUsed = profile.wind;
		strcpy(secondMostUsed_type,"Wind");
	}
	if( profile.solar > secondMostUsed && profile.solar != mostUsed )
	{
		secondMostUsed = profile.solar;
		strcpy(secondMostUsed_type,"Solar");
	}
	if( profile.hydro > secondMostUsed && profile.hydro != mostUsed )
	{
		secondMostUsed = profile.hydro;
		strcpy(secondMostUsed_type,"Hydro");
	}
	printf("Most Used Energy: %s  %dMWh  Second Most Used Energy : %s  %dMWh\n"
		,mostUsed_type,mostUsed,secondMostUsed_type,secondMostUsed);
}
void DisplayOverallStat(energyProfile *pData,int len)
{
	int coal_total = 0;
	int gas_total = 0;
	int wind_total = 0;
	int solar_total = 0;
	int hydro_total = 0;
	int energy_total , i;
	
	for(i = 0; i<len ; i++)
	{
		coal_total += (pData+i)->coal;
		gas_total += (pData+i)->gas;
		wind_total += (pData+i)->wind;
		solar_total += (pData+i)->solar;
		hydro_total += (pData+i)->hydro;
	}
	
	energy_total = coal_total + gas_total + wind_total + solar_total + hydro_total;
	printf("Coal: %.2f %%\nGas: %.2f %%\nWind: %.2f %%\nSolar: %.2f %%\nHydro: %.2f %%\n",coal_total*100.0/energy_total,
		gas_total*100.0/energy_total,wind_total*100.0/energy_total,
			solar_total*100.0/energy_total,hydro_total*100.0/energy_total);
	printf("Fossil fuels: %.2f %%\nRenewables: %.2f %%\n",(coal_total + gas_total)*100.0/energy_total,
		(wind_total + solar_total + hydro_total)*100.0/energy_total);
}
