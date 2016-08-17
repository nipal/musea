#include "folowing.hpp"

void	Mat_tostring(Mat img)
{
	cout << "=================================================================================" << endl; 
	cout << "flags:	" << img.flags << endl;
	cout << "dims:	" << img.dims << endl;
	cout << "rows:	" << img.rows << endl;
	cout << "cols:	" << img.cols << endl;
	cout << "size:	" << img.size << endl;
	cout << "=================================================================================" << endl; 
}

void	line_reset(Mat *img, Mat imgTmp)
{
	(*img).release();
	*img = Mat::zeros( imgTmp.size(), CV_8UC3 );
}

//	il faut aussi faire une fonction pour recuperer la taille d'une image;
cv::Size	*get_imgSIze(cv::Size *data)
{
	static cv::Size *size = NULL;

	if (data != NULL)
	{
		size = data;
	}
	return (size);
}


//	On peut initialiser les 
Mat	*get_connexion(Mat *data)
{
	static Mat *connexion = NULL;

	if (data != NULL)
	{
		connexion = data;
	}
	return (connexion);
}

int main(void)
{
//	sound
	my_stk_init();
	RtWvOut	*dac = open_stream();
	SineWave	sine[MAX_BALL];
/*
	if (!(sine = (SineWave*)malloc(sizeof(SineWave) * MAX_BALL)))
	{
		cerr << "Malloc error (on sine)!" << endl;
		return (-1);
	}
*/
//	bzero();

	Mat				link;
	char			key;
	t_body_data		data;
	bool			first;
	t_centre		*new_ball;
	t_centre		*old_ball;
	VideoCapture	cap(1); //capture the video from webcam
	int nb_ball, iLowH,	iHighH, iLowS,	iHighS,	iLowV, iHighV;
	


	first = true;
	new_ball = NULL;
	old_ball = NULL;
	nb_ball = 0;
	iLowH	= 50;
	iHighH	= 90;
	iLowS	= 67; 
	iHighS	= 255;
	iLowV	= 90;
	iHighV	= 255;

	if ( !cap.isOpened() )  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}


    //conexion = (Mat_<bool>(MAX_BALL,MAX_BALL));


	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	namedWindow("Thresholded Image", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	namedWindow("Body", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	namedWindow("Grey Image", CV_WINDOW_AUTOSIZE); //create a window called "Control"


	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);


	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp); 

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );

	//	initialisation de la matrice de connexion
	link = Mat::zeros(cv::Size(MAX_BALL, MAX_BALL), CV_8UC3 );
	get_connexion(&link);

	setMouseCallback("Thresholded Image", CallBackFunc, &data);


//	Mat connexion = Mat::zeros( imgTmp.size(), CV_8UC3 );


	while (true)
	{

		Mat imgOriginal;
		Mat imgBody = Mat::zeros( imgTmp.size(), CV_8UC3 );

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video


		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(PRECISION, PRECISION)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(PRECISION, PRECISION)) ); 

		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(PRECISION, PRECISION)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(PRECISION, PRECISION)) );


		//	Detection des zone blanche
		new_ball =  detect_surface_v2(imgThresholded, &nb_ball);

	//	multi_sound();

		//	Ici il faut redefinir les id, sauf pour lepremier passage
		if (!first)
		{
			//	continuite avec les ball precedente
			swap_new(new_ball, old_ball);
			//	on dessine les lignes
			draw_lines(new_ball, old_ball, nb_ball, &imgLines);
			play_ball(dac, sine, new_ball);
//play_some(dac);
	//		losted_zone(new_ball, old_ball);
		}
		if (old_ball)
		{
			free(old_ball);
		}
		old_ball = new_ball;

		//	puis desiner les lignes avec des couleur differente
		//	on pourait aussi juste sesiner le squelette
		imgOriginal = imgOriginal + imgLines;
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image


		//	setMouseCallback("My Window", CallBackFunc, &imgThresholded);
		data.size = imgThresholded.size();
		data.zone = new_ball;
		data.img  = &imgThresholded;

		
		draw_body(new_ball, &imgBody);
		imshow("Body", imgBody); //show the thresholded image
		key = waitKey(TIME_INTERVAL);
		if (key == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break; 
		}
		else if (key == 'r' || key == 'R')
		{
			line_reset(&imgLines, imgTmp);
		}
		//		cout << "nb_ball:" << nb_ball << endl;
		if (nb_ball > 0)
			first = false;

		//		cv::Size size_img = imgThresholded.size();
		//		cout << "img_size:" << imgThresholded.size() << endl;  
		//		cout << "type_id:" << typeid(imgThresholded.size()) << endl;  
		//		cout << "type_name:" << typeid(imgThresholded.size()).name << endl;  
		imgOriginal.release();
		imgThresholded.release();
		imgHSV.release();
	}
	
//	close_sound(dac);
//	free(sine);

	return 0;
}


/*
On a un singleton qui donne acces alamatrice de connexion
a terme il faudrait faire une interface pour lancer les fenetre
*/
