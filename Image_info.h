#pragma once
#include <atlimage.h>

#include <opencv2/core.hpp>

using namespace cv;

class Image_info
{
public:
	Image_info();
	~Image_info();
	void SetValue(int layer_number, CString layer_name, Mat image);
	int GetLayerNum();
	CString GetLayerName();
	Mat GetImage();

private :
	int layer_num;
	CString layer_name;

public:
	Mat image;
	int originWidth;
	int originHeight;

	double opacity;
	CPoint location; // �ٵ� ��¥�� 00���� �׷��� �����մ����𸣰���

};

