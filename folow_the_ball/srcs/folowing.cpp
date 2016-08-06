#include "folowing.hpp"



void	segfault_test(Mat img)
{
	int i = 0;

	while (i < img.cols * img.rows)
	{
		if (img.data[i] != 0)
		{
			img.data[i]= 70;
			cout << "	" << (int)img.data[i] ;//(int)img.data[i];
		}
//		img.data[i] = 100;
//		cout << "i:	" << i;
		++i;
	}
//	imshow("Grey Image", img); //show the thresholded image

}

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

int main( int argc, char** argv )
{
		bool			first = true;
		t_centre		*new_ball = NULL;
		t_centre		*old_ball = NULL;
		int				nb_ball = 0;
		char			key;
		VideoCapture	cap(1); //capture the video from webcam
		int				iLowH	= 50;
		int 			iHighH	= 83;
		int 			iLowS	= 67; 
		int 			iHighS	= 255;
		int 			iLowV	= 57;
		int 			iHighV	= 255;


		if ( !cap.isOpened() )  // if not success, exit program
		{
				cout << "Cannot open the web cam" << endl;
				return -1;
		}

		namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
//		namedWindow("Grey Image", CV_WINDOW_AUTOSIZE); //create a window called "Control"

		//Create trackbars in "Control" window
		createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
		createTrackbar("HighH", "Control", &iHighH, 179);

		createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
		createTrackbar("HighS", "Control", &iHighS, 255);

		createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
		createTrackbar("HighV", "Control", &iHighV, 255);

		int iLastX = -1; 
		int iLastY = -1;

		//Capture a temporary image from the camera
		Mat imgTmp;
		cap.read(imgTmp); 

		//Create a black image with the size as the camera output
		Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;


		while (true)
		{
				Mat imgOriginal;

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
				erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

				//morphological closing (removes small holes from the foreground)
				dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
				erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

/*
				//Calculate the moments of the thresholded image
				Moments oMoments = moments(imgThresholded);

				double dM01 = oMoments.m01;
				double dM10 = oMoments.m10;
				double dArea = oMoments.m00;

//				cout << imgThresholded << endl;	
//				cout << "dArea" << dArea << endl;
				// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
				if (dArea > 10000)
				{
						//calculate the position of the ball
						int posX = dM10 / dArea;
						int posY = dM01 / dArea;        

						if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
						{
								//Draw a red line from the previous point to the current point
								line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
						}

						iLastX = posX;
						iLastY = posY;
				}
//*/
				imshow("Thresholded Image", imgThresholded); //show the thresholded image

			//	segfault_test(imgThresholded);
				new_ball =  detect_surface_v2(imgThresholded, &nb_ball);

				//	Ici il faut redefinir les id, sauf pour lepremier passage
				if (!first)
				{
//					cout << "On est AL !!!!!!!!!!!!!!!!" << endl;
					redefine_id(new_ball, old_ball, nb_ball);
//					cout << "houhou 1" << endl;
					draw_lines(new_ball, old_ball, nb_ball, &imgLines);
//					cout << "houhou 2" << endl;
				}
				if (old_ball)
				{
					free(old_ball);
				}
				old_ball = new_ball;
				//	puis desiner les lignes avec des couleur differente
				//	on pourait aussi juste sesiner le squelette
				imgOriginal = imgOriginal + imgLines;
				imshow("Original", imgOriginal); //show the original image
				


				key = waitKey(30);
				if (key == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				{
						cout << "esc key is pressed by user" << endl;
						break; 
				}
//				cout << "nb_ball:" << nb_ball << endl;
				if (nb_ball > 0)
					first = false;
		}

		return 0;
}
