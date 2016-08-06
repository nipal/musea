#include "folowing.hpp"

/*
   Pour trouver la correspondance entre lesdiferente point
	- On calcule lesdistance entre chaque et on swap le emplacement comme capas de melange
 */
void	redefine_id( t_centre *new_ball, t_centre *old_ball, int nb_ball)
{
	//	On va chercher la corespondance entre les ancienne etles nouvelle position
	//	-On va chercher laposition laplus proche, et aussi esseailler de gerer d'eventuelleconflict
	int	distance[MAX_BALL][MAX_BALL];
	int	min = 100000;
	int	min_id;
	double x1, y1, x2, y2;
	t_centre	swap_ball;

	//	Ona calculer toute lees distance possible
	for (int j = 0; j < MAX_BALL && j < nb_ball; ++j)
	{
		min = 100000;
		if (new_ball[j].size > 0)
		{
			x1 = new_ball[j].sum_x / new_ball[j].size;
			y1 = new_ball[j].sum_y / new_ball[j].size;

			for (int i = 0; i < MAX_BALL; ++i)
			{
				if (new_ball[j].size > 0 && old_ball[i].size > 0)
				{
					x2 = old_ball[i].sum_x / old_ball[i].size;
					y2 = old_ball[i].sum_y / old_ball[i].size;
					distance[j][i] = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * y1 - y2);
					if (distance[j][i] < min)
					{
						min = distance[j][i];
	//					new_ball[j].id = old_ball[i].id;
					}
				}
				else
				{
					distance[j][i] = -1;
				}
			}
		}
	}

	//	On fait une swap en fonction deladidstance la plus courte
	for (int j = 0; j < MAX_BALL; ++j)
	{
		min_id = 0;
		min = 1000000;
		if (new_ball[j].size > 0)
		{
			for (int i = 0; i < MAX_BALL; ++i)
			{
				if (new_ball[i].size > 0 && distance[j][i] > 0 && distance[j][i] < min)
				{
					min = distance[j][i];
					min_id = i;
				}
			}
			swap_ball = old_ball[j];
			old_ball[j] = old_ball[min_id];
			old_ball[min_id] = swap_ball;
		}
	}


	//	On fait une swap en fonction deladidstance la plus courte
	for (int j = 0; j < MAX_BALL; ++j)
	{
		min_id = 0;
		min = 1000000;
		if (new_ball[j].size > 0)
		{
			for (int i = 0; i < MAX_BALL; ++i)
			{
				if (new_ball[i].size > 0 && distance[j][i] > 0 && distance[j][i] < min)
				{
					min = distance[j][i];
					min_id = i;
				}
			}
			swap_ball = old_ball[j];
			old_ball[j] = old_ball[min_id];
			old_ball[min_id] = swap_ball;
		}
	}
	
	//	En suite on va prendre pour commencer la distance la plus courte
	//	Puis on verra si il y a des comflict: deux nouvelleposition qui demande la meme
	//	Une positionqui demande une position d'un artefact
}



void	draw_lines(t_centre *new_ball, t_centre *old_ball, int nb_ball, Mat *img)
{
	int id;
	double x1, y1, x2, y2;

	//	cout << "======================================================================" << endl;
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (new_ball[i].size > MIN_SIZE)
		{
			id = i;
			if (old_ball[id].size > 0 && new_ball[i].size > 0)
			{
				x2 = old_ball[id].sum_x / old_ball[id].size;
				y2 = old_ball[id].sum_y / old_ball[id].size;
				x1 = new_ball[i].sum_x / new_ball[i].size;
				y1 = new_ball[i].sum_y / new_ball[i].size;
				line(*img, Point(x1, y1), Point(x2, y2), Scalar(0,i * (255 / nb_ball),255), 2);
			}
			//		cout << "" << endl;
			//		cout << "	newX:" << new_ball[i].x << "	newY:" << new_ball[i].y << "	size:" << new_ball[i].size << endl;
			//		cout << "	oldX:" << old_ball[id].x << "	oldY:" << old_ball[id].y <<  "	size:" << old_ball[id].size << endl;
			//		cout << "*********************************************************************" << endl;
		}
	}
	//	on atribu une couleur par deplacement de ball
	//	si il n'y a pas depositiion pour la ball en question onnetracerien, mais on garde en memoire la dernier qu'il y a eu
}


//line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);



