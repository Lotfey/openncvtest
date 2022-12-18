// OpenCV includes
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

//Functionalities includes
#include<iostream>


int main()
{

	// Set input data info
	std::string  PATH_TO_IMAGES = "standard_test_images/";
	std::string imageName = "lena_color_512.tif";
	
	//
	cv::Mat img = cv::imread(PATH_TO_IMAGES + imageName);

	// load cascade classifier
	cv::CascadeClassifier faceCascade;
	faceCascade.load(PATH_TO_IMAGES + "haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { std::cout << "model could not be loaded..." << std::endl; }

	// detect in boxing rectangle

	std::vector<cv::Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++)
	{
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);
	}

	//Display
	cv::imshow("original image", img);
	cv::waitKey(0);

	// detect the face from webCam input
	cv::VideoCapture capture(0);
	cv::Mat images;

	while (true)
	{
		capture.read(images);		
		faceCascade.detectMultiScale(images, faces, 1.1, 10);

		for (int i = 0; i < faces.size(); i++)
		{
			cv::rectangle(images, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 0), 3);
		}

		cv::imshow("detect faces", images);
		cv::waitKey(1);
	}
	
	return 0;

}