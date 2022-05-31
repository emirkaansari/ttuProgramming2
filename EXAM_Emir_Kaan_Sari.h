#ifndef EXAM_HEADER
#define EXAM_HEADER
#define INPUT_FILE "energy.txt"
#define BUFFER_LEN 150
typedef struct energyProfile
{
	char *name;
	float consumption;
	int coal;
	int gas;
	int wind;
	int solar;
	int hydro;
}energyProfile;
int ReadFromFile(energyProfile **pData, char *fileName);
int GetInput(void);
void ShowAllData(energyProfile *pData, int len);
void FindImporterExporter(energyProfile *pData, int len);
void FindCountry(energyProfile *pData, int len);
void DisplayTwoMostUsed(energyProfile profile);
void DisplayOverallStat(energyProfile *pData, int len);
#endif //EXAM_HEADER
