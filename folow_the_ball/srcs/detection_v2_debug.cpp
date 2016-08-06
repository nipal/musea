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

int			id_zone(int x, int y, t_centre* zone)
{
	int		first_id = -1;
	int		min_id = -1;
	double	min_dist = -1;
	double	dist;
	double	diff_x;
	double	diff_y;

	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (zone[i].size > 0)
		{
//			cout << "zone.x:" << (zone[i].sum_x / zone[i].size);
//			cout << " zone.y:" << (zone[i].sum_y / zone[i].size) << endl;
			diff_x = (zone[i].sum_x / zone[i].size) - x;
			diff_y = (zone[i].sum_y / zone[i].size) - y;
			dist = sqrt((diff_x * diff_x + diff_y * diff_y));
			if (dist < min_dist || min_dist == -1)
			{
				min_dist = dist;
				min_id = i;
			}
		}
		else if (first_id == -1)
		{
			first_id = i;
		}
//		cout << "i:" << i;
	}
//	cout << endl << "x:" << x << "	y:" << y << endl;
//	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	//cout << "min_dist:" << min_dist << "	min_id:" << min_id <<"	first_id:" << first_id << endl;
//	cout <<  "	min_id:" << min_id <<"	first_id:" << first_id << endl;
//	cout << "min dist:"<< min_dist << endl;
	if (min_dist < SIZE_BALL && min_dist > 0)
	{
		zone[min_id].sum_x += x;
		zone[min_id].sum_y += y;
		zone[min_id].size++;
//		cout << "zone:" << min_id  << "	min_dist:" << min_dist  << endl;
	}
	else if (first_id != -1)
	{
//		cout << "zone:" << first_id << endl;
		zone[first_id].sum_x = x;
		zone[first_id].sum_y = y;
		zone[first_id].size = 1;	
	}
	else
	{
//		cout << "(((((((((((((((((((((((((((   -->  no more space <--  )))))))))))))))))))))))))))" << endl;
	}
	return (0);
}

t_surface	*detect_surface_v2(Mat img, int *nb_balls)
{
	long		dist_moy = 0;
	long		nb_moy = 0;

	long		dist_max = 0;
	long		nb_max = 0;

	t_centre	*zone		= (t_centre*)malloc(MAX_BALL * sizeof(t_centre));
	int			nb_point;
	int			id 			= 0;
	int			size		= img.cols * img.rows;
	Point		*lst 		= list_valid_point(img, &nb_point);
	double	prevX, prevY, newX, newY, dist;	
//	on vafaire une liste de centre	

	bzero(zone, MAX_BALL * sizeof(t_centre));
	cout << "=================================================" << endl; 
	*nb_balls = 0;
	for (int i = 0; i < nb_point; ++i)
	{
		//	On va calculer la distance a tout les centre avec: size > 0
		//	on prend le plus petit < SIZE_BALL


		id_zone(lst[i].x, lst[i].y, zone);	
/*
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
//*/
	}
/*
	if (nb_moy > 0)
	{
		cout << "dist_moy:" << (dist_moy / nb_moy) << endl;
	}
	if (nb_max > 0)
	{
		cout << "dist_moy:" << (dist_max / nb_max) << endl;
	}
//*/
	return (NULL); 
}
