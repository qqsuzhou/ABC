#include "quickopencv.h"

void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//imshow("HSV", hsv);
	imshow("灰度图片", gray);
	
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

//图像像素的读写操作
void QuickDemo::pixel_visit_demo(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();	//通道数

	/*用数组方式访问、修改图片每个像素的值
	for (int row = 0 ; row < h ; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {		//灰色图片
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {		//彩色图片
				Vec3b bgr = image.at<Vec3b>(row, col);		//获取当前点的B、G、R的值
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

	/*用指针方式访问、修改图片每个像素的值*/
	for (int row = 0 ; row < h ; row++) {
		uchar* current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {		//灰色图片
				int pv = *current_row;
				*current_row ++= 255 - pv;
			}
			if (dims == 3) {		//彩色图片
				*current_row++ = 255 - *current_row;	//赋值B，指针+1,指向G
				*current_row++ = 255 - *current_row;	//赋值G，指针+1,指向R
				*current_row++ = 255 - *current_row;	//赋值R
			}
		}
	}
	
	imshow("像素读写DEMO", image);
}

//图像像素的算术操作
//saturate_cast<uchar>(a+b); ::限制在uchar范围内
void QuickDemo::operators_demo(Mat& image) {
	Mat dst;
	Mat m = Mat::zeros(image.size(), image.type());
	//dst = image - Scalar(50, 50, 50);		//直接加减法处理

	m = Scalar(2, 2, 2);
	multiply(image, m, dst);	//乘法
	divide(image, m, dst);		//除法
	add(image, m, dst);			//加法
	subtract(image, m, dst);	//减法
	imshow("加法操作", dst);
}

//TrackBar滚动条操作
Mat matSrc, matDst, m;
int lightness = 50;
static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	subtract(matSrc, m, matDst);
	imshow("亮度调整", matDst);
}
void QuickDemo::trackbar_demo(Mat& image) {
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	int max_value = 100;
	matDst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());
	matSrc = image;

	createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);
	on_track(50, 0);
}

static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	
	addWeighted(image, 1.0, m, 0.0, b, dst);
	imshow("亮度与对比度调整", dst);
}
static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("亮度与对比度调整", dst);
}

//TrackBar滚动条操作2
void QuickDemo::trackbar_demo2(Mat& image) {
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	int contrast_value = 100;
	
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness,(void*)(&image));
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}

//键盘输入调整图像操作
void  QuickDemo::key_demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);	//获取键盘输入值
		if (c == 27)			//输入esc，27
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

//颜色调整操作
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
		imshow("颜色风格", dst);
	}
}

//图像像素的逻辑运算
void QuickDemo::bitwise_demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);

	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);	//-1为填充，正数为绘制
	//rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), 2, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(255, 0, 255), -1, LINE_8, 0);

	imshow("图像1", m1);
	imshow("图像2", m2);

	Mat dst;
	bitwise_and(m1, m2, dst);	//与操作
	bitwise_or(m1, m2, dst);	//或操作
	bitwise_not(image,dst);		//非操作
	bitwise_xor(m1, m2, dst);	//异或操作
	imshow("像素位操作", dst);


}

//图像通道分离和合并
void QuickDemo::channels_demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);
	imshow("蓝色通道", mv[0]);
	imshow("绿色通道", mv[1]);
	imshow("红色通道", mv[2]);

	Mat dst;
	mv[0] = 0;				//去掉蓝色通道
	//mv[1] = 0;
	merge(mv, dst);
	imshow("红色", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("重新混合通道", dst);
}

//图像色彩空间转换
void QuickDemo::inrange_demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);

	Mat mask;		//蒙版
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);
	//imshow("蒙版", mask);

	Mat redback = Mat::zeros(image.size(), image.type());	//建新的图像对象
	redback = Scalar(40, 40, 200);							//填入红色
	bitwise_not(mask, mask);								//蒙版反转，黑转白，白变黑
	image.copyTo(redback, mask);							//将红色填充入蒙版范围
	imshow("区域提取", redback);

}

//图像像素值统计
void  QuickDemo::pixel_statistic_demo(Mat& image) {
	double minv, maxv;
	Point minLoc, maxLoc;
	std::vector<Mat>mv;
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {				//输出图层最小和最大值，minMaxLoc只能用于计算图层
		minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
		std::cout << "No.channels:" << i << " min value:" << minv << "max value:" << maxv << std::endl;
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	std::cout << "means:" << mean << std::endl;			//输出图像均值
	std::cout << "stddev:" << stddev << std::endl;		//输出图像方差
}

//图像几何图形绘制
void QuickDemo::drawing_demo(Mat& image) {		
	Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 250;
	rect.height = 300;
	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);							//矩形
	circle(bg, Point(350, 400), 15, Scalar(255, 0, 0), -1, 8, 0);				//圆
	line(bg, Point(100, 100), Point(350, 400), Scalar(0, 255, 0), 4, 8, 0);		//线
	RotatedRect rrt;															//椭圆
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 66), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);
	imshow("绘制演示", dst);

}

//随机数与随机图像绘制
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
		
		imshow("随机绘制", canvas);

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
		std::cout << "起始点：" << sp << std::endl;
		
	}
	else if(event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.x;
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			rectangle(image, box, Scalar(12, 12, 255), 2, 8, 0);
			imshow("鼠标绘制", image);
			imshow("ROI区域", image(box));
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
				
				imshow("鼠标绘制", image);
			}
		}
	}
	
}
void QuickDemo::mouse_demo(Mat &image) {
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
	imshow("鼠标绘制", image);
	temp = image.clone();

}

//视频文件摄像头
void QuickDemo::video_demo(Mat& image) {
	VideoCapture capture(0);		//打开摄像头
	//VideoCapture capture("F:/opencv_tutorial_data-master/opencv_tutorial_data-master/images/example_dsh.mp4");

	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);		//宽
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);		//高
	int count = capture.get(CAP_PROP_FRAME_COUNT);				//帧
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
		writer.write(frame);		//保存视频
		int c = waitKey(10);
		if (c == 27)
			break;

	}
	capture.release();				//释放资源
	writer.release();
}



