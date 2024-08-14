#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst1, dst2;
Point srcPts[4], dstPts[4], srcPts1[2];

void on_mouse(int event, int x, int y, int flags, void* userdata) {
	if(event == EVENT_LBUTTONDOWN) {
		srcPts[0] = Point(x, y);
		srcPts[1] = Point(x + src.cols - 1, y);
		srcPts[2] = Point(x, y + src.rows - 1);
		srcPts[3] = Point(x + src.cols - 1, y + src.rows - 1);
	}
	else if (event == EVENT_LBUTTONUP) {
		for (int i = 0; i < 4; i++) {
			dstPts[i] = srcPts[i];
		}
	}
	else if (event == EVENT_RBUTTONDOWN) {
		srcPts1[0] = Point(x, y);
	}
	else if (event == EVENT_RBUTTONUP) {
		srcPts1[1] = Point(x, y);
		int width = abs(srcPts1[0].x - srcPts1[1].x);
		int height = abs(srcPts1[0].y - srcPts1[1].y);
		
		Rect re(srcPts1[0], Size(width, height));
		Mat remat = src(re);
		
		resize(remat, dst2, Size(400,400),0,0,INTER_CUBIC);
		
		imshow("dst2", dst2);
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (flags & EVENT_FLAG_LBUTTON) {
			Mat M = Mat_<float>({ 2,3 }, { 1, 0, (float)x, 0, 1, (float)y });

			warpAffine(src, dst1, M, Size());

			imshow("src", dst1);
		}
	}
}

int main(void) {
	src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "fail" << endl;
		return -1;
	}

	srcPts[0] = Point(0, 0);
	srcPts[1] = Point(src.cols-1, 0);
	srcPts[2] = Point(0, src.rows-1);
	srcPts[3] = Point(src.cols-1, src.rows-1);

	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;
}