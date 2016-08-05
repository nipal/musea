#include "folowing.hpp"


void	find_one(Mat *img, int i, int *x, int *y, int *number)
{
	int pos = 0;

	*number += 1;
	*x += i % img->cols;
	*y += i / img->cols;
	img->data[i] = 0;
	if ((pos = (i % img->cols)) < img->cols - 1 && img->data[pos] == 255)	find_one(img, i + 1, x, y, number);
	if ((pos = (i % img->cols)) > 0 && img->data[pos] == 255) 				find_one(img, i - 1, x, y, number);
	if ((pos = (i / img->cols)) < img->rows - 1 && img->data[pos] == 255)	find_one(img, i + img->cols, x, y, number);
	if ((pos = (i / img->cols)) > 0 && img->data[pos] == 255)				find_one(img, i - img->cols, x, y, number);
}


//	On va chercher tout les illo, et on gade que les plus gros ou les n plus gros.
//	on trvaille avec une image seuillee et sur un seul canal
t_surface *detect_surface(Mat img, int *nb_balls)
{
	int id = 0;
	int size = img.rows * img.cols;
	int x=0, y=0, number = 0;
	t_surface	*balls;

	*nb_balls = 0;
	balls = (t_surface*)malloc(sizeof(t_surface) * MAX_BALL);
	bzero(balls, sizeof(t_surface) * MAX_BALL);
	if (!balls)
		return (NULL);
//	cout << "************************************************************" << endl;
	for (int i = 0; i < size && id < MAX_BALL; ++i)
	{

		if (img.data[i] == 255)
		{
			cout << "x:" << (i % img.cols) << "	y:" << (i / img.cols) << endl;
			balls[id].x = 0;
			balls[id].y = 0;
			balls[id].size = 0;

			//On appel lafonctionqui conte les point concomitant, les efface et done surface + position;		
			find_one(&img, i, &(balls[id].x), &(balls[id].y), &(balls[id].size));
			balls[id].id= id;
			++id;
			*nb_balls += 1;
//*
			if (balls[id].size != 0)
			{
				cout << "==============================================================" << endl;
				cout << "number:	" << balls[id].size << endl;
				cout << "x:	" << (balls[id].x )<< endl;// / balls[id].size) << endl;
				cout << "y:	" << (balls[id].y )<< endl;// / balls[id].size) << endl;
			}
			else
			{
				cout << "size = 0" << endl;
			}
//*/
			
		}
	}
//	*nb_balls = id;
	cout << "########	nb_ball:" << *nb_balls << endl;
	return (balls);
	//	tan qu'on a pas fait tout l'image:
	//		-on cherche un point blanc, on cherche tout ceux quisont autour (recurtion ou truc avec des liste)
}
