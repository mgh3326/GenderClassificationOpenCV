#include "preprocess.hpp"

Point2d calc_center(Rect obj)							// �簢�� �߽� ���	
{
	Point2d c = (Point2d)obj.size() / 2.0;
	Point2d center = (Point2d)obj.tl() + c;
	return center;
}

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");	// ���� �� �����
	load_cascade(eyes_cascade, "haarcascade_eye.xml");			// �� �����	

	Mat  image = imread("../face/oh.jpg", IMREAD_COLOR);	// �� ���� �ε�
	CV_Assert(image.data);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;

	Mat  gray = preprocessing(image);								// ��ó��
	face_cascade.detectMultiScale(gray, faces, 1.1, 4, 0, Size(0, 0));	// �� ����

	//if (faces.size() > 0)		// �� �簢�� ����Ǹ�
	for (int i = 0; i < faces.size(); i++)
	{	// �� ���� ����
		eyes_cascade.detectMultiScale(gray(faces[i]), eyes, 1.15, 2, 0, Size(0, 0));

		if (eyes.size() > 0)
		{							// �� �簢���� ����Ǹ�
			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point2d center = calc_center(eyes[j] + faces[i].tl());	// �߽��� ���
				circle(image, center, 5, Scalar(0, 255, 0), 2);	// �� �߽ɿ� �� �׸���
			}
			rectangle(image, faces[i], Scalar(255, 0, 0), 2);	// �� ���� �簢�� �׸���

		}
		else
		{
			rectangle(image, faces[i], Scalar(0, 0, 255), 2);	// �� ���� �簢�� �׸���

		}

	}

	imwrite("out5.jpg", image);

	//imshow("image", image);
	//waitKey();
	return 0;
}