#include "folowing.cpp"

/*
	on	prend en photo une position et on s'ensert pour initialiser les conexion
	-capture body:
		--> zone
		--> matrice de connexion associer
	
	-representation grafique
	-cercle actif ou pas


	positionement des clercle de detection + definition des lien



	on exporte ca pour que ca puisse estre intereendure... ou je travaille avecles fichier
*/

/*
	La matrice de connexion c'est la cle de lecture des zone
*/
t_conex *save_position(t_centre *zone, Mat conexion)
{
	t_conex	*elem;

	if (!(elem = (t_conex*)malloc(sizeof(t_conex))))
	{
		cout << "ERROR ALLOCATION" << endl;
		return (NULL);
	} 
}

t_conex create_position()
{
	// Il faut pouvoir ajouter, suprimer des zone et les deplacer
	//
}
