#include <opencv2/core/core.hpp>        // core���W���[���̃w�b�_�[���C���N���[�h
#include <opencv2/highgui/highgui.hpp>  // highgui���W���[���̃w�b�_�[���C���N���[�h
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <math.h>

int main(int argc, const char* argv[])
{
	HANDLE comPort;

	comPort = CreateFile(_T("COM5"),                //port name
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,                            // No Sharing
		NULL,                         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);        // Null for Comm Devices

	if (comPort == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port");
	else
		printf("opening serial port successful");

	DCB dcb; // �V���A���|�[�g�̍\����񂪓���\����
	GetCommState(comPort, &dcb); // ���݂̐ݒ�l��ǂݍ���

	dcb.BaudRate = 115200; // ���x
	dcb.ByteSize = 8; // �ʐM�f�[�^��
	dcb.Parity = NOPARITY; // �p���e�B
	dcb.StopBits = ONESTOPBIT; // �X�g�b�v�r�b�g��
	dcb.fOutxCtsFlow = FALSE; // �n�[�h�E�F�A�t���[���� ���M��CTS�t���[
	dcb.fOutX = FALSE; // �\�t�g�E�F�A�t���[���� ���M��XON/OFF����̗L��
	SetCommState(comPort, &dcb); // �ύX�����ݒ�l����������

	// ��320px�A����240px�ŐԐF�̉摜�f�[�^�𐶐�
	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));
	cv::Mat yellowImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 255, 255));

	// �摜�\���p�̃E�B���h�E�𐶐�
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	// �L�[���͂�ҋ@ frequency test
	DWORD numberOfPut;
	char sentData[2];
	DWORD lengthOfSent = 2; // ���M���镶����
	cv::imshow("red", redImg);
	sentData[0] = 0;
	sentData[1] = 0;

	int i,j;

	//�ؑւ̑��x�������ȈՓI�ɒ���
	int ajustmentNum = 20;//40
	//�������g��������
	int initialCountValue = 250 * ajustmentNum / 10;
	//���g���̊Ԋu�����߂�B1�グ���10Hz
	int interval = 10;//30
	int count = initialCountValue;
	while (1){
		
		/*WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // �|�[�g�֑��M
		for (i = 0; i < ajustmentNum; i++){
			WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // �|�[�g�֑��M

			count++;
			sentData[0] = count / ajustmentNum;
			sentData[1] = count / ajustmentNum;
			//���g���ō��l
			if (count >= 1100 * ajustmentNum / 10){
				//count = initialCountValue;
				count = 1100 * ajustmentNum / 10;
			}
		}
		count += ajustmentNum * (interval - 1);*/
		for (i = 50; i <= 110; i++){
			sentData[0] = i;
			sentData[1] = i;
			WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // �|�[�g�֑��M
			if (cv::waitKey(1) > 0){
				break;
			}
		}
		if (cv::waitKey(1) > 0){
			break;
		}

	}

	cv::imshow("red", yellowImg);
	sentData[0] = 0;
	sentData[1] = 25;
	//sentData[2] = '\0';
	//sentData = "0";
	while (1){
		WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // �|�[�g�֑��M
		if (cv::waitKey(1) > 0){
			break;
		}
	}

	CloseHandle(comPort);// Closing the Serial Port

	// 5�쐬�����E�B���h�E��S�Ĕj��
	cv::destroyAllWindows();

	return 0;
}
