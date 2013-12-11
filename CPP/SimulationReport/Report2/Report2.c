#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define	N	100
#define pi	3.141592


double  interArrivalTime[N];	// 도착간격
double  arrivalTime[N];		// 도착시간
double  endTime[N];			// 종료시간
double  responseTime[N];			// 응답시간
double  processTime[N];			// 실제 처리시간

double P1 = 0.99;				// 0.1초뒤에 반응할 확률
double P2 = 0.00999;			// 60초뒤에 반응할 확률
double P3 = 0.00001;			// 360초뒤에 반응할 확률

double response()				// 응답시간을 계산
{
	double p = (rand()%10001)/10000.0 ;
	
						// 난수를 생성하여 0~1 사이로 변경
	if(p < P1)			// 확률에 따라서 어떤 응답을 할 것인가를 결정	
	{
		// 0.1 뒤에 반응
		return 0.1;
	}
	else if(p < (P1+P2))
	{
		// 60초 뒤에 반응
		return 60.0;
	}
	else
	{
		// 360초 뒤에 반응
		return 360.0;
	}			
}

void main()
{
	int i=0, j=0;						// 반복문 사용을 위한 변수
	
	double tempTime = 0;
	double AllJobEndTime = 0;			// 모든 작업이 끝난시간;
	double AverageResponseTime = 0;		// 평균 응답시간;
	double ServerUtil = 0;				// 두뇌 활용도

	srand(time(NULL));					// Rand 함수를 잘쓰기 위해서 시간값을 seed로 설정합니다.

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 지수분포를 따르는 난수를 만들어서 자극 도착 시간을 생성하였습니다. (만드는 방법이 교수님이 원하시는거랑 맞는지 모르겠네요.)
	// 지수분포의 평균은 100으로 하였습니다. 
	// 총 자극의 개수는 100으로 define에 N으로 정의하였습니다.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(i=0; i<N; i++)
	{
		interArrivalTime[i] = (-1.0/100)*log(1-(rand()%10000)/10000.0);	// 지수분포 난수 생성, 람다는 100으로 설정
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 시작시간, 대기시간 및 종료 시간 구하기 (시물레이션)
	//					
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tempTime = 0;
	for(i=0; i<N; i++)								// 모든 자극에 대해서 시물레이션 진행
	{		
		tempTime += interArrivalTime[i];	// (자동으로 생성한것은 도착시간의 간격 이므로..) 각 고객의 실제 도착 시간을 계산하여 저장합니다.
		arrivalTime[i] = tempTime;

		if(i == 0)							// 첫 자극은 대기 없이 바로 처리
		{
			processTime[i] = response();
			endTime[i] = arrivalTime[i] + processTime[i];
			responseTime[i] = endTime[i] - arrivalTime[i];	// 응답시간은 처리 시간 - 도착시간
		}
		else
		{
			if(endTime[i-1] <= arrivalTime[i])		// 현재 처리중인 자극이 없으면 바로 처리
			{
				processTime[i] = response();
				endTime[i] = arrivalTime[i] + processTime[i];
				responseTime[i] = endTime[i] - arrivalTime[i];	// 응답시간은 처리 시간 - 도착시간
			}
			else									// 현재 처리중인 자극이 있으면 기다렸다가 처리
			{
				processTime[i] = response();
				endTime[i] = endTime[i-1] + processTime[i];
				responseTime[i] = endTime[i] - arrivalTime[i];	// 응답시간은 처리 시간 - 도착시간
			}
		}
	}

	AllJobEndTime = endTime[i-1];
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 평균 응답 시간 및 서버 활용도 계산	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(i=0; i<N; i++)								// 모든 고객에 대해서 시물레이션 진행
	{
		AverageResponseTime += responseTime[i];				// 모든 응답시간을 다 더합니다.
		ServerUtil += processTime[i];						// 모든 처리 시간을 더합니다.
	}
	AverageResponseTime = AverageResponseTime/N;	    // 응답시간의 평균을 구합니다.
	ServerUtil = ServerUtil/AllJobEndTime * 100.0;		// 모든 처리시간 나누기 마지막 자극 응답시간 (백분율)



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 출력!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("평균응답시간 : %10.4lf \n", AverageResponseTime);	 // 총 10자리출력, 소수점이하 4자리 출력
	printf("두뇌효율계산 : %10.4lf%% \n", ServerUtil);
	

	
}

