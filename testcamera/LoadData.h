
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <opencv2\core\core.hpp>
using namespace std;

int LoadData(string fileName, cv::Mat& matData, int matRows = 0, int matCols = 0, int matChns = 0)
{
	int retVal = 0;

	// 打开文件
	ifstream inFile(fileName.c_str(), ios_base::in);
	if (!inFile.is_open())
	{
		//读取文件失败
		cout << "failed to read the file" << endl;
		retVal = -1;
		return (retVal);
	}

	// 载入数据
	istream_iterator<float> begin(inFile);    //按 float 格式取文件数据流的起始指针
	istream_iterator<float> end;            //取文件流的终止位置
	vector<float> inData(begin, end);        //将文件数据保存至 std::vector 中
	cv::Mat tmpMat = cv::Mat(inData);        //将数据由 std::vector 转换为 cv::Mat

	// 输出到命令行窗口
	//copy(vec.begin(),vec.end(),ostream_iterator<double>(cout,"\t")); 

	// 检查设定的矩阵尺寸和通道数
	size_t dataLength = inData.size();
	//1.通道数
	if (matChns == 0)
	{
		matChns = 1;
	}
	//2.行列数
	if (matRows != 0 && matCols == 0)
	{
		matCols = dataLength / matChns / matRows;
	}
	else if (matCols != 0 && matRows == 0)
	{
		matRows = dataLength / matChns / matCols;
	}
	else if (matCols == 0 && matRows == 0)
	{
		matRows = dataLength / matChns;
		matCols = 1;
	}
	//3.数据总长度
	if (dataLength != (matRows * matCols * matChns))
	{
		//读入的数据长度 不满足 设定的矩阵尺寸与通道数要求，将按默认方式输出矩阵！
		cout << "length of the data doesn't satisfy the predefined matrix size, " << endl;
		retVal = 1;
		matChns = 1;
		matRows = dataLength;
	}

	// 将文件数据保存至输出矩阵
	matData = tmpMat.reshape(matChns, matRows).clone();

	return (retVal);
}