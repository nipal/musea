#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int		detect_circle(Mat src, Mat src_gray);

int main( int argc, char** argv )
{
		char key;
		VideoCapture cap(1); //capture the video from web cam

		if ( !cap.isOpened() )  // if not success, exit program
		{
				cout << "Cannot open the web cam" << endl;
				return -1;
		}

		namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

		int iLowH = 0;
		int iHighH = 179;

		int iLowS = 0; 
		int iHighS = 255;

		int iLowV = 0;
		int iHighV = 255;

		//Create trackbars in "Control" window
		cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
		cvCreateTrackbar("HighH", "Control", &iHighH, 179);

		cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
		cvCreateTrackbar("HighS", "Control", &iHighS, 255);

		cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
		cvCreateTrackbar("HighV", "Control", &iHighV, 255);

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


/*
				//morphological opening (remove small objects from the foreground)
				erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
				dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

				//morphological closing (fill small holes in the foreground)
				dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
				erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
*/

				imshow("Thresholded Image", imgThresholded); //show the thresholded image
				imshow("Original", imgOriginal); //show the original image

//				detect_circle(imgOriginal, imgThresholded);
				
				key = waitKey(30);
				if (key == 27 || key == 'q' || key == 'Q') //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				{
						cout << "esc key is pressed by user" << endl;
						break; 
				}
		}

		return 0;

}

int		detect_circle(Mat src, Mat src_gray)
{

		if(!src.data)
		{ return -1; }

		/// Convert it to gray
		cvtColor( src, src_gray, CV_BGR2GRAY );

		/// Reduce the noise so we avoid false circle detection
		GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

		vector<Vec3f> circles;

		/// Apply the Hough Transform to find the circles
		HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

		/// Draw the circles detected
		for( size_t i = 0; i < circles.size(); i++ )
		{
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				// circle center
				circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
				// circle outline
				circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

		/// Show your results
		namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
		imshow( "Hough Circle Transform Demo", src );

		//waitKey(0);
		return (0);
}
