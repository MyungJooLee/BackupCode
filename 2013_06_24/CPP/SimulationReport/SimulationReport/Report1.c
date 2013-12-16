#include <stdio.h>
#include <stdlib.h>

#define	CustomerNo	1000
#define ServiceUserNoPerServer	1		// 서버가 동시에 처리할 수 있는 고객의 수

double  interArrivalTime[CustomerNo];	// 도착간격
double  serviceTime[CustomerNo];		// 서비스시간
double  arrivalTime[CustomerNo];		// 도착시간
double  serviceStartTime[CustomerNo];	// 서비스 시작시간
double  waitingTime[CustomerNo];		// 대기시간
double  endTime[CustomerNo];			// 서비스 종료시간

double ServerJobEndTime[ServiceUserNoPerServer];


int findFastEndServer()
{
	int i=0;
	int ServerNo = -1;		// 가장 먼저 끝나는 서버의 작업 번호!
	double fastEndTime = 1000000000000;

	for(i=0 ;i<ServiceUserNoPerServer; i++)				// 가장 먼저 끝나는 창구를 찾아요!
	{
		if(fastEndTime > ServerJobEndTime[i])
		{
			ServerNo = i;
			fastEndTime = ServerJobEndTime[i];
		}
	}

	return ServerNo;
}

