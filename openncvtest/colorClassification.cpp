// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

//Functionalities includes
#include<iostream>

// get contour function signature, pass argument by reference to avoid copies
void getContour(cv::Mat& imgDil, cv::Mat& imgOut);


int main()
{
	// Set input data info	
	const std::string  PATH_TO_IMAGES = "standard_test_images/";
	const std::string imageName = "shapes.png";
	
	//read rgb image to test rgb to gray and bluring algorithms
	cv::Mat RGBImage = cv::imread(PATH_TO_IMAGES + imageName);	
	cv::Mat grayImage, blurredImage, cannyImage, dilatedImage, kernel;
	
	// preprocessing 
	cv::cvtColor(RGBImage, grayImage, cv::COLOR_BGR2GRAY);	
	cv::GaussianBlur(grayImage, blurredImage, cv::Size(3, 3), 3, 0);
	cv::Canny(blurredImage, cannyImage, 25, 75);

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


void getContour(cv::Mat& imgDil, cv::Mat& imgOut)
{
	std::vector<std::vector<cv::Point>> contour;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contour, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(imgOut, contour, -1, cv::Scalar(255, 0, 255), 3);

	// filter out small area if found 
	int area = 0;
	for (int i = 0; i < contour.size(); ++i)
	{
		area = cv::contourArea(contour[i]);
		std::cout << area << std::endl;

		std::vector<std::vector<cv::Point>>contourPoly(contour.size());
		std::vector<cv::Rect>boundRect(contour.size());
		std::string objectType;
		if (area > 1000)
		{
			//find the bounding box 
			float param = cv::arcLength(contour[i], true);
			cv::approxPolyDP(contour[i], contourPoly[i], 0.02 * param, true);
			//cv::drawContours(imgOut, contour, i, cv::Scalar(255, 0, 255), 3);
			cv::drawContours(imgOut, contourPoly, i, cv::Scalar(255, 0, 255), 3);
			std::cout<<contourPoly[i].size() << std::endl;

			boundRect[i]=cv::boundingRect(contourPoly[i]);
			cv::rectangle(imgOut, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(255, 0, 0),2);

			int objectCornors = static_cast<int>(contourPoly[i].size());
			
			if (objectCornors == 3) { objectType = "Tiangle"; }
			if (objectCornors == 4) { objectType = "rectanle"; }
			if (objectCornors == 5) { objectType = "polygone"; }
			if (objectCornors > 5 && objectCornors < 10) { objectType = "Star"; }
			if (objectCornors>  10) { objectType = "Circle"; }

			cv::putText(imgOut, objectType, { boundRect[i].x, boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(175, 175, 175), 1);


		}
		
	}
}