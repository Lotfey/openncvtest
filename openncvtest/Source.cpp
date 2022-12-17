// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>


int main()
{ 
	// Set input data info
	std::string  PATH_TO_IMAGES= "standard_test_images/"; 
	std::string imageName= "cameraman.tif";
	
	// read images
	cv::Mat imgOrigin = cv::imread(PATH_TO_IMAGES+imageName);
	
	//Display
	imshow("original image of cameraman", imgOrigin);

	cv::waitKey(0);

	


	std::cout << "nothing" << std::endl;
	return 0;
}