#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;

class QuickDemo {
public:
	void colorSpace_Demo(Mat& image);
	void mat_creation_demo();
	void pixel_visit_demo(Mat& image);		//ͼ�����صĶ�д����
	void operators_demo(Mat& image);		//ͼ�����ص���������
	void trackbar_demo(Mat& image);			//TrackBar����������
	void trackbar_demo2(Mat& image);
	void key_demo(Mat& image);				//�����������ͼƬ����
	void color_style_demo(Mat& image);		//��ɫ��������
	void bitwise_demo(Mat& image);			//ͼ�����ص��߼�����
	void channels_demo(Mat& image);			//ͼ��ͨ������ͺϲ�
	void inrange_demo(Mat& image);			//ͼ��ɫ�ʿռ�ת��
	void pixel_statistic_demo(Mat& image);	//ͼ������ֵͳ��
	void drawing_demo(Mat& image);			//ͼ�񼸺�ͼ�λ���
	void random_drawing();					//����������ͼ�����
	void mouse_demo(Mat& image);						//�����Ӧ

	void video_demo(Mat& image);
};