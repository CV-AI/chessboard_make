#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    //单位转换
    int dot_per_inch = 96;  // dpi of computer (in ubuntu16.04, do "xdpyinfo | grep dot" to check)
    double cm_to_inch = 0.3937; //1cm=0.3937inch
    double inch_to_cm = 2.54;   //1inch = 2.54cm
    double inch_per_dot = 1.0 / 96.0;

    //自定义标定板
    double blockSize_cm = 2.5;
    int blockNum = 4; // number of blocks


    int blockSize = (int)(blockSize_cm /inch_to_cm *dot_per_inch); // blockSize(number of dots on screen)
    cout << blockSize << endl;

    int imageSize = blockSize * blockNum;
    cout << imageSize << endl;
    Mat chessBoard = cv::Mat::zeros(imageSize, imageSize, CV_8UC1);
    unsigned char color = 0;

    for (int i = 0; i < imageSize; i = i + blockSize){
        color = ~color;
        for (int j = 0; j < imageSize; j = j + blockSize){
            Mat ROI = chessBoard(Rect(i, j, blockSize, blockSize));
            ROI.setTo(Scalar::all(color));
            color = ~color;
        }
    }
    chessBoard.push_back(chessBoard);
    imshow("Chess board", chessBoard);
    imwrite("chessBoard.bmp",chessBoard);
    waitKey(3000);
    return 0;
}