// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>

//#define SRS	16384
//#define SRS	8192
//#define SRS	12288
//#define SRS	6144
#define SRS	512
#define FS	(double)SRS*30
#define PI	3.14159265359
#define SHORT_MAX	32767

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* dest = NULL;
	int i=0;

	// Open File
	dest = fopen("result.csv", "wt");
	if(dest == NULL)
		printf("File Open Error");
	
	for(i=0; i<SRS; i++)
	{
		
		// Make Sine Table
		
		// 30Hz Sine
		unsigned short DataValue = (unsigned short)(sin( (i/(double)SRS)*2*PI ) * (double)SHORT_MAX + SHORT_MAX);

		// 30Hz Cosine
		//unsigned short DataValue = (unsigned short)(cos( (i/(double)SRS)*2*PI ) * (double)SHORT_MAX + SHORT_MAX);

		// 1020Hz Cosine
		//unsigned short DataValue = (unsigned short)(sin( (i/(double)SRS)*2*PI * 1020/30 ) * (double)SHORT_MAX + SHORT_MAX);

		// FM 30Hz
		//unsigned short DataValue = (unsigned short)(sin((i/(double)SRS)*2*PI * (9960/30) + ((480+480)/30)*(sin(i* 2* PI * (30/30)))) * (double)SHORT_MAX + SHORT_MAX);

		// 720Hz Blending Cosine
		//double DataValueDouble = (cos( (i/(double)SRS)*2*PI * 720/30 ));
		//if(DataValueDouble < 0) DataValueDouble *= -1;
		//unsigned short DataValue = DataValueDouble * SHORT_MAX + SHORT_MAX;

		// 720Hz Blending Sine
		//double DataValueDouble = (sin( (i/(double)SRS)*2*PI * 720/30 ));
		//if(DataValueDouble < 0) DataValueDouble *= -1;
		//unsigned short DataValue = DataValueDouble * SHORT_MAX + SHORT_MAX;

		// 90+150
		//unsigned short DataValue = (unsigned short)(((sin((i/(double)SRS)*2*PI * 90/30 ) + sin( (i/(double)SRS)*2*PI * 150/30 ) )* (double)SHORT_MAX + SHORT_MAX)/2);

		// 90-150
		//unsigned short DataValue = (unsigned short)(((sin((i/(double)SRS)*2*PI * 90/30 ) - sin( (i/(double)SRS)*2*PI * 150/30 ) )* (double)SHORT_MAX + SHORT_MAX)/2);



		
		// Write File
		fprintf(dest, "%d,", DataValue);
		//printf("%d,\n", DataValue);
	}

	fclose(dest);

	return 0;
}

