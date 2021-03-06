//////////////////////////////////////////////////////////////////////////////////////////////////
//
//			Program to test intrinsic function to get copy of VEX Cortex IME I2C Statistics
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,            ,             tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,            ,             tmotorVex269, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port3,            ,             tmotorVex269, openLoop, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port10,           ,             tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int kPegSize = 15;
static long nHistogram[kPegSize + 1];
static TSpuriousInterruptPegCounts nInterruptPegs;
static TI2cStatistics nI2cStatistics;
static long nLoopTime;
static unsigned long nLoopStartTime;
static unsigned long nNextHistogramTIme;
static unsigned long nCycleTimeHistogram[15];

task main()
{
	unsigned int nMsgCountThisLoop;
	unsigned int nCurrMsgCount;
	unsigned int nPrevMsgCount = nI2cStatistics.nTotalI2cMessagesSent;
	nNextHistogramTIme = nSysTime + 10;
	while (true)
	{
		nLoopStartTime = nSysTime;
		getI2CStatistics(&nI2cStatistics, sizeof(nI2cStatistics));
		getI2CErrorPegs(&nInterruptPegs, sizeof(nInterruptPegs));

		if (nSysTime >= nNextHistogramTIme)
		{
			nNextHistogramTIme = nSysTime + 10;
			nCurrMsgCount = nI2cStatistics.nTotalI2cMessagesSent;
			nMsgCountThisLoop = nCurrMsgCount - nPrevMsgCount;
			nPrevMsgCount = nCurrMsgCount;
			if (nMsgCountThisLoop > kPegSize)
				++nHistogram[kPegSize];
			else
				++nHistogram[nMsgCountThisLoop];
		}
		nLoopTime = nSysTime - nLoopStartTime;
		if (nLoopTime >= 15)
			nLoopTime = 14;
		++nCycleTimeHistogram[nLoopTime];
	}
	return;
}
