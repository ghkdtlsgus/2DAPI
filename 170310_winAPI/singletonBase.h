#pragma once
//==================================================
//	## singletonBase ## (�� ���̽��� �̱����� �����)
//==================================================

/*
�̱��� ������ static member�� �ϳ��� �ν��Ͻ��� �����Ǹ�.
���α׷� �ȿ��� ���������� ������ �����ϴ�.
���� Ŭ������ �ν��Ͻ��� �ϳ��� �����ϰ��� �� �� ����Ѵ�.

���� ������ �̿��ص� �ϳ��� �ν��Ͻ��� ������ �� ������,
�̱��� ������ ����ϸ� Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ��� 
�����ϴ� ����� ����ȭ �Ͽ� ������ �� �ְ�, ���, ��ü ����, ��ü�Ҹ�
, �ν��Ͻ��� ���� ������ Ȱ�뿡 �����ϴ�.

�� ���� ����� �ڱ� �����ΰ� �ڱ��� ������ �ν��Ͻ��� �����ϴ�
����� ��ü������ �����ϴ� ����̴�.
�� �̱��� ���̽��� �ٸ� �ν��Ͻ��� �������� �ʵ��� ó�� �� �� �ְ�,
���� ��� ���� ������ �� �� �ִ�.
*/

template <typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	//�̱��� ��ü ��������
	static T* getSingleton();
	//�̱��� ��ü �޸𸮿��� �����ϱ�
	void releaseSingleton();

};

//�̱��� �ν��Ͻ� ����
template <typename T>
T* singletonBase<T>::singleton = nullptr;

//�̱��� ��ü ��������
template <typename T>
T* singletonBase<T>::getSingleton()
{
	//�̱��� ��ü�� ������ ���� ����
	if (!singleton) singleton = new T;

	return singleton;
}

//�̱��� ��ü �޸𸮿��� ����
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	//�̱��� ��ü�� �մٸ� �޸𸮿��� ����
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
