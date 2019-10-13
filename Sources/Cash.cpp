
#include <iostream>
#include <chrono>
#include <vector>

#undef RAND_MAX
#define RAND_MAX 4 * 1024 * 1024

using namespace std;
struct Report
{
	int64_t directTime;
	int64_t reversTime;
	int64_t randomTime;
	int size;
public:
	void setDT(int64_t setTime)
	{
		this->directTime = setTime;
	}
	void setRevT(int64_t setTime)
	{
		this->reversTime = setTime;
	}
	void setRandT(int64_t setTime)
	{
		this->randomTime = setTime;
	}
	void setSize(int64_t size)
	{
		this->size = size;
	}
	int64_t getDT()
	{
		return this->directTime;
	}

	int64_t getDRevT()
	{
		return this->reversTime;
	}

	int64_t getRandT()
	{
		return this->randomTime;
	}

	int64_t getSize()
	{
		return this->size;
	}

	void print()
	{
		cout << "Size:" << this->getSize() << " ";
		cout << "Direct:" << this->getDT() << " ";
		cout << "Revers:" << this->getDRevT() << " ";
		cout << "Random:" << this->getRandT() << "\n";
	}


};

class Wrapper
{
public:
	void heat(int count, int *arr, int *t)
	{

		for (int i = 0; i < count; ++i)
			*t = arr[i];
	}
	void direct(int count, int *arr, int *t)
	{

		for (int i = 0; i < 1000; ++i)
		{
			for (int j = 0; j < count; ++j)
				*t = arr[*t];
		}
	}
	void revers(int count, int *arr, int *t)
	{
		for (int i = 0; i < 1000; ++i)
		{
			for (int j = 0; j < count; ++j)
				*t = arr[*t];
		}
	}
	void rand(int count, int* arr, int* t)
	{
		for (int i = 0; i < 1000; ++i)
		{
			for (int j = 0; j < count; ++j)
				*t = arr[*t];
		}
	}
};

Report RunTest(int size)
{
	Report report;
	Wrapper wrapper;
	report.setSize(size);

	int count = size / 4;
	int *arr = new int[count];

	for (int i = 0; i < count; ++i)
		arr[i] = (i + 1) % count;
	int t;


	wrapper.heat(count, arr, &t);
	auto timer_on = chrono::high_resolution_clock::now();
	wrapper.direct(count, arr, &t);
	auto timer_of = chrono::high_resolution_clock::now();
	report.setDT(chrono::duration_cast<chrono::milliseconds>(timer_of - timer_on).count());


	for (int i = count - 1; i >= 0; --i)
		arr[i] = i - 1;
	arr[0] = count - 1;
	wrapper.heat(count, arr, &t);
	timer_on = chrono::high_resolution_clock::now();
	wrapper.revers(count, arr, &t);
	timer_of = chrono::high_resolution_clock::now();
	report.setRevT(chrono::duration_cast<chrono::milliseconds>(timer_of - timer_on).count());


	for (int i = 0; i < count; ++i)
		arr[i] = rand() % count;
	wrapper.heat(count, arr, &t);
	timer_on = chrono::high_resolution_clock::now();
	wrapper.rand(count, arr, &t);
	timer_of = chrono::high_resolution_clock::now();
	report.setRandT(chrono::duration_cast<chrono::milliseconds>(timer_of - timer_on).count());

	delete[]arr;
	return report;
}

int main()
{
	for (int i = 64; i <= 4 * 1024; i << 1)
	{
		RunTest(i * 1024).print();
	}
}