void main(void)
{
	int i=0, j=0;						// 반복문 사용을 위한 변수
	FILE* fpinterArrivalTime = NULL;	// interArrivalTime 파일을 읽어오기 위한 파일 포인터
	FILE* fpserviceTime = NULL;			// serviceTime 파일을 읽어 오기 위한 파일 포인터
	double tempTime = 0;				// 시작 시간을 구하기위해서 임시로 시간을 누적시키는 변수 입니다.
	int ServerNo = 0;					// 현재 고객이 사용 가능한 서버 번호!
	double AllJobEndTime = 0;			// 모든 작업이 끝난시간;
	double AverageWaitingTime = 0;		// 평균 대기시간;
	double ServerUtil = 0;				// 서버 활용도
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 용어 해석이 명확하지 않아서... 다음과 같은 가정을 하고 시작하였습니다.
	// 1. interArrivalTime.TXT 파일에 있는 시간 간격으로 고객이 도착한다.
	// 2. 고객은 서버가 사용중이면, 서버를 사용 할 수 있을 때 까지 대기한 후에 serviceTime.txt 파일에 있는 만큼 서비스를 이용하고 끝났다.
	//		-> 어닐 수도 있을 것 같아서 주석으로 serviceTime.txt에 대기시간을 포함한 경우를 해 놓았습니다.
	// 3. 서버는 동시에 N명만 서비스 할 수 있다. => Define으로 정의하여 변경 하면서 시물레이션 할 수 있게 하였습니다.
	//		-> 은행처럼 창구가 있고 번호표를 뽑아서 각 창구에서 처리하는 형태!
	// 4. 서버는 무조건 먼저 도착한 사람을 먼저 처리한다.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 파일에서 기본 데이터 불러오기
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	fpinterArrivalTime = fopen("InterArrivalTime.txt", "rt");	//interArrivalTime 파일을 사용하기 위해서 엽니다. 
	if(fpinterArrivalTime == NULL)								// 못열었을 경우 문제가 있는 것이기 때문에, 에러메세지를 표시하고 종료합니다.
	{
		printf("interArrivalTime 파일을 못열었어요.. ㅠ.ㅠ\n");
		return;
	}
	fpserviceTime = fopen("serviceTime.txt", "rt");			//serviceTime 파일을 사용하기 위해서 엽니다. 
	if(fpserviceTime == NULL)								// 못열었을 경우 문제가 있는 것이기 때문에, 에러메세지를 표시하고 종료합니다.
	{
		printf("serviceTime 파일을 못열었어요.. ㅠ.ㅠ\n");
		return;
	}
	for(i=0; i<CustomerNo; i++)									// 각 파일별로 1000개의 숫자일 읽어서 변수에 저장 합니다.
	{
		fscanf(fpinterArrivalTime, "%lf\n", &interArrivalTime[i]);
		fscanf(fpserviceTime, "%lf\n", &serviceTime[i]);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 시작시간, 대기시간 및 종료 시간 구하기 (시물레이션)
	//					- 만약, serviceTime.txt 안의 시간이 대기시간을 포함 하지 않는 경우
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tempTime = 0;
	for(i=0; i<CustomerNo; i++)								// 모든 고객에 대해서 시물레이션 진행
	{		
		tempTime += interArrivalTime[i];	// (파일에 있는 것은 도착시간의 간격 이므로..) 각 고객의 실제 도착 시간을 계산하여 저장합니다.
		arrivalTime[i] = tempTime;

		ServerNo = findFastEndServer();		// 가장 먼저 끝나는 (창구)를 찾아요~

		if(ServerJobEndTime[ServerNo] <= arrivalTime[i])	// 도착 시간보다 창구의 작업이 먼저 끝나 있으면, 비어있는 거라 판단합니다.
		{
			serviceStartTime[i] = arrivalTime[i];						// 창구가 비어있으면 도착하자 마자 시작			
			endTime[i] = serviceStartTime[i] + serviceTime[i];			// 시작시간에 서비스 시간을 더하면 끝.
			waitingTime[i] = 0;											// 대기시간은 0!
			ServerJobEndTime[ServerNo] = endTime[i];					// 서버는 내일을 처리 할꺼니까, 해당 창구의 일이 언제 끝나는지를 저장
		}
		else												// 도착했는데 창구의 작업이 아직 안끝나있으면 끝날때 까지 기다렸다가 작업을 해야죠~~
		{
			serviceStartTime[i] = ServerJobEndTime[ServerNo];			// 창구가 비어 있지 않으니까, 기다렸다가 시작해야죠!
			endTime[i] = serviceStartTime[i] + serviceTime[i];			// 시작시간에 서비스 시간을 더하면 끝.
			waitingTime[i] = serviceStartTime[i] - arrivalTime[i];		// 대기시간은 시작시간 - 도착시간!
			ServerJobEndTime[ServerNo] = endTime[i];					// 서버는 내일을 처리 할꺼니까, 해당 창구의 일이 언제 끝나는지를 저장
		}
	}
	
/*
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 시작시간, 대기시간 및 종료 시간 구하기 (시물레이션)
	//					- 만약, serviceTime.txt 안의 시간이 대기시간을 포함 하는 경우
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tempTime = 0;
	for(i=0; i<CustomerNo; i++)								// 모든 고객에 대해서 시물레이션 진행
	{		
		tempTime += interArrivalTime[i];	// (파일에 있는 것은 도착시간의 간격 이므로..) 각 고객의 실제 도착 시간을 계산하여 저장합니다.
		arrivalTime[i] = tempTime;

		
			serviceStartTime[i] = arrivalTime[i];						// 이건 알 방법이 없으므로 도착시간으로 지정	
			endTime[i] = serviceStartTime[i] + serviceTime[i];			// 대기시간이 포함되어 있으면 그냥 도착시간 + 서비스 시간 하면 종료시간
			waitingTime[i] = 0;											// 대기시간은 0!
			ServerJobEndTime[ServerNo] = endTime[i];					// 서버는 내일을 처리 할꺼니까, 해당 창구의 일이 언제 끝나는지를 저장
		
	}
*/	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 평균 대기 시간 및 서버 활용도 계산을 위해서 가장 늦게 끝난 작업이 언제 끝났는지 찾기	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(i=0; i<CustomerNo; i++)		
	{
		if(AllJobEndTime < endTime[i])
			AllJobEndTime = endTime[i];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 평균 대기 시간 및 서버 활용도 계산	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(i=0; i<CustomerNo; i++)								// 모든 고객에 대해서 시물레이션 진행
	{
		AverageWaitingTime += waitingTime[i];				// 일단 대기시간을 다 더합니다.
		ServerUtil += serviceTime[i];						// 모든 서비스 시간을 더합니다.
	}
	AverageWaitingTime = AverageWaitingTime/CustomerNo;	    // 대기시간의 평균을 구합니다.
	ServerUtil = ServerUtil/(AllJobEndTime*ServiceUserNoPerServer) * 100.0;	// 모든 서비스시간 나누기 전체작업시간*동시처리수 (백분율)



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 출력!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("평균대기시간 : %10.4lf \n", AverageWaitingTime);	 // 총 10자리출력, 소수점이하 4자리 출력
	printf("서버효율계산 : %10.4lf%% \n", ServerUtil);
}

