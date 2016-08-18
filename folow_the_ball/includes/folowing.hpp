#ifndef FOLOWING_HPP 
 #define PRECISION 30 
 #define TIME_INTERVAL 5
 #define FOLOWING_HPP
 #define MAX_BALL  5
 #define SIZE_BALL 50
 #define MIN_SIZE  10
 #include <iostream>
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
 #include <math.h>
 #include <stdio.h>
 #include <string.h>
 #include <typeinfo>
 #include "SineWave.h"
 #include "RtAudio.h"
 #include "RtWvOut.h"
 #include <cstdlib>

using namespace cv;
using namespace std;
using namespace stk;

//void	detect_surface(Mat img);

//	n'est plus utile
typedef	struct	s_surface
{
	int	x;
	int	y;
	int	size;
	int	id;
}				t_surface;

typedef struct	s_centre
{
	long	sum_x;
	long	sum_y;
	int		size;
	int		id;
}				t_centre;

typedef	struct	s_body_data
{
	cv::Size	size;
	t_centre	*zone;
	Mat			*img;
}				t_body_data;

typedef	struct	s_conex
{
	t_centre				*zone;
	Mat						conexion;
	struct	s_conex 	*next;
}				t_conex;

//sound
void	play_ball(RtWvOut *dac, SineWave sine[MAX_BALL], t_centre *zone);
void	my_stk_init();
void	play_some(RtWvOut *dac);
RtWvOut	*open_stream();

//	calcule_distance.cpp
//	on a juste besoin d'appeler swap_old ou swap_new, ils'ocupe du renste
void CallBackFunc(int event, int x, int y, int flags, void* userdata);
int	closer_zone(int x, int y, t_centre *zone);
int		id_to_swap_old(t_centre *new_ball, t_centre *old_ball, int id_new);
int		id_to_swap_new(t_centre *new_ball, t_centre *old_ball, int id_old);
double	*calcul_dist_to_old(t_centre *new_ball, t_centre *old_ball, int id_new);
double	*calcul_dist_to_new(t_centre *new_ball, t_centre *old_ball, int id_old);
void	swap_old(t_centre *new_ball, t_centre *old_ball);
void	swap_new(t_centre *new_ball, t_centre *old_ball);

void	draw_body(t_centre *zone, Mat *imgBody);
//singleton
Mat	*get_connexion(Mat *data);
cv::Size	*get_imgSIze(cv::Size *data);

void	describe_zone(t_centre *zone, int nb_ball);

t_centre	*detect_surface_v2(Mat img, int *nb_balls);
t_surface	*detect_surface(Mat img, int *nb_balls);
void		redefine_id( t_centre *new_ball, t_centre *old_ball, int nb_bal);
void		draw_lines(t_centre *new_ball, t_centre *old_ball, int nb_ball, Mat *img);


void	losted_zone(t_centre *new_ball, t_centre *old_ball);
void	multi_sound(t_centre *zone);
#endif
