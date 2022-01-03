//==============================================================================
//
// Title:		Sample
// Purpose:		A short description of the command-line tool.
//
// Created on:	01.08.2017 at 13:58:59 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include <ansi_c.h>
#include "TLTSPB.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  The main entry-point function.
/// HIPAR argc/The number of command-line arguments.
/// HIPAR argc/This number includes the name of the command-line tool.
/// HIPAR argv/An array of command-line arguments.
/// HIPAR argv/Element 0 contains the name of the command-line tool.
/// HIRET Returns 0 if successful.
int main (int argc, char *argv[])
{
	ViUInt32 devCnt = 0;
	ViStatus err = VI_SUCCESS;
	ViChar resName[256];
	ViSession vi;
	ViReal64 humidity;
	ViReal64 temperature; 
	
	ViUInt32 measCnt =0;
	
	ViReal64 m_chanExtTempR01;
	ViReal64 m_chanExtTempT01;
	ViReal64 m_chanExtTempBeta1;
	
	
	// get the number of all connected instruments (although they are in use by another application)
	err = TLTSPB_findRsrc(VI_NULL, &devCnt);

	// get the identifier of the instrument
	err = TLTSPB_getRsrcName(VI_NULL, 0, resName);

	// open the connection to the instrument by using the identifier
	err = TLTSPB_init(resName, VI_FALSE, VI_FALSE, &vi);
	
	// get the params
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_2, TLTSP_ATTR_SET_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_3, TLTSP_ATTR_SET_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_2, TLTSP_ATTR_MIN_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_3, TLTSP_ATTR_MIN_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_2, TLTSP_ATTR_MAX_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_3, TLTSP_ATTR_MAX_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_2, TLTSP_ATTR_DFLT_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);
	err = TLTSPB_getThermistorExpParams (vi, TLTSP_TEMPER_CHANNEL_3, TLTSP_ATTR_DFLT_VAL, &m_chanExtTempR01, &m_chanExtTempT01, &m_chanExtTempBeta1);

	
	// get a few measurements
	for(measCnt = 0; measCnt < 10; measCnt++)
	{
		
		Delay(1);
		err = TLTSPB_getHumidityData(vi, TLTSP_ATTR_SET_VAL, &humidity);
		err = TLTSPB_getTemperatureData(vi, TLTSP_TEMPER_CHANNEL_1, TLTSP_ATTR_SET_VAL, &temperature);
		err = TLTSPB_getTemperatureData(vi, TLTSP_TEMPER_CHANNEL_2, TLTSP_ATTR_SET_VAL, &temperature);
		err = TLTSPB_getTemperatureData(vi, TLTSP_TEMPER_CHANNEL_3, TLTSP_ATTR_SET_VAL, &temperature);

		
		printf("Temp %.2f, err: %d\n", temperature, err );
	}
	
	
	// release the connection to the instrument
	TLTSPB_close(vi);
	
	
	return 0;
}

