#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void setLabel_minRect(Mat& img, const vector<Point>& pts) {
	RotatedRect rR = minAreaRect(pts);

	Point2f pts2[4];
	rR.points(pts2);
	for (int i = 0; i < 4; i++) {
		line(img, pts2[i], pts2[(i + 1) % 4], Scalar(255, 255, 255), 2);
	}
}

void setLabel_minCir(Mat& img, const vector<Point>& pts) {
	Point2f center;
	float radius;
	minEnclosingCircle(pts, center, radius);

	circle(img, center, radius, Scalar(255, 255, 255), 2);
}

int main(void) {
	Mat src = imread("keyboard.bmp", IMREAD_COLOR);
	Mat dst = imread("keyboard.bmp", IMREAD_COLOR);

	if (src.empty() || dst.empty()) {
		cerr << "fail" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);

	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>> contours;
	findContours(bin, contours, RETR_TREE, CHAIN_APPROX_NONE);


	for (vector<Point>& pts : contours) {
		if (contourArea(pts) < 30)
			continue;

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true) * 0.02, true);

		setLabel_minRect(src, pts);

		setLabel_minCir(dst, pts);
	}

	//Mat src1;
	//morphologyEx(src, src1, MORPH_CLOSE, Mat());
	//imshow("src1", src1);
	//Mat dst1;
	//morphologyEx(dst, dst1, MORPH_CLOSE, Mat());
	//imshow("dst1", dst1);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	return 0;
}