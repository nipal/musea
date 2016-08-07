#include "folowing.hpp"

/*
   Pour trouver la correspondance entre lesdiferente point
	- On calcule les distance entre une balle et toute les autre
	- Pour chaqu balle on adapte
 */

//	On calcule toute les distance entre une new_ball et toute les old



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



