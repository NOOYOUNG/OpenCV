#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_contrast(int pos, void* userdata);
void contrast();

int main(void) {
	contrast();

	return 0;
}

void contrast() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load fail" << endl;
		return;
	}

	namedWindow("dst");
	createTrackbar("Contrast", "dst", 0, 10, on_contrast, (void*)&src);
	on_contrast(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void on_contrast(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;

	float alpha = float(pos) / 10.f;
	Mat dst = src + (src - 128) * alpha;

	String str = format("Alpha: %.1f", alpha);

	putText(dst, str, Point(0, 25), 0, 1, Scalar(0, 0, 0), 2);

	imshow("src", src);
	imshow("dst", dst);
}

/*#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_contrast(int pos, void* userdata);
void contrast();

int main(void) {
	contrast();

	return 0;
}

void contrast() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load fail" << endl;
		return;
	}	

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	namedWindow("dst");
	createTrackbar("Contrast", "dst", 0, 10, on_contrast, (void*)&src);
	on_contrast(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void on_contrast(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	float a = pos / 10.0;
	Mat dst;
	src.convertTo(dst, -1, a, 0);

	String str = format("Alpha: %.1f", a);
	putText(dst, str, Point(0, 25), 0, 1, Scalar(0, 0, 0), 2);

	imshow("dst", dst);
}*/