// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>

int main()
{
	//set the min and max for HSV values
	int hmin = 0, smin = 0, vmin = 0;
	int hmax =179, smax = 255, vmax = 255;

	// Set input data info
	const std::string  PATH_TO_IMAGES = "standard_test_images/";
	const std::string imageName = "lena_color_512.tif";
	const std::string imageName2 = "peppers_color.tif";

	//read rgb image to test rgb to gray and bluring algorithms
	cv::Mat RGBImage = cv::imread(PATH_TO_IMAGES + imageName);
	cv::Mat paperRgbImage = cv::imread(PATH_TO_IMAGES + imageName2);

	// outputs
	cv::Mat grayImage, bluredImage, edgeImage, dilatedImage, erodedImage, resizedImage, cropedImage;
	cv::Mat imgHSV, mask;

	// rgb to gray
	cv::cvtColor(RGBImage, grayImage, cv::COLOR_BGR2GRAY);
	
	// gaussian filter
	cv::GaussianBlur(grayImage, bluredImage, cv::Size(3, 3), 5.0, 0.0);

	// canny filter, edge detection
	cv::Canny(grayImage, edgeImage, 35, 80);

	// dilate edges
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::dilate(edgeImage, dilatedImage, kernel);

	// erode
	cv::erode(edgeImage, erodedImage, kernel2);

	//resize an image 
	cv::resize(RGBImage, resizedImage, cv::Size(), 0.5, 0.5);

	//Cropped image
	cv::Rect cropMe2(cv::Point(100, 80), cv::Point(400, 400));
	//Equivalent syntax
	cv::Rect cropMe(100, 80, 400, 400);
	cropedImage = RGBImage(cropMe2);
	
	//Display
	cv::imshow("original image", RGBImage);
	cv::imshow("Gray image conversion", grayImage);
	cv::imshow("blured image", bluredImage);
	cv::imshow("edge detection", edgeImage);
	cv::imshow("Dilated Image", dilatedImage);
	cv::imshow("Eroded Image", erodedImage);
	cv::imshow("Resized Image", resizedImage);
	cv::imshow("croped Image", cropedImage);

	//v::waitKey(0);

	//rgb to hsv
	cv::cvtColor(paperRgbImage, imgHSV, cv::COLOR_BGR2HSV);
	cv::namedWindow("Track Bar for HSV image", (640, 200));

	cv::createTrackbar("Hue min: ", "Track Bar for HSV image", &hmin, hmax);
	cv::createTrackbar("Hue max: ", "Track Bar for HSV image", &hmax, hmax);

	cv::createTrackbar("Sat min: ", "Track Bar for HSV image", &smin, smax);
	cv::createTrackbar("Sat max: ", "Track Bar for HSV image", &smin, smax);

	cv::createTrackbar("Value min: ", "Track Bar for HSV image", &vmin, vmax);
	cv::createTrackbar("Value max: ", "Track Bar for HSV image", &vmin, vmax);


	while (true)

	{
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(imgHSV, lower, upper, mask);

		cv::imshow("Image", paperRgbImage);
		cv::imshow("Image HSV", imgHSV);
		cv::imshow("Image mask", mask);
		cv::waitKey(1);
	}


	return 0;
	//Looks fine so far ...
}