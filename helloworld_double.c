	
/*
 * Code written by Vinz (GeckoGeek.fr)
 */
 
#include <stdio.h>
#include "highgui.h"
#include "cv.h"
 
int main() {
 
	// Touche clavier
	char key;
	// Image
	IplImage *image_cam;
	IplImage *image_front;

	// Capture vidéo
	CvCapture *capture_front;
	CvCapture *capture_cam;
 
	// Ouvrir le flux vidéo
	//capture = cvCreateFileCapture("/path/to/your/video/test.avi"); // chemin pour un fichier
	//capture = cvCreateCameraCapture(CV_CAP_ANY);
	capture_cam = cvCreateCameraCapture(0);
	capture_front = cvCreateCameraCapture(1);
	//printf("cv number:%d", CV_CAP_ANY); 

	// Vérifier si l'ouverture du flux est ok
	if (!capture_cam)
	{
		printf("Ouverture du flux vidéo CAM impossible !\n");
		return 1; 
	}
 	// Vérifier si l'ouverture du flux est ok
	if (!capture_front)
	{
		printf("Ouverture du flux vidéo FRONT impossible !\n");
		return 1; 
	}

	// Définition de la fenêtre
	cvNamedWindow("Window cam", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Window front", CV_WINDOW_AUTOSIZE);
 
	// Boucle tant que l'utilisateur n'appuie pas sur la touche q (ou Q)
	while(key != 'q' && key != 'Q') {
 
		// On récupère une image
		image_cam = cvQueryFrame(capture_cam);
		image_front = cvQueryFrame(capture_front);
 
		// On affiche l'image dans une fenêtre
		cvShowImage( "Window cam", image_cam);
		cvShowImage( "Window front", image_front);
 
		// On attend 10ms
		key = cvWaitKey(50);
 
	}
 
	cvReleaseCapture(&capture_cam);
	cvDestroyWindow("Window cam");

	cvReleaseCapture(&capture_front);
	cvDestroyWindow("Window front");
 
	return 0;
 
}
