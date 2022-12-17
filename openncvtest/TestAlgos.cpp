// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>


int main()
{
	// Set input data info
	const std::string  PATH_TO_IMAGES = "standard_test_images/";
	const std::string imageName = "lena_color_512.tif";
	
	//read rgb image to test rgb to gray and bluring algorithms
	cv::Mat RGBImage=cv::imread(PATH_TO_IMAGES + imageName);

	// outputs
	 cv::Mat grayImage, bluredImage;

	 // rgb to gray
	 cv::cvtColor(RGBImage, grayImage, cv::COLOR_BGR2GRAY);

	// gaussian filter
	 cv::GaussianBlur(grayImage, bluredImage, cv::Size(3, 3), 5.0, 0.0);

	//Display
	cv::imshow("original image", RGBImage);
	cv::imshow("Gray image conversion", grayImage);
	cv::imshow("blured image", bluredImage);

	cv::waitKey(0);
	return 0;

	//Looks fine so far...
}