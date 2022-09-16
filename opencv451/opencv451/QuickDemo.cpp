#include "quickopencv.h"

void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("HSV", hsv);
	imshow("�Ҷ�ͼƬ", gray);
	
	//imwrite("d:/hsv.png", hsv);
	//imwrite("d:/gray.png", gray);

}

void QuickDemo::mat_creation_demo() {
	Mat m1, m2, m3;
	m3 = Mat::zeros(Size(400, 400), CV_8UC3);
	m3 = Scalar(255, 0, 0);
	std::cout << "width=" << m3.cols << "  height=" << m3.rows << "  channels:" << m3.channels() << std::endl;
	//std::cout << m3 << std::endl;
	namedWindow("window", WINDOW_FREERATIO);
	imshow("M3",m3);

}

//ͼ�����صĶ�д����
void QuickDemo::pixel_visit_demo(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();	//ͨ����

	/*�����鷽ʽ���ʡ��޸�ͼƬÿ�����ص�ֵ
	for (int row = 0 ; row < h ; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {		//��ɫͼƬ
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {		//��ɫͼƬ
				Vec3b bgr = image.at<Vec3b>(row, col);		//��ȡ��ǰ���B��G��R��ֵ
				//image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				//image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				//image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
				if(bgr[0] >=100)
					image.at<Vec3b>(row, col)[0] -=55;
				
				image.at<Vec3b>(row, col)[1] =  bgr[1];
				image.at<Vec3b>(row, col)[2] =  bgr[2];
			}
		}
	}
	*/

	/*��ָ�뷽ʽ���ʡ��޸�ͼƬÿ�����ص�ֵ*/
	for (int row = 0 ; row < h ; row++) {
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {		//��ɫͼƬ
				int pv = *current_row;
				*current_row ++= 255 - pv;
			}
			if (dims == 3) {		//��ɫͼƬ
				*current_row++ = 255 - *current_row;	//��ֵB��ָ��+1,ָ��G
				*current_row++ = 255 - *current_row;	//��ֵG��ָ��+1,ָ��R
				*current_row++ = 255 - *current_row;	//��ֵR
			}
		}
	}
	
	imshow("���ض�дDEMO", image);
}

//ͼ�����ص���������
//saturate_cast<uchar>(a+b); ::������uchar��Χ��
void QuickDemo::operators_demo(Mat& image) {
	Mat dst;
	Mat m = Mat::zeros(image.size(), image.type());
	//dst = image - Scalar(50, 50, 50);		//ֱ�ӼӼ�������

	m = Scalar(2, 2, 2);
	multiply(image, m, dst);	//�˷�
	divide(image, m, dst);		//����
	add(image, m, dst);			//�ӷ�
	subtract(image, m, dst);	//����
	imshow("�ӷ�����", dst);
}

//TrackBar����������
Mat matSrc, matDst, m;
int lightness = 50;
static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	subtract(matSrc, m, matDst);
	imshow("���ȵ���", matDst);
}
void QuickDemo::trackbar_demo(Mat& image) {
	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	matDst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());
	matSrc = image;

	createTrackbar("Value Bar:", "���ȵ���", &lightness, max_value, on_track);
	on_track(50, 0);
}

static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	
	addWeighted(image, 1.0, m, 0.0, b, dst);
	imshow("������Աȶȵ���", dst);
}
static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("������Աȶȵ���", dst);
}

//TrackBar����������2
void QuickDemo::trackbar_demo2(Mat& image) {
	namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	int contrast_value = 100;
	
	createTrackbar("Value Bar:", "������Աȶȵ���", &lightness, max_value, on_lightness,(void*)(&image));
	createTrackbar("Contrast Bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}

//�����������ͼ�����
void  QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);	//��ȡ��������ֵ
		if (c == 27)			//����esc��27
			break;
		if (c == 49) { 
			std::cout << "you enter key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50) {
			std::cout << "you enter key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {
			std::cout << "you enter key #3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("KEY", dst);
	}

}

//��ɫ��������
void  QuickDemo::color_style_demo(Mat& image) {
	int colormap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};
	
	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(2000);
		if (c == 27)
			break;
		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		imshow("��ɫ���", dst);
	}
}

