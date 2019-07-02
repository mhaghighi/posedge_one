//============================================================================
// Name        : afifo.cpp
// Author      : mahmoud
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "mex.h"
#include <iostream>
using namespace std;

#include "ftd2xx.h"
#include "stdio.h"
#include "windows.h"

#define SECTOR 64*1024 //64*1024
#define MAX_SIZE 512*1024

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	#define A_IN prhs[0]
	#define B_OUT plhs[0]
	//unsigned char *A, *B;
	double *A, *B;
	//A = (unsigned char *)mxGetPr(A_IN);	
	A = mxGetPr(A_IN);	
	int M = (int)mxGetM(A_IN);
	int N = (int)mxGetN(A_IN);
	int i, j;
	//B_OUT = mxCreateNumericMatrix(M, N, mxCHAR_CLASS, mxREAL);
	B_OUT = mxCreateDoubleMatrix(M, N, mxREAL);
	B = mxGetPr(B_OUT);

	
	if (N > MAX_SIZE || M != 1)
		mexPrintf("Invalid input array size (maximum: 512K*1 unsigned char array)");
	
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;
	DWORD BytesWritten;
	DWORD BytesRead;
	unsigned char rx_buffer[MAX_SIZE];
	unsigned char tx_buffer[MAX_SIZE];
	DWORD t0, t1, t_total = 0, t1_prev = 0;
	DWORD rxBytes = 0;
	DWORD txBytes = 0;
	DWORD errors = 0;
	float kbps;

	for (int i=0; i<N; i++)
	{
		tx_buffer[i] = A[i];
		rx_buffer[i] = 0;
	}

	// Open
	ftStatus = FT_OpenEx((PVOID) "Digilent USB Device B", FT_OPEN_BY_DESCRIPTION, &ftHandle);
	if (ftStatus != FT_OK) {
	  mexPrintf("Failed to open device!\n");
	  return;
	} else {
	  mexPrintf("Opened Device Successfully!\n");
	}
	
	ftStatus = FT_SetUSBParameters(ftHandle, SECTOR, SECTOR);
	FT_Purge(ftHandle, FT_PURGE_RX);
	ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
	FT_SetTimeouts(ftHandle, 1000, 1000);

	//t0 = GetTickCount();

	// TX
	//for (i=0; i < N/SECTOR + 1; i=i+SECTOR)
	//{
	//	for (j=0; j<SECTOR; j++)
	//	{
	//		tx_buffer[j] = A[j+i];
			//mexPrintf("%x\n", tx_buffer[j]);
	//	}
			
		ftStatus  = FT_Write(ftHandle, tx_buffer, N, &BytesWritten);
		txBytes += BytesWritten;	
	//}	
	mexPrintf("%d bytes written\n", txBytes);
	
	for(i=0;i<10000000;i++); // delay
	
	// RX
	//for (i=0; i < M/SECTOR; i=i+SECTOR)
	//{
		ftStatus  = FT_Read(ftHandle, rx_buffer, N, &BytesRead);
		rxBytes += BytesRead;
	//}
	mexPrintf("%d bytes read\n", rxBytes);
	for (int i=0; i<N; i++)
	{
		B[i] = rx_buffer[i];
	}
	
	
	// Print RX
	/*
	for (int i = 0; i < SECTOR; i++) {
		//cout << (int) rx_buffer[i] << endl;
		mexPrintf("%x\n", rx_buffer[i]);
	}
	*/


	//mexPrintf("%d Bytes | %d errors\n");
	ftStatus = FT_Close(ftHandle);

return;
}


