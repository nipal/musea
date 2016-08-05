#include "folowing.hpp"

/*
	-on liste tout les point
	-on defini des famille en fonction des distance moyenne
*/

//	{x,y} 
Point	*list_valid_point(Mat img, int *nb_point)
{
	int		id				= 0;
	int		size			= img.cols * img.rows;
//	Point	dim				= new Point(img.cols, img.rows);
	Point	*list_pt 	= (Point*)malloc(sizeof(double) * size);

	bzero(list_pt, size * sizeof(Point));
	*nb_point = 0;
	for (int i = 0; i < size; ++i)
	{
		if (img.data[i] == 255)
		{
			list_pt[id] = Point((double)(i % img.cols), (double)(i / img.rows));
			id++;
		}
	}
	*nb_point = id;
	return (list_pt);
}

t_surface *detect_surface_v2(Mat img, int *nb_balls)
{
	long		dist_moy = 0;
	long		nb_moy = 0;

	long		dist_max = 0;
	long		nb_max = 0;

//	t_centre	*zone		= (t_centre)malloc(MAX_BALL * sizeof(t_centre));
	int			nb_point;
	int			id 			= 0;
	int			size		= img.cols * img.rows;
	Point		*lst 		= list_valid_point(img, &nb_point);
	double	prevX, prevY, newX, newY, dist;	
//	on vafaire une liste de centre	

//	bzero(zone, MAX_BALL * sizeof(t_centre));
	cout << "=================================================" << endl; 
	*nb_balls = 0;
	for (int i = 0; i < nb_point; ++i)
	{
		//	On va calculer la distance a tout les centre avec: size > 0
		//	on prend le plus petit < SIZE_BALL




		newX = lst[i].x;
		newY = lst[i].y;
		if (i > 0)
		{
			dist = sqrt(((newX - prevX) * (newX - prevX) + (newY - prevY) * (newY - prevY)));
			if (dist < SIZE_BALL && dist > 1)
			{
				dist_moy += dist;
				nb_moy += 1;
	//			cout << "x:" << newX << "	y:" << newY << "	dist:" << dist << endl; 
			}
			else if (dist > SIZE_BALL)
			{
				dist_max += dist;
				nb_max += 1;
			}
		}


		prevX = newX;
		prevY = newY;
	}
	if (nb_moy > 0)
	{
	cout << "dist_moy:" << (dist_moy / nb_moy) << endl;
	}
	if (nb_max > 0)
	{
		cout << "dist_moy:" << (dist_max / nb_max) << endl;
	}
	return (NULL); 
}
