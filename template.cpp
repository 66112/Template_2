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
class Data<T1, int>           //部分特化
{
public:
	Data(){ cout << "Data<T1,int> " << endl; }
private:
	T1 _d1;
	int _d2;
};

template<>
class Data<int, char>     //全特化
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
class Data<T1*, T2*>     //偏特化为指针类型
{
public:
	Data()
		:_d1(_d2), _d2(4)
	{
		cout << "Data<int*,char*>"<< _d1 << endl;
	}
private:
	T1 _d1;           //是T1,不是T1*
	T2 _d2;
};
template<typename T1,typename T2>
class Data<T1&, T2&>     //偏特化为引用类型
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
	Data<double, int> d1;            //模板类必须指定类型
	Data<int, double> d2;
	Data<int*, int*> d3;
	Data<double&, int&> d4;
}
//////类型萃取/////////////////////////////////////////
struct TrueType          //内置类型
{
	static bool Get(){ cout << "int" << endl; return true; }
};
struct FalseType         //自定义类型
{
	static bool Get(){ cout << "string" << endl; return false; }
};
template<class T>
struct TypeTraits        //默认为自定义类型
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
将所有内置类型都特化一下
template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::IsPODTYPE::Get())          //若是内置类型，则直接memcpy函数
		memcpy(dst, src, sizeof(T)*size);
	else
	{
		for (size_t i = 0; i < size; i++){        //若不是，则用赋值方式拷贝
			dst[i] = src[i];
		}
	}
}
void Test2()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6 };
	int b[10];
	Copy(b, a, 6);              //模板函数不用指定类型

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

模板分离编译////////////////////////////////
模板不能分离编译,链接出错，找不到模板实例化出的代码
1.编译器对多个源文件是分离单独编译的，a.cpp中并没有实例化出相应的代码
2.所以链接的时候main.cpp并找不到代码，导致链接错误