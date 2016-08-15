#include "folowing.hpp"

/*
	-on liste tout les point
	-on defini des famille en fonction des distance moyenne
	
	-on liste les zone non active et on lesrange enfonction deleur taille, on lesgardeenmemoire... un certain temps
	-on garde en memoire les n=10 position precedente, on fait une estimation de la vitesse et de l'acceleration
*/

/*
	-zone non Active
		on met le poid en negatif
	-trajet
		
*/

void	losted_zone(t_centre *new_ball, t_centre *old_ball)
{
	//	lacorrespondance entre les balle active et non active a deja ete etablie
	// On imprime les active et les non active
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout <<"same conexion:" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size > 0 && old_ball[i].size > 0)
		{
			cout << "	" << i<< " is OK"  << endl;
		}
	}
	cerr << endl << endl << "new has gone:" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size <= 0 && old_ball[i].size > 0)
		{
			cerr << "	" << i<< " despear"  << endl;
		}
	}
	cerr << endl << endl << "old weren't her" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size > 0 && old_ball[i].size <= 0)
		{
			cerr << "	" << i << " aparition"  << endl;
		}
	}
}

//	On liste les point blanc
Point	*list_valid_point(Mat img, int *nb_point)
{
	int id, size;
	Point	*list_pt;

	id		= 0;
	size	= img.cols * img.rows;
	list_pt 	= (Point*)malloc(sizeof(double) * size);

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

//	on trie les point en fonction de leure proximite, si il y en aun trop loin, on cree une nouvelle zone
int			sort_zone(int x, int y, t_centre* zone)
{
	int first_id, min_id;
	double	min_dist, dist, diff_x, diff_y;

	first_id = -1;
	min_id = -1;
	min_dist = -1;

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
	t_centre	*zone;
	int			nb_point;
	Point		*lst;


	zone		= (t_centre*)malloc(MAX_BALL * sizeof(t_centre));
	lst 		= list_valid_point(img, &nb_point);
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
//	describe_zone(zone, *nb_balls);
	free(lst);
	return (zone); 
}

void	describe_zone(t_centre *zone, int nb_ball)
{
	long x, y;
	cout << "________________________________________________" << endl;
	cout << "MAX_BALL:" << MAX_BALL << "	nb_ball:" << nb_ball << endl; 
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (zone[i].size > 0)
		{
			x = zone[i].sum_x / zone[i].size;
			y = zone[i].sum_y / zone[i].size;
		}
		else
		{
			x = -1;
			y = -1;
		}
		cout << "zone:" << i << "	x:" << x << "	y:" << y << "	size:" << zone[i].size << endl;	
	}
}
