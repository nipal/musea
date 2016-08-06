#ifndef FOLOWING_HPP 

 #define FOLOWING_HPP
 #define MAX_BALL  20
 #define SIZE_BALL 100
 #define MIN_SIZE  10
 #include <iostream>
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <math.h>
 #include <stdio.h>
 #include <string.h>

using namespace cv;
using namespace std;

//void	detect_surface(Mat img);

typedef	struct	s_surface
{
	int	x;
	int	y;
	int	size;
	int	id;
}				t_surface;

typedef struct	s_centre
{
	long	sum_x = 0;
	long	sum_y = 0;
	int		size  = 0;
	int		id	  = 0;
}				t_centre;

t_centre	*detect_surface_v2(Mat img, int *nb_balls);
t_surface	*detect_surface(Mat img, int *nb_balls);
void		redefine_id( t_centre *new_ball, t_centre *old_ball, int nb_bal);
void		draw_lines(t_centre *new_ball, t_centre *old_ball, int nb_bal, Mat *img);
#endif
