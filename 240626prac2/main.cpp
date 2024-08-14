#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_algt(int pos, void* userdata) {
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "fail" << endl;
		return;
	}

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst = *(Mat*)userdata;

	float alpha = float(pos) / 10.f;
	addWeighted(src1, alpha, src2, 1 - alpha, 0, dst);

	String str = format("alpha: %.1f", alpha);
	putText(dst, str, Point(20, 20), 0, 1, Scalar(0, 0, 0), 1);

	imshow("dst", dst);
}

void algt() {
	Mat dst(400, 800, CV_8UC3);

	namedWindow("dst");
	createTrackbar("Weighted", "dst", 0, 10, on_algt, (void*)&dst);
	on_algt(0, (void*)&dst);

	waitKey();
	destroyAllWindows();
}

int main(void)
{
	algt();
}
