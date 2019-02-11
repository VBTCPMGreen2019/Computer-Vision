#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <conio.h>

#define COLOR_ROWS 80
#define COLOR_COLS 250

using namespace std;
using namespace cv;

void on_mouse_click(int event, int x, int y, int flags, void* ptr) {
	if (event == EVENT_LBUTTONDOWN) {
		Mat* frame = (Mat*)ptr;
		Vec3b pixel = frame->at<Vec3b>(Point(x, y));
		int b, g, r;
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];
		string rgbText = "[" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + "]";

		float luminance = 1 - (0.299*r + 0.587*g + 0.114*b) / 255;
		Scalar textColor;
		if (luminance < 0.50) {
			textColor = Scalar(0, 0, 0);
		}
		else {
			textColor = Scalar(255, 255, 255);
		}
		Mat colorArray;
		colorArray = Mat(COLOR_ROWS, COLOR_COLS, CV_8UC3, Scalar(b, g, r));
		putText(colorArray, rgbText, Point2d(20, COLOR_ROWS - 20), FONT_HERSHEY_SIMPLEX, 0.8, textColor);
		imshow("Color", colorArray);
	}
}

int main(int argc, char** argv) {
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "Error opening VideoCapture." << endl;
		return -1;
	}

	Mat frame, colorArray;
	cap.read(frame);

	
	colorArray = Mat(COLOR_ROWS, COLOR_COLS, CV_8UC3, Scalar(0, 0, 0));
	imshow("Color", colorArray);

	int keyVal;
	while (1) {
		if (!cap.read(frame)) {
			break;
		}
		imshow("Video", frame);

		keyVal = waitKey(1) & 0xFF;
		if (keyVal == 81 or keyVal == 113) {
			break;
		}
		else {
			setMouseCallback("Video", on_mouse_click, &frame);
		}
	}
	return 0;
}