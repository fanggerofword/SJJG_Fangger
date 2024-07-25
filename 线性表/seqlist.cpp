#include<iostream>
#include <stdexcept>

#if 1
//初始化+增删查改+显示
typedef struct SeqList{
	int* data; //存放每个表中的数据，用指针模拟数组
	int MaxLength; 
	int size; 
}SeqList;
SeqList sl;

SeqList InitList(SeqList _sl, int _max);
void TheServer();
SeqList Add(SeqList _sl, int _num);
SeqList Insert(SeqList _sl, int _num, int _index);
SeqList Del_Lcoation(SeqList _sl, int _index);
SeqList Del_Values(SeqList _sl, int _num, bool ifmuti);
bool ifexit(SeqList _sl, int _num);
void show(SeqList _sl);

/*初始化 
	尝试分配内存，失败则抛出异常，成功分配最大值和当前值，完成初始化
*/
SeqList InitList(SeqList _sl, int _max) {
	_sl.data = (int*)malloc(sizeof(int)*(_max+1));
	if (_sl.data == nullptr) {
		throw std::bad_alloc();
	}
	_sl.size = 0;
	_sl.MaxLength = _max;
	return _sl;
}

/*服务函数
	服务用户进行操作顺序表：初始化+增删查改+显示
*/
void TheServer() {

	int _max;
	std::cout << "请输入您要创建顺序表的最大容量" << std::endl;
	std::cin >> _max;
	try {
		sl = InitList(sl,_max);
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "分配内存失败" << e.what() << std::endl;
	}

	try {
		sl = Add(sl, 8);
		sl = Add(sl, 2);
		sl = Add(sl, 1);
		sl = Add(sl, 9);
	}
	catch (const std::out_of_range& e) {
		std::cerr << "异常：" << e.what() << std::endl;
	}
	show(sl);
	sl = Insert(sl, 7, 2);
	show(sl);
	sl = Insert(sl, 3, 100);
	show(sl);

	// 初始化和删除都没有问题了，接下来检测删除

	sl = Del_Lcoation(sl, 2);
	show(sl);

	sl = Del_Values(sl, 2, false);
	show(sl);

	sl = Add(sl, 1);
	show(sl);

	sl = Del_Values(sl, 1, true);

	show(sl);

	sl = Del_Values(sl, 100, true);
}
/*增- - 末尾新增数据*/
SeqList Add(SeqList _sl , int _num) {
	if (_sl.size >= _sl.MaxLength) {
		throw std::out_of_range("新增数据超过了预设最大值，无法新增数据");
	}
	_sl.data[_sl.size] = _num;
	_sl.size += 1;
	return _sl;
}
/*增- - 指定位置插入*/
SeqList Insert(SeqList _sl, int _num, int _index) {
	if (_index > _sl.size) {
		std::cout << "位置超过索引，即将自动在末尾进行插入" << std::endl;
		try {
			_sl = Add(_sl, _index); 
			return _sl;
		}
		catch (const std::out_of_range& e) {
			std::cerr << "异常：" << e.what() << std::endl;
		}
	}
	if (_sl.size >= _sl.MaxLength) {
		throw std::out_of_range("插入数据超过了预设最大值，无法插入数据");
	}
	// 如果未超过索引最大位置，则进行指定位置插入
	for (int i = _sl.size-1; i >=_index-1; i--) {
		_sl.data[i+1] = _sl.data[i];
	}
	_sl.size += 1;
	_sl.data[_index - 1] = _num;
	return _sl;
}

/*删- - 按位置进行删除*/
SeqList Del_Lcoation(SeqList _sl , int _index) {
	if (_index > _sl.size) {
		throw std::out_of_range("输入位置索引非法");
	}
	for (int i = _index-1; i <= _sl.size; i++) {
		_sl.data[i] = _sl.data[i + 1];
	}
	_sl.size -= 1;
	return _sl;
}

/*删- - 按数据进行删除*/
SeqList Del_Values(SeqList _sl , int _num ,bool ifmuti){
	int _index;
	int mun=0;
	if (!ifexit(_sl, _num)) { std::cout << "数据不存在" << std::endl; return _sl; }
	for (int i = 0; i < _sl.size; i++) {
		if (_sl.data[i] != _num) continue;
		_index = i+1;
		mun += 1;
		// 找到此位置的索引，按位置删除函数进行删除
		Del_Lcoation(_sl, _index);
		if (!ifmuti) {
			_sl.size -= 1;
			return _sl;
		}
	}
	_sl.size -= mun;
	return _sl;
}

/*查- - 字面意思*/ 
bool ifexit(SeqList _sl , int _num) {
	for (int i = 0; i < _sl.size; i++) {
		if (_sl.data[i] != _num) continue;
		return true;
	}
	return false;
}

void show(SeqList _sl) {
	for (int i = 0; i <_sl.size; i++) {
		std::cout << _sl.data[i] << " ";
	}std::cout << "\n";
}
int main() {
	TheServer();
}




/*
	tips:
	void throw_it(根据不同的枚举类型，抛出不同的错误)
	void catch_it(根据不同的枚举类型，接受并打印)
*/
#endif