#include <iostream>
using namespace std;

template<class T,size_t N = 10>
class Array
{
public:
	T& operator[](size_t index)
	{
		return _array[index];
	}
	const T& operator[](size_t index) const
	{
		return _array[index];
	}
	size_t size() const
	{
		return _size;
	}
	bool Empty()
	{
		return 0 == _size;
	}
private:
	T _array[N];
	size_t _size;
};

template <class T1,class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};

template<class T1>
class Data<T1, int>           //�����ػ�
{
public:
	Data(){ cout << "Data<T1,int> " << endl; }
private:
	T1 _d1;
	int _d2;
};

template<>
class Data<int, char>     //ȫ�ػ�
{
public:
	Data(){
		cout << "Data<int,char>" << endl;
	}
private:
	int _d1;
	int _d2;
};

template<typename T1,typename T2>
class Data<T1*, T2*>     //ƫ�ػ�Ϊָ������
{
public:
	Data()
		:_d1(_d2), _d2(4)
	{
		cout << "Data<int*,char*>"<< _d1 << endl;
	}
private:
	T1 _d1;           //��T1,����T1*
	T2 _d2;
};
template<typename T1,typename T2>
class Data<T1&, T2&>     //ƫ�ػ�Ϊ��������
{
public:
	Data()
		:_d1(1), _d2(3)
	{
		cout << "Data<int&,char&>" << _d1 << endl;
	}
private:
	T1 _d1;
	T1 _d2;
};
void Test1()
{
	Data<double, int> d1;            //ģ�������ָ������
	Data<int, double> d2;
	Data<int*, int*> d3;
	Data<double&, int&> d4;
}
//////������ȡ/////////////////////////////////////////
struct TrueType          //��������
{
	static bool Get(){ cout << "int" << endl; return true; }
};
struct FalseType         //�Զ�������
{
	static bool Get(){ cout << "string" << endl; return false; }
};
template<class T>
struct TypeTraits        //Ĭ��Ϊ�Զ�������
{
	typedef FalseType IsPODTYPE;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType IsPODTYPE;
};
template<>
struct TypeTraits<char>
{
	typedef TrueType IsPODTYPE;
};
template<>
struct TypeTraits<float>
{
	typedef TrueType IsPODTYPE;
};
template<>
struct TypeTraits<double>
{
	typedef TrueType IsPODTYPE;
};
�������������Ͷ��ػ�һ��
template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::IsPODTYPE::Get())          //�����������ͣ���ֱ��memcpy����
		memcpy(dst, src, sizeof(T)*size);
	else
	{
		for (size_t i = 0; i < size; i++){        //�����ǣ����ø�ֵ��ʽ����
			dst[i] = src[i];
		}
	}
}
void Test2()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6 };
	int b[10];
	Copy(b, a, 6);              //ģ�庯������ָ������

	string s1[4] = { "1111", "2222", "3333", "4444" };
	string s2[4];
	Copy(s2, s1, 4);
}
int main()
{
	Test1();
	Test2();
	return 0;
}

ģ��������////////////////////////////////
ģ�岻�ܷ������,���ӳ����Ҳ���ģ��ʵ�������Ĵ���
1.�������Զ��Դ�ļ��Ƿ��뵥������ģ�a.cpp�в�û��ʵ��������Ӧ�Ĵ���
2.�������ӵ�ʱ��main.cpp���Ҳ������룬�������Ӵ���