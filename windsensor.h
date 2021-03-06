/************************************************************************/
/*									                                    */
/*		                P R O J E K T    A V A L O N	                */
/*								                                    	*/
/*  	windsensor.h	  The class for the wind data                   */
/*									                                    */
/*	    Author  	      Stefan Wismer			                        */
/*                        wismerst@student.ethz.ch                      */
/*									                                    */
/************************************************************************/


#ifndef WINDSENSOR_H
#define WINDSENSOR_H

#include <DDXStore.h>
#include <DDXVariable.h>

DDX_STORE_TYPE(WindData,
  struct {
    double direction;		// In Degree (from -180 to +180 degrees)
    double speed;		// Windspeed in Knots
    double temperature;		// Temperature at the Surface
    double voltage;		// Voltage of the heating
    int uptodate;		// Are Voltage and Temp up to date? (0 = no, not 0 = yes)
  }
);

#endif // WINDSENSOR_H
