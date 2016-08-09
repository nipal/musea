#include "folowing.hpp"

//	on fait un fonction qui sauvgarde les liens
//	on lui envoie deus id et la matrice de conexion
int	make_conexion(int id1, int id2)
{
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	static bool first = true;
	static int id1 = -1;
	static int id2 = -1;

	//	imshow("Test", *img); //show the original image
	//*img = Mat::zeros( imgTmp.size(), CV_8UC3 );
	t_body_data *data = (t_body_data*) userdata;

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
			}
		}
		else
		{
			cout << "dans le noir" << endl;
		}
	//	cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}

}

void	draw_body(t_surface *zone)
{
	
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
