// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>


void getContour(cv::Mat& imgDil, cv::Mat& imgOut)
{
	std::vector<std::vector<cv::Point>> contour;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contour, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	cv::drawContours(imgOut, contour, -1, cv::Scalar(2055, 0, 255), 3);
}

int main()
{
	// Set input data info	
	const std::string  PATH_TO_IMAGES = "standard_test_images/";
	const std::string imageName = "shape.png";
	
	//read rgb image to test rgb to gray and bluring algorithms
	cv::Mat RGBImage = cv::imread(PATH_TO_IMAGES + imageName);
	cv::Mat grayImage, blurredImage, cannyImage, dilatedImage, kernel;
	
	// preprocessing 
	cv::cvtColor(RGBImage, grayImage, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(grayImage, blurredImage, cv::Size(3, 3), 3, 0);
	kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(cannyImage, dilatedImage, kernel);

	// get contour 
	
	getContour(dilatedImage, RGBImage);
	//Display
	cv::imshow("original image", RGBImage);
	cv::imshow("Gray image conversion", grayImage);
	cv::imshow("blured image", blurredImage);
	cv::imshow("edge detection", cannyImage);
	cv::imshow("Dilated Image", dilatedImage);
	cv::waitKey(0);






	return 0;
}