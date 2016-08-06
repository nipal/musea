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
	Point	*list_pt 	= (Point*)malloc(sizeof(double) * size);

	bzero(list_pt, size * sizeof(Point));
	*nb_point = 0;
	for (int i = 0; i < size; ++i)
	{
		if (img.data[i] == 255)
		{
			list_pt[id] = Point((double)(i % img.cols), (double)(i / img.cols));
			id++;
		}
	}
	*nb_point = id;
	return (list_pt);
}

int			sort_zone(int x, int y, t_centre* zone)
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
	}
	if (min_dist < SIZE_BALL && min_dist > 0)
	{
		zone[min_id].sum_x += x;
		zone[min_id].sum_y += y;
		zone[min_id].size++;
	}
	else if (first_id != -1)
	{
		zone[first_id].sum_x = x;
		zone[first_id].sum_y = y;
		zone[first_id].size = 1;
		zone[first_id].id = first_id;	
	}
	else
	{
		cout << "(((((((((((((((((((((((((((   -->  no more space <--  )))))))))))))))))))))))))))" << endl;
	}
	return (0);
}

t_centre	*detect_surface_v2(Mat img, int *nb_balls)
{
	t_centre	*zone		= (t_centre*)malloc(MAX_BALL * sizeof(t_centre));
	int			nb_point;
	int			id 			= 0;
	Point		*lst 		= list_valid_point(img, &nb_point);
	//	on vafaire une liste de centre	

	bzero(zone, MAX_BALL * sizeof(t_centre));
//	cout << "=================================================" << endl; 
	*nb_balls = 0;
	for (int i = 0; i < nb_point; ++i)
	{
		//	Pour chaque point on lui attribut une zone enfonction de sa distance a celle-ci
		sort_zone(lst[i].x, lst[i].y, zone);	
	}
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (zone[i].size > 0)
		{
			*nb_balls += 1;
		}
	}
	return (zone); 
}
