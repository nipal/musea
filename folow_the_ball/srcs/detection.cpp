#include "folowing.hpp"


void	find_one(Mat *img, int i, int *x, int *y, int *number)
{
	int pos = 0;

	*number += 1;
	*x += i % img->cols;
	*y += i / img->cols;
	img->data[i] = 0;
	if ((pos = (i % img->cols)) < img->cols - 1 && img->data[pos] != 0)	find_one(img, i + 1, x, y, number);
	if ((pos = (i % img->cols)) > 0 && img->data[pos] != 0) 				find_one(img, i - 1, x, y, number);
	if ((pos = (i / img->cols)) < img->rows - 1 && img->data[pos] != 0)	find_one(img, i + img->cols, x, y, number);
	if ((pos = (i / img->cols)) > 0 && img->data[pos] != 0)				find_one(img, i - img->cols, x, y, number);
}


//	On va chercher tout les illo, et on gade que les plus gros ou les n plus gros.
//	on trvaille avec une image seuillee et sur un seul canal
t_surface *detect_surface(Mat img, int *nb_balls)
{
	int id = 0;
	int size = img.rows * img.cols;
	int x, y, number = 0;
	t_surface	*balls;

	balls = (t_surface*)malloc(sizeof(t_surface) * MAX_BALL);
	if (!balls)
		return (NULL);
//	cout << "************************************************************" << endl;
	for (int i = 0; i < size && id < MAX_BALL; ++i)
	{

		if (img.data[i] != 0)
		{
			//x = 0;
			//y = 0;
			//number = 0;
			//On appel lafonctionqui conte les point concomitant, les efface et done surface + position;		
			find_one(&img, i, &(balls[id].x), &(balls[id].y), &(balls[id].size));
			balls[id].id= id;
			++id;
/*
			cout << "==============================================================" << endl;
			cout << "x:	" << (x / number) << endl;
			cout << "y:	" << (y / number) << endl;
			cout << "number:	" << number << endl;
*/
			
		}
	}
	*nb_balls = id;
	return (balls);
	//	tan qu'on a pas fait tout l'image:
	//		-on cherche un point blanc, on cherche tout ceux quisont autour (recurtion ou truc avec des liste)
}
