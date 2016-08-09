#include "folowing.hpp"

//	On envoiune position et on retourne l'id de la zne laplus proche
int	closer_zone(int x, int y, t_centre *zone)
{
	int	dx, dy, id;
	double	min, dist;

	min = 100000;
	id = -1;
//	cout << "haha" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
//		cout << "i:" << i << endl;
		if (zone[i].size > 0)
		{
			dx = x - (zone[i].sum_x / zone[i].size);
			dy = y - (zone[i].sum_y / zone[i].size);
			dist = sqrt(dx * dx + dy * dy);
			if (dist < min)
			{
				id = i;
				min = dist;
			}
		}
	}
	return (id);
}

//	On calcule la plus petite distance avec les old_ball et on renvoie l'id
int	id_to_swap_old(t_centre *new_ball, t_centre *old_ball, int id_new)
{
	double	distance[MAX_BALL];
	double x1, y1, x2, y2, min_dist, min_id;

	if (!new_ball || !old_ball || new_ball[id_new].size <= 0)
	{
		cout << "FAIL SWAP_OLD" << endl;
		return (-1);
	}
	
	x1 = new_ball[id_new].sum_x / new_ball[id_new].size;
	y1 = new_ball[id_new].sum_y / new_ball[id_new].size;
	min_dist = 1000000;
	min_id = -1;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (old_ball[i].size > 0)
		{
			x2 = old_ball[i].sum_x / old_ball[i].size;
			y2 = old_ball[i].sum_y / old_ball[i].size;
			distance[i] = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
			if (distance[i] < min_dist)
			{
				min_dist = distance[i];
				min_id = i;
			}
		}
		else
		{
			distance[i] = -1;
		}
	}
	return (min_id);
}

int	id_to_swap_new(t_centre *new_ball, t_centre *old_ball, int id_old)
{
	double	distance[MAX_BALL];
	double x1, y1, x2, y2, min_dist, min_id;

	if (!new_ball || !old_ball || old_ball[id_old].size <= 0)
	{
		cout << "FAIL SWAP_NEW" << endl;
		return (-1);
	}
	
	x1 = old_ball[id_old].sum_x / old_ball[id_old].size;
	y1 = old_ball[id_old].sum_y / old_ball[id_old].size;
	min_dist = 1000000;
	min_id = -1;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size > 0)
		{
			x2 = new_ball[i].sum_x / new_ball[i].size;
			y2 = new_ball[i].sum_y / new_ball[i].size;
			distance[i] = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
			if (distance[i] < min_dist)
			{
				min_dist = distance[i];
				min_id = i;
			}
		}
		else
		{
			distance[i] = -1;
		}
	}
	return (min_id);
}

//	On calcule les distance d'un new avec tout les old
double	*calcul_dist_to_old(t_centre *new_ball, t_centre *old_ball, int id_new)
{
	double	*distance;
	double x1, y1, x2, y2;

	if (!(distance = (double*)malloc(sizeof(double) * MAX_BALL)) || !new_ball || !old_ball || new_ball[id_new].size <= 0)
	{
		return (NULL);
	}
	
	x1 = new_ball[id_new].sum_x / new_ball[id_new].size;
	y1 = new_ball[id_new].sum_y / new_ball[id_new].size;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (old_ball[i].size > 0)
		{
			x2 = old_ball[i].sum_x / old_ball[i].size;
			y2 = old_ball[i].sum_y / old_ball[i].size;
			distance[i] = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
		}
		else
		{
			distance[i] = -1;
		}
	}
	return (distance);
}

//	On calcule les distance d'un new avec tout les new
double	*calcul_dist_to_new(t_centre *new_ball, t_centre *old_ball, int id_old)
{
	double	*distance;
	double x1, y1, x2, y2;

	if (!(distance = (double*)malloc(sizeof(double) * MAX_BALL)) || !new_ball || !old_ball || old_ball[id_old].size <= 0)
	{
		return (NULL);
	}
	
	x1 = old_ball[id_old].sum_x / old_ball[id_old].size;
	y1 = old_ball[id_old].sum_y / old_ball[id_old].size;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size > 0)
		{
			x2 = new_ball[i].sum_x / new_ball[i].size;
			y2 = new_ball[i].sum_y / new_ball[i].size;
			distance[i] = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
		}
		else
		{
			distance[i] = -1;
		}
	}
	return (distance);
}

void	swap_old(t_centre *new_ball, t_centre *old_ball)
{
	int			id_swap;
	t_centre	swap;

//	cout << "------------------------------------------------" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (new_ball[i].size > 0)
		{
			id_swap = id_to_swap_old(new_ball, old_ball, i);
			if (id_swap >= 0 && i != id_swap)
			{
//				cout << "swaping: " << i << " and " << id_swap << endl; 
				swap = old_ball[i];
				old_ball[i] = old_ball[id_swap];
				old_ball[id_swap] = swap;
			}
		}	
	}
}

void	swap_new(t_centre *new_ball, t_centre *old_ball)
{
	int			id_swap;
	t_centre	swap;

//	cout << "------------------------------------------------" << endl;
	for (int i = 0; i < MAX_BALL; i++)
	{
		if (old_ball[i].size > 0)
		{
			id_swap = id_to_swap_new(new_ball, old_ball, i);
			if (id_swap >= 0 && i != id_swap)
			{
//				cout << "swaping: " << i << " and " << id_swap << endl; 
				swap = new_ball[i];
				new_ball[i] = new_ball[id_swap];
				new_ball[id_swap] = swap;
			}
		}	
	}
}
