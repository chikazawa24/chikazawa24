#include <iostream>

#include <C:/opencv/build/include/opencv2/imgproc.hpp>
#include <C:/opencv/build/include/opencv2/opencv_lib.hpp>
#include <C:/opencv/build/include/opencv2/opencv.hpp>
#include <C:/opencv/build/include/opencv2/highgui/highgui.hpp>



using namespace cv;
using namespace std;

int main(void)
{
	//映像の読み込み//

	uchar hue, sat, val; // Hue, Saturation, Valueを表現する変数
	Mat src_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // サイズを指定する
	Mat smooth_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // ノイズを除去した映像を保存する
	Mat hsv_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // HSVに変換した映像を保存する
	Mat frame(Size(640, 480), CV_8UC1, Scalar::all(255));
	Mat dst_img(Size(640, 480), CV_8UC1, Scalar::all(0)); // 認識結果を表示する

	/*
	cv::VideoWriter writer; // 動画ファイルを書き出すためのオブジェクトを宣言する
	int    width, height, fourcc; // 作成する動画ファイルの設定
	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // ビデオフォーマットの指定( ISO MPEG-4 / .mp4)
	double fps;
	width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);	// フレーム横幅を取得
	height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);	// フレーム縦幅を取得
	fps = video.get(cv::CAP_PROP_FPS);				// フレームレートを取得

	writer.open("CloneVideo.mp4", fourcc, fps, cv::Size(width, height));
	cv::Mat image;// 画像を格納するオブジェクトを宣言する
	while (1) {
		video >> image; // videoからimageへ1フレームを取り込む
		if (image.empty() == true) break; // 画像が読み込めなかったとき、無限ループを抜ける
		cv::imshow("showing", image); // ウィンドウに動画を表示する
		writer << image;  // 画像 image を動画ファイルへ書き出す
		if (cv::waitKey(1) == 'q') break; //qを押すと終了
	}
	return 0;*/

	
	char windowName[] = "!";
	namedWindow(windowName, WINDOW_AUTOSIZE);//表示ウィンドウの設定
	char hsvwindow[] = "HSV変換結果";
	namedWindow(hsvwindow, WINDOW_AUTOSIZE);
	char dstwindow[] = "認識結果";
	namedWindow(dstwindow, WINDOW_AUTOSIZE);

	// 動画ファイルのパスの文字列を格納するオブジェクトを宣言する
	std::string filepath = "C:/Users/81901/Desktop/研究室/Project1/wave.mp4";
	// 動画ファイルを取り込むためのオブジェクトを宣言する
	cv::VideoCapture capture;
	// 動画ファイルを開く
	capture.open(filepath);
	if (capture.isOpened() == false) {
		// 動画ファイルが開けなかったときは終了する
		return 0;
	}

	/*VideoCapture capture(0);
	// カメラが使えない場合はプログラムを止める
	if (!capture.isOpened())
		return -1;*/

	
	while (waitKey(1) == -1)
	{
		dst_img = Scalar::all(0);
		// カメラから1フレーム取得する
		do {
			capture >> frame;
		} while (frame.empty());

		src_video = frame;
		imshow(windowName, src_video);

		// HSV表色系へ色情報を変換
		// 先にノイズを消しておく
		medianBlur(src_video, smooth_video, 5);
		cvtColor(smooth_video, hsv_video, COLOR_BGR2HSV);
		imshow(hsvwindow, hsv_video);

		// H,S,Vの要素に分割する
		for (int y = 0; y < hsv_video.rows; y++) {
			for (int x = 0; x < hsv_video.cols; x++) {
				hue = hsv_video.at<Vec3b>(y, x)[0];
				sat = hsv_video.at<Vec3b>(y, x)[1];
				val = hsv_video.at<Vec3b>(y, x)[2];
				// 色の検出
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