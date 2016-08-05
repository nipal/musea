#include "folowing.hpp"

void	redefine_id( t_surface *new_ball, t_surface *old_ball, int nb_bal)
{
	//	On va chercher la corespondance entre les ancienne etles nouvelle position
	//		-On va chercher laposition laplus proche, et aussi esseailler de gerer d'eventuelleconflict
	int	distance[MAX_BALL][MAX_BALL];
	int	min = 100000;
	(void)nb_bal;

	//	Ona calculer toute lees distance possible
	for (int j = 0; j < MAX_BALL; ++j)
	{
		min = 100000;
		for (int i = 0; i < MAX_BALL; ++i)
		{
			if (new_ball[j].size > MIN_SIZE && old_ball[i].size > MIN_SIZE)
			{
				distance[j][i] = sqrt(((new_ball[j].x - old_ball[i].x) * (new_ball[j].x - old_ball[i].x)) + ((new_ball[j].y - old_ball[i].y) * (new_ball[j].y - old_ball[i].y)));
				if (distance[j][i] < min)
				{
					min = distance[j][i];
					new_ball[j].id = old_ball[i].id;
				}
			}
			else
			{
				distance[j][i] = -1;
			}
		}
	}
	
	//	En suite on va prendre pour commencer la distance la plus courte
	//	Puis on verra si il y a des comflict: deux nouvelleposition qui demande la meme
	//	Une positionqui demande une position d'un artefact
}

void	draw_lines(t_surface *new_ball, t_surface *old_ball, int nb_bal, Mat *img)
{
	int id;
	int lastX;
	int	lastY;

	cout << "======================================================================" << endl;
	for (int i = 0; i < MAX_BALL; ++i)
	{
		if (new_ball[i].size > MIN_SIZE)
		{
			id = new_ball[i].id;
			lastX = old_ball[id].x;
			lastY = old_ball[id].y;
			line(*img, Point(new_ball[i].x, new_ball[i].y), Point(lastX, lastY), Scalar(0,255 - ((255 * (i))/ MAX_BALL),(255 * (i))/ MAX_BALL), 2);
			cout << "" << endl;
			cout << "	newX:" << new_ball[i].x << "	newY:" << new_ball[i].y << "	size:" << new_ball[i].size << endl;
			cout << "	oldX:" << old_ball[id].x << "	oldY:" << old_ball[id].y <<  "	size:" << old_ball[id].size << endl;
			cout << "*********************************************************************" << endl;
		}
	}
	//	on atribu une couleur par deplacement de ball
	//	si il n'y a pas depositiion pour la ball en question onnetracerien, mais on garde en memoire la dernier qu'il y a eu
}


//line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);



