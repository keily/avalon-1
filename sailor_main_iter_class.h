
#ifndef SAILOR_MAIN_ITER_CLASS_H
#define SAILOR_MAIN_ITER_CLASS_H

// General Things
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "avalon.h"
#include "sailor_rudder_iter_fn.h"

// General gsl-Things
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>


class sailor_main_iter_class
{
		//private:
                public:
                            int status;
                            int iter, max_iter;
                            const gsl_root_fsolver_type *T;
                            gsl_root_fsolver *s;
                    
                //public:     
                            double iter_start;
           
                            sailor_main_iter_class() {// TODO
			    }  
                      
                            double sailor_main_iter_fn(double heading_speed, double torque_des, double speed_x, double speed_y, double aoa_sail, double d_wind, double pose_33, double V_wind);
                            double alpha_r;
                            double x;
                            double x_lo; 
                            double x_hi;
};

#endif