# include "mex.h"

void mexFunction ( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] );

void mexFunction ( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
	int i;
	double x;
	double y;
	double *y_pointer;

	x = mxGetScalar ( prhs[0] );

	y = 1.0;
	for ( i = 1; i <= ( int ) x; i++ )
	{
		y = y * ( double ) i;
	}

	plhs[0] = mxCreateDoubleMatrix ( 1, 1, mxREAL );

	y_pointer = mxGetPr ( plhs[0] );

	*y_pointer = y;

	return;
}
