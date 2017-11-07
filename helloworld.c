/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <xsimplealu.h>
#include <xsimplealu_hw.h>
#include "platform.h"
#include "xil_printf.h"





//volatile unsigned int *ipBaseAddr=( unsigned int *)0x43c00000;
volatile unsigned int *regA = ( unsigned int *)0x43c00010;
volatile unsigned int *regB = ( unsigned int *)0x43c00018;
volatile unsigned int *regOp = ( unsigned int *)0x43c00020;
volatile unsigned int *regC = ( unsigned int *)0x43c00028;
volatile unsigned int *regCrtl = ( unsigned int *)0x43c00000;

void bm_IP_Start()
{
	unsigned int data = (*regCrtl & 0x80);
	*regCrtl =(data | 0x01);

}

unsigned int bm_IP_IsDone()
{
	unsigned int data = *regCrtl;
	return ((data >> 1)& 0x1);
}
/*
XSimplealu xSimpleAluInst;

void initSimpleAlu()
{
//	int status;

	XSimplealu_Config *xSimpleAluCfg;
	// = new XSimplealu_Config;
//	xSimpleAluCfg->Ctrl_bus_BaseAddress = 0x43C00000;
//	xSimpleAluCfg -> DeviceId = 0;

	xSimpleAluCfg =XSimplealu_LookupConfig(XPAR_SIMPLEALU_0_DEVICE_ID);



if(!xSimpleAluCfg)
{
	printf("hardwre not found");

}
if(XSimplealu_CfgInitialize(&xSimpleAluInst,xSimpleAluCfg)!= XST_SUCCESS){
	printf("Error config");
}

}

*/

int main()
{
    //initSimpleAlu();
    printf("bare metal wuth HLS driver\n");
    int a,b;


    a=20; b=10;
    *regA=a;
    *regB = b;
    *regOp =0;
    bm_IP_Start();
    while(!bm_IP_IsDone());
    printf("A(%d)+B(%d)=%d \n ",a,b,*regC);

    a=20; b=10;
    *regA=a;
    *regB = b;
    *regOp =1;
    bm_IP_Start();
    while(!bm_IP_IsDone());
    printf("A(%d)-B(%d)=%d \n ",a,b,*regC);

    a=20; b=10;
    *regA=a;
    *regB = b;
    *regOp =2;
    bm_IP_Start();
    while(!bm_IP_IsDone());
    printf("A(%d)*B(%d)=%d \n ",a,b,*regC);



/*
    a=10; b=5;
    XSimplealu_Set_A(&xSimpleAluInst,a); XSimplealu_Set_B(&xSimpleAluInst,b);
    XSimplealu_Set_op(&xSimpleAluInst,2);
    XSimplealu_Start(&xSimpleAluInst);
    while(!XSimplealu_IsDone(&xSimpleAluInst));
   // printf("A(%d)+B(%d)=%d \n ",a,b,(int)XSimplealu_Get_C_vld(&xSimpleAluInst));
    printf("A(%d)+B(%d)=%d \n ",a,b,*regC);




    a=10; b=5;
    XSimplealu_Set_A(&xSimpleAluInst,a); XSimplealu_Set_B(&xSimpleAluInst,b);
    XSimplealu_Set_op(&xSimpleAluInst,3);
    XSimplealu_Start(&xSimpleAluInst);
    while(!XSimplealu_IsDone(&xSimpleAluInst));
    // printf("A(%d)+B(%d)=%d \n ",a,b,(int)XSimplealu_Get_C_vld(&xSimpleAluInst));
    printf("A(%d)+B(%d)=%d \n ",a,b,*regC);

*/









}
