#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

class HelloCV
{
public:
void test()
	{
	Mat img = imread("C:/Users/10545/Desktop/saber.jpg");
	imshow("test", img);
	waitKey(0);
	}
};

int main()
{
	Mat img = imread("C:/Users/10545/Desktop/saber.jpg");
	imshow("test", img);
	waitKey(0);
	return 0;
}