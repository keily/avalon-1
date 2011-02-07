// General Things
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include "avalon.h"

// General rtx-Things
#include <rtx/getopt.h>
#include <rtx/main.h>
#include <rtx/error.h>
#include <rtx/timer.h>
#include <rtx/thread.h>
#include <rtx/message.h>

double sailor_inverted_linear_model(double heading_speed, double torque_des, 
		double speed_x, double speed_y) 
{    
    double dens_water      = 1025.0;       
    double A_rudder        = 0.085;
    double dist_rudder_CenterOfRotation = 1.7;

    double v_r_tot;
    double d_water;
    double incid_angle;
    double rudder_angle;

    v_r_tot	= sqrt((speed_x*speed_x) + ((speed_y - dist_rudder_CenterOfRotation*heading_speed)*(speed_y - dist_rudder_CenterOfRotation*heading_speed)));
   // d_water     = atan2((speed_y - dist_rudder_CenterOfRotation*heading_speed),speed_x)*180/AV_PI; 
    d_water	= 0;
    incid_angle = torque_des / (AV_MODEL_LIN_COEFF*dist_rudder_CenterOfRotation*dens_water*v_r_tot*v_r_tot*A_rudder) *180/AV_PI;

    if(incid_angle > 10)
    {
	incid_angle = 10;
    }
    else if(incid_angle < -10)
    {
      incid_angle = -10;
    }
    rudder_angle = remainder(incid_angle + d_water,360.);

	if(rudder_angle > AV_MAX_RUDDER_ANGLE)
	{
		rudder_angle = AV_MAX_RUDDER_ANGLE;
	}
	else if (rudder_angle < -AV_MAX_RUDDER_ANGLE)
	{
		rudder_angle = -AV_MAX_RUDDER_ANGLE;
	}
FILE * model_file;
FILE * model_plot;
model_file = fopen("model_file.txt","a+");
fprintf(model_file,"approach velocity: %f, speed_y: %f, speed_x: %f, theta_dot: %f, rudderangle:%f \n",v_r_tot, speed_y, speed_x, heading_speed, rudder_angle); 
fclose(model_file);
model_plot = fopen("model_plot.txt","a+");
fprintf(model_plot,"%f %f %f %f %f \n",v_r_tot, speed_y, speed_x, heading_speed, rudder_angle);
fclose(model_plot);
	return rudder_angle;
}




