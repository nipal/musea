	
/*
 * Code written by Vinz (GeckoGeek.fr)
 */
 
#define DOUBLE_CAM 0

#include <stdio.h>
//#include <iostream.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "highgui.h"
#include "cv.h"


void	detect_circle(IplImage* image, char *name_window);

using namespace cv;
 
int main() {
/*

//*/
//*
	IplImage *image_front;
	CvCapture *capture_front;
	if (DOUBLE_CAM)
	{
		capture_front = cvCreateCameraCapture(0);
		if (!capture_front)
		{
			printf("Ouverture du flux vidéo FRONT impossible !\n");
			return 1; 
		}
		cvNamedWindow("Window front", CV_WINDOW_AUTOSIZE);
	}
//*/
	// Touche clavier
	char key;
	// Image
	IplImage *image_cam;

	// Capture vidéo
	CvCapture *capture_cam;
 
	// Ouvrir le flux vidéo
	//capture = cvCreateFileCapture("/path/to/your/video/test.avi"); // chemin pour un fichier
	//capture = cvCreateCameraCapture(CV_CAP_ANY);
	capture_cam = cvCreateCameraCapture(1);
	//printf("cv number:%d", CV_CAP_ANY); 

	// Vérifier si l'ouverture du flux est ok
	if (!capture_cam)
	{
		printf("Ouverture du flux vidéo CAM impossible !\n");
		return 1; 
	}
 	// Vérifier si l'ouverture du flux est ok


	// Définition de la fenêtre
	cvNamedWindow("Window cam", CV_WINDOW_AUTOSIZE);
 
	
	printf("debut de la boucle\n");
	// Boucle tant que l'utilisateur n'appuie pas sur la touche q (ou Q)
	while(key != 'q' && key != 'Q' && key != 27)
	{ 
		if (DOUBLE_CAM)
		{
			image_front = cvQueryFrame(capture_front);
			cvShowImage( "Window front", image_front);
		}


		// On récupère une image
		image_cam = cvQueryFrame(capture_cam);
 
		// On affiche l'image dans une fenêtre
		cvShowImage( "Window cam", image_cam);
 

		detect_circle(image_cam, strdup("Window cam"));
	
		// On attend 10ms
		key = cvWaitKey(100);
		printf("key:%d\n", key);
	} 
	printf("fin de la boucle\n");

	cvReleaseCapture(&capture_cam);
//	cvDestroyWindow("Window cam");
	cvDestroyAllWindows();

	if (DOUBLE_CAM) cvReleaseCapture(&capture_front);
//	cvDestroyWindow("Window front");
 
	return 0;
 
}

void	detect_circle(IplImage* image, char *name_window)
{
	IplImage *src =cvCloneImage(image);
dprintf(1, "petit debug des famille 1\n");
//	IplImage* image = cvLoadImage( "testing.bmp",CV_LOAD_IMAGE_GRAYSCALE);

//	IplImage* src = cvLoadImage("testing.bmp");
	CvMemStorage* storage = cvCreateMemStorage(0);

dprintf(1, "petit debug des famille 2\n");
///
	cvThreshold(src, src,  200, 255, CV_THRESH_BINARY );

dprintf(1, "petit debug des famille 3\n");
	CvSeq* results = cvHoughCircles(image, storage, CV_HOUGH_GRADIENT, 3, image->width/10); 

dprintf(1, "petit debug des famille 4\n");
	for( int i = 0; i < results->total; i++ ) 
	{
		float* p = (float*) cvGetSeqElem( results, i );
		CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
///
		cvCircle(src, pt, cvRound( p[2] ), CV_RGB(0xff,0,0));
	}
	cvNamedWindow( "HoughCircles", 1 );
dprintf(1, "petit debug des famille 5\n");
///
	cvShowImage( "HoughCircles", src);
dprintf(1, "petit debug des famille 6\n");
}


