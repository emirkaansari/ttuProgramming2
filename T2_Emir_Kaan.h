#ifndef T2_HEADER
#define T2_HEADER
#define EMPLOYEES_INPUT_FILE "01_employees.txt"
#define LOGS_INPUT_FILE "01_times.txt"
#define BASE_PAY 600
#define BUFFER_LEN 250
typedef struct
{
	int empCode;
	char *name;
	char *position;
	float wage;
	int totalPay; 
	int totalHours;
}employee;
typedef struct
{
	int entry_ID;
	int empCode;
	int hours;
	int day;
	int month;
	int year;
}log;
int ReadEmployees(employee **pData, char *fileName);
int ReadLogs(log **pData, char *fileName);
void CalculatePayment(employee *pEmp, int empLen, log *pLog, int logLen);
#endif //T2_HEADER

