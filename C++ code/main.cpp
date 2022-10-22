#include <fstream>
#include <windows.h>  
#include <ctime>
#include <io.h>
#include "get_max_val_point.h"
using namespace std;

void read_data(const char* data_txt_path, double* x, double* y, double* z, double* t, int rows)
{
	int num = 0;
	std::ifstream data_txt(data_txt_path);
	std::string data_line;
	while (num <rows && data_txt >> data_line)
	{
		for (int col_id = 0; col_id < 4; col_id++)
		{
			string::size_type pos = data_line.find(",");
			if (pos != data_line.npos)
			{
				std::string data_str_ = data_line.substr(0, pos);
				data_line = data_line.substr(pos + 1, data_line.length() - pos - 1);
				if (col_id == 0)
				{
					x[num]= atof(data_str_.c_str());
				}
				else if (col_id == 1)
				{
					y[num] = atof(data_str_.c_str());
				}
				else if (col_id == 2)
				{
					z[num] = atof(data_str_.c_str());
				}
			}
			else {
				t[num] = atof(data_line.c_str());
			}
		}
		num += 1;
	}

}

int main()
{
	const char* data_txt_path = "D:\\Datasets\\origin\\���\\1.txt";
	if ((_access(data_txt_path, 0)) == -1)
	{
		cout << "txt�ļ�·�������ڣ������¼��·������" << endl;
		return 0;
	}
	int num_points = 125;
	int num_parameters = 10;
	double threshold = 0.8;
	//x,y,z����3��������������飬t����÷ֽ����ǩ
	double* x = new double[num_points]; double* y = new double[num_points]; double* z = new double[num_points]; double* t = new double[num_points];
	//x0_real_ptr,y0_real_ptr,z0_real_ptr����ֵ�������ָ��
	double* x0_real_ptr = new double; double* y0_real_ptr = new double; double* z0_real_ptr = new double;
	//��txt������ݶ������������ݸ���x, y, z, t��ȥ
	read_data(data_txt_path, x, y, z, t, num_points);
	clock_t startTime, endTime;
	startTime = clock();//��ʱ��ʼ
	//start = GetTickCount();
	//Sleep(1);
	//get_max_val_point������������:
	//x,y,z����3��������������飬t����÷ֽ����ǩ
	//num_points�����ж���������,���ﶼ��125
	//threshold����÷���ֵ��ֻ�е÷ֳ�������ֵ�����ݻ���Ϊ��Ч����������ϣ�С�ڵ������Ķ��ᱻ�޳��������������0.8
	//x0_real_ptr,y0_real_ptr,z0_real_ptr�������յõ��ļ�ֵ�������ֵ����ָ�봫�룬ִ����󱣴�ľ������ս��
	
	//result������û�м�����������������˾���true���м��л��ڳ�����û������������false
	bool result;
	result = get_max_val_point(x, y, z, t, num_points, threshold, num_parameters, x0_real_ptr, y0_real_ptr, z0_real_ptr);
	//for (int i = 0; i < 1000; i++)
	//{
	//	result = get_max_val_point(x, y, z, t, num_points, threshold, num_parameters, x0_real_ptr, y0_real_ptr, z0_real_ptr);
	//}
	
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime)/1000 / CLOCKS_PER_SEC << "s" << endl;
	if(result)
	{ 
		cout << "����ֵ��x:" << x0_real_ptr[0] << endl;
		cout << "����ֵ��y:" << y0_real_ptr[0] << endl;
		cout << "����ֵ��z:" << z0_real_ptr[0] << endl;
	}
	else
	{
		cout << "�󼫴�ֵ������л��ڳ������޷���ü���ֵ������" << endl;
	}
	delete[] x;delete[] y;delete[] z; delete[] t;
	delete x0_real_ptr; delete y0_real_ptr; delete z0_real_ptr;
	system("pause");
	return 0;
}