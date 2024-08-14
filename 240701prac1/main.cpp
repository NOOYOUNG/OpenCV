#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void hough_circle() {
	Mat src = imread("coinkor2.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "fail" << endl;
		return;
	}

	Mat blurred;
	blur(src, blurred, Size(3, 3));

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 350, 40);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);

		if (radius < 35) {
			circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
		}
		else if (radius < 40) {
			circle(dst, center, radius, Scalar(0, 255, 0), 2, LINE_AA);
		}
		else if (radius < 50) {
			circle(dst, center, radius, Scalar(255, 0, 0), 2, LINE_AA);
		}
	}

	putText(dst, "RED=10 GREEN=100 BLUE=500", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main(void) {
	hough_circle();
}