//ͼ�����ص��߼�����
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);

	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);	//-1Ϊ��䣬����Ϊ����
	//rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), 2, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(255, 0, 255), -1, LINE_8, 0);

	imshow("ͼ��1", m1);
	imshow("ͼ��2", m2);

	Mat dst;
	bitwise_and(m1, m2, dst);	//�����
	bitwise_or(m1, m2, dst);	//�����
	bitwise_not(image,dst);		//�ǲ���
	bitwise_xor(m1, m2, dst);	//������
	imshow("����λ����", dst);


}

//ͼ��ͨ������ͺϲ�
void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);
	imshow("��ɫͨ��", mv[0]);
	imshow("��ɫͨ��", mv[1]);
	imshow("��ɫͨ��", mv[2]);

	Mat dst;
	mv[0] = 0;				//ȥ����ɫͨ��
	//mv[1] = 0;
	merge(mv, dst);
	imshow("��ɫ", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("���»��ͨ��", dst);
}

//ͼ��ɫ�ʿռ�ת��
void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);

	Mat mask;		//�ɰ�
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
	//imshow("�ɰ�", mask);

	Mat redback = Mat::zeros(image.size(), image.type());	//���µ�ͼ�����
	redback = Scalar(40, 40, 200);							//�����ɫ
	bitwise_not(mask, mask);								//�ɰ淴ת����ת�ף��ױ��
	image.copyTo(redback, mask);							//����ɫ������ɰ淶Χ
	imshow("������ȡ", redback);

}

//ͼ������ֵͳ��
void  QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;
	Point minLoc, maxLoc;
	std::vector<Mat>mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {				//���ͼ����С�����ֵ��minMaxLocֻ�����ڼ���ͼ��
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		std::cout << "No.channels:" << i << " min value:" << minv << "max value:" << maxv << std::endl;
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	std::cout << "means:" << mean << std::endl;			//���ͼ���ֵ
	std::cout << "stddev:" << stddev << std::endl;		//���ͼ�񷽲�
}

//ͼ�񼸺�ͼ�λ���
void QuickDemo::drawing_demo(Mat& image) {		
	Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 250;
	rect.height = 300;
	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);							//����
	circle(bg, Point(350, 400), 15, Scalar(255, 0, 0), -1, 8, 0);				//Բ
	line(bg, Point(100, 100), Point(350, 400), Scalar(0, 255, 0), 4, 8, 0);		//��
	RotatedRect rrt;															//��Բ
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 66), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);
	imshow("������ʾ", dst);

}

//����������ͼ�����
void QuickDemo::random_drawing() {
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);
	while (true) {
		int c = waitKey(10);
		if (c == 27)
			break;
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w); 
		int y2 = rng.uniform(0, h); 
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		//canvas = Scalar(0, 0, 0);
		line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0);
		
		imshow("�������", canvas);

	}

}
static Point sp(-1, -1);
static Point ep(-1, -1);
Mat temp;
static void on_draw(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		std::cout << "��ʼ�㣺" << sp << std::endl;
		
	}
	else if(event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.x;
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(12, 12, 255), 2, 8, 0);
			imshow("������", image);
			imshow("ROI����", image(box));
			sp.x = -1;
			sp.y = -1;
		}
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.x;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(image);
				rectangle(image, box, Scalar(12, 12, 255), 2, 8, 0);
				
				imshow("������", image);
			}
		}
	}
	
}
void QuickDemo::mouse_demo(Mat &image) {
	namedWindow("������", WINDOW_AUTOSIZE);
	setMouseCallback("������", on_draw, (void*)(&image));
	imshow("������", image);
	temp = image.clone();

}

//��Ƶ�ļ�����ͷ
void QuickDemo::video_demo(Mat& image) {
	VideoCapture capture(0);		//������ͷ
	//VideoCapture capture("F:/opencv_tutorial_data-master/opencv_tutorial_data-master/images/example_dsh.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);		//��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);		//��
	int count = capture.get(CAP_PROP_FRAME_COUNT);				//֡
	double fps = capture.get(CAP_PROP_FPS);					//FPS
	std::cout << frame_width << "---" << frame_height << "---" << count << "---" << fps << std::endl;
	VideoWriter writer("D:/test.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);

	Mat frame;
	while (true) {
		capture.read(frame);
		flip(frame, frame, 1);
		if (frame.empty())
			break;

		imshow("frame", frame);
		colorSpace_Demo(frame);	
		writer.write(frame);		//������Ƶ
		int c = waitKey(10);
		if (c == 27)
			break;

	}
	capture.release();				//�ͷ���Դ
	writer.release();
}



