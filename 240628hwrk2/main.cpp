#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Point srcPts[4], dstPts[4];

int main(void) {
	Mat src = imread("tekapo.bmp");

	if (src.empty()) {
		cerr << "fail" << endl;
		return -1;
	}

	srcPts[0] = Point(0, 0);
	srcPts[1] = Point(src.cols - 1, 0);
	srcPts[2] = Point(0, src.rows - 1);
	srcPts[3] = Point(src.cols - 1, src.rows - 1);

	Point cp(src.cols / 2, src.rows / 2);

	for (int angle = 0; angle <= 360; angle++) {
		Mat M = getRotationMatrix2D(cp, angle, 1);

		Mat dst;
		warpAffine(src, dst, M, Size());

		if (src.cols < 0) {
			src.cols = 0;
		}
		imshow("dst", dst);
		waitKey();
		/*dstPts[0]=
		dstPts[1]=
		dstPts[2]=
		dstPts[3]=*/
	}

	destroyAllWindows();
	return 0;
}