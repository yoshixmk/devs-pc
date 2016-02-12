#include "ColorTest.h"

namespace Test {

ColorTest::ColorTest() {
}

void ColorTest::twoImageSynthesisTest() {
	std::cout << "TwoImageSynthesis_test" << std::endl;
	Color::TwoImageSynthesis twoImageSynthesis;

//	cvNamedWindow("AllRound", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("NonDistortion", CV_WINDOW_AUTOSIZE);
	while(1)
	{
		Hardware::Camera::renew();
//		cvShowImage("AllRound", twoImageSynthesis.synthesize());
		cvShowImage("NonDistortion", twoImageSynthesis.synthesizeNonDistortion());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::hockeyTableMaskingTest() {
	std::cout << "HockeyTableMasking_test" << std::endl;
	Color::HockeyTableMasking hockeyTableMasking;

	cvNamedWindow("HockeyTableMacking", CV_WINDOW_AUTOSIZE);
	while (1) {
		Hardware::Camera::renew();
		cvShowImage("HockeyTableMacking", hockeyTableMasking.mask());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::robotSideHockeyTableMaskingTest()
{
	std::cout<<"RobotSideHockeyTableMasking_test"<<std::endl;
	Color::RobotSideHockeyTableMasking robotSideHockeyTableMasking;

	cvNamedWindow("RobotSideHockeyTableMasking", CV_WINDOW_AUTOSIZE);

	while(1)
	{
		Hardware::Camera::renew();
		cvShowImage("RobotSideHockeyTableMasking", robotSideHockeyTableMasking.mask());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::perspectiveTransformationTest()
{
	std::cout<<"PerspectiveTransformation_test"<<std::endl;
	Color::PerspectiveTransformation perspectiveTransformation;
	cvNamedWindow("PerspectiveTransformationR", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("PerspectiveTransformationH", CV_WINDOW_AUTOSIZE);
	IplImage* robotSideImage;
	IplImage* humanSideImage;
	while(1)
	{
		Hardware::Camera::renew();
		robotSideImage = perspectiveTransformation.transformRobotSideImage();
		humanSideImage = perspectiveTransformation.transformHumanSideImage();
		cvShowImage("PerspectiveTransformationR", robotSideImage);
		cvShowImage("PerspectiveTransformationH", humanSideImage);
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::colorExtractionTest()
{
	std::cout<<"ColorExtraction_test"<<std::endl;
	cvNamedWindow("ColorExtractionAll", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ColorExtractionRS", CV_WINDOW_AUTOSIZE);

	Color::ColorExtraction colorExtractionMallet;
	Color::ColorExtraction colorExtractionPack;
	colorExtractionMallet.setMalletHSV();
	colorExtractionPack.setPackHSV();

	int iSliderValuePack1 = 81; 
	cvCreateTrackbar("minH", "ColorExtractionAll", &iSliderValuePack1, 255);
	int iSliderValuePack2 = 88;
	cvCreateTrackbar("maxH", "ColorExtractionAll", &iSliderValuePack2, 255);
	int iSliderValuePack3 = 99;
	cvCreateTrackbar("minS", "ColorExtractionAll", &iSliderValuePack3, 255);
	int iSliderValuePack4 = 130;
	cvCreateTrackbar("maxS", "ColorExtractionAll", &iSliderValuePack4, 255);
	int iSliderValuePack5 = 0;
	cvCreateTrackbar("minV", "ColorExtractionAll", &iSliderValuePack5, 255);
	int iSliderValuePack6 = 130;
	cvCreateTrackbar("maxV", "ColorExtractionAll", &iSliderValuePack6, 255);
	//mallet threthold 0, 255, 100, 255, 140, 200
	int iSliderValuemallet1 = 13;
	cvCreateTrackbar("minH", "ColorExtractionRS", &iSliderValuemallet1, 255);
	int iSliderValuemallet2 = 44;
	cvCreateTrackbar("maxH", "ColorExtractionRS", &iSliderValuemallet2, 255);
	int iSliderValuemallet3 = 124;
	cvCreateTrackbar("minS", "ColorExtractionRS", &iSliderValuemallet3, 255);
	int iSliderValuemallet4 = 255;
	cvCreateTrackbar("maxS", "ColorExtractionRS", &iSliderValuemallet4, 255);
	int iSliderValuemallet5 = 110;
	cvCreateTrackbar("minV", "ColorExtractionRS", &iSliderValuemallet5, 255);
	int iSliderValuemallet6 = 174;
	cvCreateTrackbar("maxV", "ColorExtractionRS", &iSliderValuemallet6, 255);

	Color::HockeyTableMasking hockeyTableMasking;
	//cvNamedWindow("HockeyTableMacking", CV_WINDOW_AUTOSIZE);
	//Hardware::Timer timer;
	//double passedTime;
	while(1)
	{
		//passedTime = 0;
		//for(int i=0; i<100; i++){
		//timer.resetStartOperatingTime();
		
		Hardware::Camera::renew();
		colorExtractionPack.setHSV(iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);
		colorExtractionMallet.setHSV(iSliderValuemallet1, iSliderValuemallet2, iSliderValuemallet3, iSliderValuemallet4, iSliderValuemallet5, iSliderValuemallet6);
		cvShowImage("ColorExtractionAll", colorExtractionPack.extractHockeyTable());
		cvShowImage("ColorExtractionRS", colorExtractionMallet.extractRobotSideHockeyTable());
		//cvShowImage("HockeyTableMacking", hockeyTableMasking.mask());
		if(cv::waitKey(1) >= 0) {
			break;
		}

			//passedTime += timer.getOperatingTime();
		//}
		//std::cout << passedTime/100 << std::endl;
	}
}

void ColorTest::nonFlipTwoImageSynthesisTest()
{
	std::cout << "NonFlip_TwoImageSynthesis_test" << std::endl;
	Color::NonFlipTwoImageSynthesis nonFlipTwoImageSynthesis;

	while(1)
	{
		Hardware::Camera::renew();
		cvShowImage("SynthesisImage", nonFlipTwoImageSynthesis.synthesizeNonDistortion());
		//cvSaveImage("../output2.jpg", nonFlipTwoImageSynthesis.synthesizeNonDistortion());
		if (cv::waitKey(1) >= 0) {
			break;
		}
		//int param[]={CV_IMWRITE_JPEG_QUALITY,100};
		//cvSaveImage("../output.jpg", nonFlipTwoImageSynthesis.synthesizeNonDistortion(), param);
		
	}
}

void ColorTest::cameraMovieSaveTest()
{
	std::cout << "NonFlip_TwoImageSynthesis_test" << std::endl;
	Color::NonFlipTwoImageSynthesis nonFlipTwoImageSynthesis;
	CvVideoWriter *vw;
	vw = cvCreateVideoWriter ("../../cap.avi", CV_FOURCC('D', 'I', 'B', ' '), 60, cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()*2), 1);
	IplImage* ipl;
	while(1)
	{
		Hardware::Camera::renew();
		ipl = nonFlipTwoImageSynthesis.synthesizeNonDistortion();
		cvShowImage("SynthesisImage", ipl);
		cvWriteFrame (vw, ipl);
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
	cvReleaseVideoWriter(&vw);
}

} /* namespace Test */
