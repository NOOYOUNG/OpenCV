#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void camera_in() {
	VideoCapture cap(1);

	if (!cap.isOpened()) {
		cerr << "Camera open failed" << endl;
		return;
	}

	cout << "Frame Width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame Height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, faceFrame;
	while (true) {
		cap >> frame;
		
		if (frame.empty()) {
			cerr << "fail" << endl;
			return;
		}
		imshow("frame", frame);
		cvtColor(frame, faceFrame, COLOR_BGR2HSV);

		Scalar lowerb(0, 50, 80);
		Scalar upperb(30, 255, 255);
		
		Mat mask;
		inRange(faceFrame, lowerb, upperb, mask);
		bitwise_and(frame, frame, faceFrame, mask);

		Mat background = Mat::zeros(frame.size(), frame.type());

		frame.copyTo(background, mask);

		imshow("face recogizition", background);

		if (waitKey(10) == 27)
			break;
	}
	destroyAllWindows();
}

int main(void) {
	camera_in();
}