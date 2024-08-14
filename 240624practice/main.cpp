#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void modified(Mat mat) {
	rectangle(mat, Rect(200, 430, 100, 100), Scalar(0, 0, 0), 3);

	putText(mat, "WATCH OUT!!!", Point(350, 480), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 0));
}

void video_in()
{
	VideoCapture cap("video.mov");

	if (!cap.isOpened()) {
		cout << "file open failed" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT));

	Mat frame;

	while (true) {
		cap.read(frame);
		if (frame.empty())
			break;

		modified(frame);

		imshow("Video", frame);
		resizeWindow("Video", 1200, 800);
		if (waitKey(10) == 27)
			break;
	}
}


int main()
{
	video_in();
}