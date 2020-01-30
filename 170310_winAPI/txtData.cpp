#include "stdafx.h"
#include "txtData.h"

txtData::txtData()
{
}

txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}
//����¥�� �����͸� ��Ƶ� ��(��� �����͸� ���ٴ����� ©�� ����)
void txtData::txtSave(char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 128);

	file = CreateFile(
		saveFileName,	//������ ���� �Ǵ� �� ��ġ�� ���� �̸�
		GENERIC_WRITE,	//�����̳� ��ġ�� ����ų� �� �� ����� ����
		0,				//������ ���� ��� �Է�
		NULL,			//���� �Ǵ� ��ġ�� ���� ���� �� Ư��
		CREATE_ALWAYS,	//�����̳� ��ġ�� ���� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	//�����̳� ��ġ�� ���� �Ǵ� ���� �� ���� �� Ư��
		NULL);	//������� ������ ���� �� Ư�� �� Ȯ�� Ư���� ���� ������ ������ �մ� ���ø� ���� �ڵ�

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);
}
//���� ����� ������(����¥�� �����͸� ��ǥ ������ �� ����)���� ���ϴ°� ����
char * txtData::vectorArrayCombine(vector<string> vAarry)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vAarry.size(); i++)
	{
		strncat_s(str, 128, vAarry[i].c_str(), 128);
		if ((i + 1) < vAarry.size())
		{
			strcat(str, ",");
		}
	}
	return str;
}

vector<string> txtData::txtLoad(char * loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;
	
	ZeroMemory(str, sizeof(str));

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

//���������� ������ �߶� �������ذ��� �о��
vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
