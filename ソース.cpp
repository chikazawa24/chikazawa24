#include <iostream>

#include <C:/opencv/build/include/opencv2/imgproc.hpp>
#include <C:/opencv/build/include/opencv2/opencv_lib.hpp>
#include <C:/opencv/build/include/opencv2/opencv.hpp>
#include <C:/opencv/build/include/opencv2/highgui/highgui.hpp>



using namespace cv;
using namespace std;

int main(void)
{
	//�f���̓ǂݍ���//

	uchar hue, sat, val; // Hue, Saturation, Value��\������ϐ�
	Mat src_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // �T�C�Y���w�肷��
	Mat smooth_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // �m�C�Y�����������f����ۑ�����
	Mat hsv_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // HSV�ɕϊ������f����ۑ�����
	Mat frame(Size(640, 480), CV_8UC1, Scalar::all(255));
	Mat dst_img(Size(640, 480), CV_8UC1, Scalar::all(0)); // �F�����ʂ�\������

	/*
	cv::VideoWriter writer; // ����t�@�C���������o�����߂̃I�u�W�F�N�g��錾����
	int    width, height, fourcc; // �쐬���铮��t�@�C���̐ݒ�
	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // �r�f�I�t�H�[�}�b�g�̎w��( ISO MPEG-4 / .mp4)
	double fps;
	width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);	// �t���[���������擾
	height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);	// �t���[���c�����擾
	fps = video.get(cv::CAP_PROP_FPS);				// �t���[�����[�g���擾

	writer.open("CloneVideo.mp4", fourcc, fps, cv::Size(width, height));
	cv::Mat image;// �摜���i�[����I�u�W�F�N�g��錾����
	while (1) {
		video >> image; // video����image��1�t���[������荞��
		if (image.empty() == true) break; // �摜���ǂݍ��߂Ȃ������Ƃ��A�������[�v�𔲂���
		cv::imshow("showing", image); // �E�B���h�E�ɓ����\������
		writer << image;  // �摜 image �𓮉�t�@�C���֏����o��
		if (cv::waitKey(1) == 'q') break; //q�������ƏI��
	}
	return 0;*/

	
	char windowName[] = "!";
	namedWindow(windowName, WINDOW_AUTOSIZE);//�\���E�B���h�E�̐ݒ�
	char hsvwindow[] = "HSV�ϊ�����";
	namedWindow(hsvwindow, WINDOW_AUTOSIZE);
	char dstwindow[] = "�F������";
	namedWindow(dstwindow, WINDOW_AUTOSIZE);

	// ����t�@�C���̃p�X�̕�������i�[����I�u�W�F�N�g��錾����
	std::string filepath = "C:/Users/81901/Desktop/������/Project1/wave.mp4";
	// ����t�@�C������荞�ނ��߂̃I�u�W�F�N�g��錾����
	cv::VideoCapture capture;
	// ����t�@�C�����J��
	capture.open(filepath);
	if (capture.isOpened() == false) {
		// ����t�@�C�����J���Ȃ������Ƃ��͏I������
		return 0;
	}

	/*VideoCapture capture(0);
	// �J�������g���Ȃ��ꍇ�̓v���O�������~�߂�
	if (!capture.isOpened())
		return -1;*/

	
	while (waitKey(1) == -1)
	{
		dst_img = Scalar::all(0);
		// �J��������1�t���[���擾����
		do {
			capture >> frame;
		} while (frame.empty());

		src_video = frame;
		imshow(windowName, src_video);

		// HSV�\�F�n�֐F����ϊ�
		// ��Ƀm�C�Y�������Ă���
		medianBlur(src_video, smooth_video, 5);
		cvtColor(smooth_video, hsv_video, COLOR_BGR2HSV);
		imshow(hsvwindow, hsv_video);

		// H,S,V�̗v�f�ɕ�������
		for (int y = 0; y < hsv_video.rows; y++) {
			for (int x = 0; x < hsv_video.cols; x++) {
				hue = hsv_video.at<Vec3b>(y, x)[0];
				sat = hsv_video.at<Vec3b>(y, x)[1];
				val = hsv_video.at<Vec3b>(y, x)[2];
				// �F�̌��o
				if ((hue < 35 && hue > 20) && sat > 127) {
					dst_img.at<uchar>(y, x) = 255;
				}
				else {
					dst_img.at<uchar>(y, x) = 0;
				}
			}
		}
		imshow(dstwindow, dst_img);
	}
	destroyAllWindows();
	return 0;
}