#include"preprocess.h"

void preProcess(const Mat& srcImage, Mat& dstImage)
{
	Mat tmpImage = srcImage.clone();
	if (tmpImage.type() != CV_8UC1)
	{
		cvtColor(tmpImage, tmpImage, CV_BGR2GRAY);
	}
	//高斯滤波预处理噪点
	GaussianBlur(tmpImage, tmpImage, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//形态学滤波 开运算预处理
	Mat element = getStructuringElement(MORPH_RECT, Size(7,7));
	morphologyEx(tmpImage, tmpImage, MORPH_OPEN, element);

	//imshow("fff", tmpImage);
	//waitKey(500);
	
	//canny提取边沿
	Canny(tmpImage, dstImage, 75, 100, 3);
	//imshow("qq", dstImage);
	//waitKey(500);
	//形态学滤波，闭运算终处理
	Mat tmpImage4 = dstImage.clone();
	element = getStructuringElement(MORPH_RECT, Size(10, 10));
	morphologyEx(dstImage, tmpImage4, MORPH_DILATE, element);

	//imshow("hhh", tmpImage4);
	//waitKey(500);

	threshold(tmpImage4, dstImage, 0, 255, THRESH_OTSU + THRESH_BINARY);

	//imshow("hhh2", dstImage);
	//waitKey(0);
}