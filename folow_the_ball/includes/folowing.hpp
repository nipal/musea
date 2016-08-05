#ifndef FOLOWING_HPP 

 #define FOLOWING_HPP
 #define MAX_BALL 10
 #define MIN_SIZE 30
 #include <iostream>
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <math.h>
 #include <stdio.h>

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

t_surface	*detect_surface(Mat img, int *nb_balls);
void		redefine_id( t_surface *new_ball, t_surface *old_ball, int nb_bal);
void		draw_lines(t_surface *new_ball, t_surface *old_ball, int nb_bal, Mat *img);
#endif
