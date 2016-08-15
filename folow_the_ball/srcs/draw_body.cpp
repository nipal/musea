#include "folowing.hpp"

//	on fait un fonction qui sauvgarde les liens
//	on lui envoie deus id et la matrice de conexion
void	make_conexion(int id1, int id2)
{
	Mat *link;

	link = get_connexion(NULL);

//	cout << "Mat connexion:"<< endl;
//	cout << *link << endl; 
	//si les indice ne sont pas bon on quit tout de suite
	if (id1 < 0 || id2 < 0)
	{
		cerr << "ERROR negativ id:	id1-->" << id1 << ", " << id2  << endl;
		return;
	}
	if (id1 >= MAX_BALL || id2 >= MAX_BALL)
	{
		cerr << "ERROR out of range:	id1-->" << id1 << "	id2-->" << id2  << endl;
		return;
	}
	if (id1 == id2)
	{
		cerr << "ERROR	same id	id1-->"<< id1 << "	id2-->" << id2  << endl;
		return;
	}
	if (link->data[id1 + MAX_BALL * id2] == 1 || link->data[id2 + MAX_BALL * id1] == 1)
	{
		//	on met tout a 0
		link->data[id2 + (MAX_BALL * id1)] = 0;
		link->data[id1 + (MAX_BALL * id2)] = 0;
		cout << "connexion destroy betwen "<< id1 << " and "<< id2 << endl;
	}
	else
	{
		// on les met a 1
		link->data[id2 + (MAX_BALL * id1)] = 1;
		link->data[id1 + (MAX_BALL * id2)] = 1;
		cout << "connexion creat betwen "<< id1 << " and "<< id2 << endl;
	}

//	cout << "Mat connexion:"<< endl;
//	cout << *link << endl; 
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	(void) flags;
	t_body_data *data;
	static bool first = true;
	static int id1 = -1;
	static int id2 = -1;

	data = (t_body_data*) userdata;
	//	imshow("Test", *img); //show the original image
	//*img = Mat::zeros( imgTmp.size(), CV_8UC3 );

//	Mat img = Mat::zeros( data->size, CV_8UC3 );
	if  ( event == EVENT_LBUTTONDOWN )
	{
		if (data->img->data[x + y * data->img->cols] == 255)	
		{
			cout << "dans le blanc" << endl;
			cout << "zone:" << closer_zone(x, y, data->zone) << endl;
			if (first)
			{
				first = !first;
				id1 = closer_zone(x, y, data->zone); 
			}
			else
			{
				first = !first;
				id2 = closer_zone(x, y, data->zone);
				make_conexion(id1, id2);
			}
		}
		else
		{
			cout << "dans le noir" << endl;
		}
	//	cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}

}

void	draw_body(t_centre *zone, Mat *imgBody)
{
	Mat *link;
	double x1, x2, y1, y2;

	link = get_connexion(NULL);
	//	On va passer par toutes les connexion possible, mais que la parite superrieur	
	for (int j = 0; j < MAX_BALL; j++)
	{
		for (int i = j; i < MAX_BALL; i++)
		{
			if (link->data[i + MAX_BALL * j] == 1)
			{
			//	cout << "linke found betwen " << i << " and "<< j << endl;
				if (zone[i].size > 0 && zone[j].size > 0) 
				{
				//	cout << "size is ok" << endl;
					x1 = zone[i].sum_x / zone[i].size;
					y1 = zone[i].sum_y / zone[i].size;
					x2 = zone[j].sum_x / zone[j].size;
					y2 = zone[j].sum_y / zone[j].size;
					line(*imgBody, Point(x1, y1), Point(x2, y2), Scalar(0,255, 255,255), 2);
				}
	//			else cout << "not inof size" << endl;
			}
		}
	}
}

/*
	on va detecter d'abord le corp

	-il faut initialiser la detection:
		on place le cort dans une pausition
		on appuis sur une touche

	(beta)
		tout sans sauvgarde

	(1)-system de capture de position corporel
		-key event
		-sauvgarde dansun fichier
		-lecture du fichier
		-menu de selection
			-graphique
			-console
	(2)-interface de selection du squelette
		-zone cliquable
		-multiligne
		-ctr+z/ctr+y
	(3)-zone de selection
		-keyevent
		-cercle assosier ou non
		-mis en relation
	(4)-dessin du squelette



	structure des position:
		-une matrice de vecteur: (x, y)
			-->on alenombre de point et leursposition

	structure des liaison:
		-une matrice des id et de leur conexion avec 0 lui meme, 1 ok -1 pas ok	
		Il faudra:	-->	definir une id pour tout les cercle d'origine
		 			-->	definir une corespondance entre les id d'origine et les nouvelle id avec la presencedansle cercle
					-->	on pourra allors construire une matrice de corespondance entre les id
*/


	/*
	else if  ( event == EVENT_RBUTTONDOWN )
	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if  ( event == EVENT_MBUTTONDOWN )
	{
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if ( event == EVENT_MOUSEMOVE )
	{
		      cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
	//*/
