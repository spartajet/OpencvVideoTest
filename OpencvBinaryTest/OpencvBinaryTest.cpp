#include "opencv2/core.hpp"
#include <opencv2/core/types_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		printf("open video failed!\n");
		return 1;
	}

	Mat frame;
	fstream fs;
	fs.open("test1.vdi", ios::in | ios::out | ios::binary | ios::trunc);

	//设置保存的视频帧数目
	int frame_num = 100;
	//保存视频的路径
	// const string output_video_path = "test.avi";
	//获取当前摄像头的视频信息
	const cv::Size s_wh = cv::Size(static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)),
	static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)));
	// VideoWriter output_video;
	// output_video.open(output_video_path, output_video.fourcc('M', 'P', '4', '2'), 25.0, s_wh, false);
	const int channel = 1;
	const int bits = 16;
	fs.write((char*)&s_wh.height, sizeof(int));    // rows
	fs.write((char*)&s_wh.width, sizeof(int));    // cols
	fs.write((char*)&bits, sizeof(int));        // type
	fs.write((char*)&channel, sizeof(int));    // channels
	if (cap.isOpened())
	{
		for (int i = 0; i < 1500; ++i)
		{
			cap >> frame;
			cvtColor(frame, frame, CV_RGB2GRAY);
			frame.convertTo(frame, CV_16UC1);
			normalize(frame, frame, 0, 256 * 256, NORM_MINMAX);
			// cvConvertScale(&frame, &frame, 1 / 255);
			int type = frame.type();
			// Data
			if (frame.isContinuous())
			{
				fs.write(frame.ptr<char>(0), (frame.dataend - frame.datastart));
			}
			else
			{
				int rowsz = CV_ELEM_SIZE(type) * frame.cols;
				for (int r = 0; r < frame.rows; ++r)
				{
					fs.write(frame.ptr<char>(r), rowsz);
				}
			}
		}
	}
	cap.release();
	fs.close();


	// while (cap.isOpened() && frame_num > 0)
	// {
	// 	cap >> frame;
	// 	if (frame.empty()) break;
	// 	// cvtColor(frame, frame, CV_RGB2GRAY);
	// 	// cvConvertScale(frame, frame, 1 / 255);
	// 	frame.convertTo(frame, CV_16UC3);
	// 	normalize(frame, frame, 0, 256 * 256, NORM_MINMAX);
	// 	cvtColor(frame, frame, CV_RGB2GRAY);
	// 	output_video << frame;
	// 	frame_num--;
	//
	// 	imshow("img", frame);
	// 	waitKey(10);
	//
	// 	if (char(waitKey(1)) == 'q') break;
	// }
	//
	// output_video.release();
	// system("pause");
	return 0;
}
