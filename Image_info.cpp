#include "pch.h"
#include "Image_info.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

//Image_info::Image_info(int layer_number, CString layer_name, CImage image)
//{
//	layer_num = layer_number;
//	this->layer_name = layer_name;
//	this->image = image;
//	originWidth = image.GetWidth();
//	originHeight = image.GetHeight();
//}

Image_info::Image_info()
{
}

Image_info::~Image_info()
{
}

void Image_info::SetValue(int layer_number, CString layer_name, Mat image)
{
	layer_num = layer_number;
	this->layer_name = layer_name;
	//this->image = image;


	//���� �̹����� 1�������� ������, 0�������� Ǫ�������� �̻��ϰԹٲ�
	//image.convertTo(image, CV_32FC3, 100/255.0);

	image.copyTo(this->image);
	//cv::cvtColor(this->image, this->image, cv::COLOR_BGR2RGBA);
		
	//originWidth = image.cols;
	//originHeight = image.rows;
	//�̹��� ũ�� �ٿ��� m_image�� �����ſ��� 
}

int Image_info::GetLayerNum()
{
	return this->layer_num;
}

CString Image_info::GetLayerName()
{
	return this->layer_name;
}

Mat Image_info::GetImage()
{
	return this->image;
}
