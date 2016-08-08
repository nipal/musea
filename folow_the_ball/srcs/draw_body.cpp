#include "folowing.hpp"

/*
	on va detecter d'abord le corp

	-il faut initialiser la detection:
		on place le cort dans une pausition
		on appuis sur une touche


	(1)-system de capture de position corporel
		(1.1)-key event
		(1.2)-sauvgarde dansun fichier
		(1.3)-lecture du fichier
		(1.4)-menu de selection
			1.4.1)-graphique
			(1.4.2)-console
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

void	draw_body(t_surface *zone)
{
	
}

