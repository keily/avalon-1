// General Things
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "avalon.h"
#include "sailor_rudder_iter_fn.h"
#include "sailor_main_iter_class.h" 


// General gsl-Things
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_min.h>


//sailor_main_iter_class::sailor_main_iter_class()
//{
//}

double sailor_main_iter_class::sailor_main_iter_fn(double heading_speed, double torque_des, 
		double speed_x, double speed_y, double aoa_sail, 
		double d_wind, double pose_3, double V_wind )
{
	iter_start = atan2(((speed_y - 1.7*heading_speed)*0.01),speed_x);
	iter = 0, max_iter = 100;
	// const gsl_root_fsolver_type *T;
	// gsl_root_fsolver *s;
	// alpha_r = 0;

	x_lo = iter_start - 10.0*M_PI/180;//iter_start - 15*M_PI/180; 
	x_hi = iter_start + 10.0*M_PI/180;//iter_start + 15*M_PI/180;
	gsl_function F;

	struct rudder_iter_params params = {heading_speed, torque_des, speed_x, speed_y, aoa_sail, d_wind, pose_3, V_wind};

	F.function = &sailor_rudder_iter_fn;
	F.params   = &params;

#ifdef ROOT_FINDING
	const gsl_root_fsolver_type *T;
	gsl_root_fsolver *s;

	T = gsl_root_fsolver_brent;
	s = gsl_root_fsolver_alloc (T);
	gsl_root_fsolver_set (s, &F, x_lo, x_hi);

	do
	{
		iter++;
		status   = gsl_root_fsolver_iterate (s);
		x        = gsl_root_fsolver_root (s);
		x_lo     = gsl_root_fsolver_x_lower (s);
		x_hi     = gsl_root_fsolver_x_upper (s);
		status   = gsl_root_test_interval (x_lo, x_hi, 0, 0.1);
		alpha_r  = x;
	}

	while (status == GSL_CONTINUE && iter < max_iter);

	gsl_root_fsolver_free (s);
#else // Minimisation
	const gsl_min_fminimizer_type *T;
	gsl_min_fminimizer *s;

	T = gsl_min_fminimizer_brent;
	s = gsl_min_fminimizer_alloc (T);
	gsl_min_fminimizer_set (s, &F, iter_start, x_lo, x_hi);

	do
	{
		iter++;
		status = gsl_min_fminimizer_iterate (s);
		x = gsl_min_fminimizer_x_minimum (s);
		x_lo = gsl_min_fminimizer_x_lower (s);
		x_hi = gsl_min_fminimizer_x_upper (s);

		status = gsl_min_test_interval (x_lo, x_hi, 0.001, 0.0);
	}
	while (status == GSL_CONTINUE && iter < max_iter);

	gsl_min_fminimizer_free (s);
#endif

	// return status;
	return alpha_r*180/M_PI;
}

