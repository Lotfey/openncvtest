// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>


int main()
{ 
	std::string  PATH_TO_IMAGES= "standard_test_images/"; 
	std::string imageName= "cameraman.tif";
	cv::Mat imgOrigin = cv::imread(PATH_TO_IMAGES+imageName);
	imshow("original image of cameraman", imgOrigin);

	cv::waitKey(0);

	


	std::cout << "nothing" << std::endl;
	return 0;
}