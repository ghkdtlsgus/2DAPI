#include "stdafx.h"
#include "iniData.h"

iniData::iniData()
{
}

iniData::~iniData()
{
}

HRESULT iniData::init()
{
	return S_OK;
}

void iniData::addData(char * section, char * key, char * value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//ini������ ����ü ���Ϳ� ���
	arrIniData vIniData;
	vIniData.push_back(iniData);

	//��� �����ʹ� nIniData�� ����ü�� ���� ���͸� ���
	vIniDatas.push_back(vIniData);
}

void iniData::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	for (int i = 0; i < vIniDatas.size(); i++)
	{
		arrIniData vData = vIniDatas[i];

		WritePrivateProfileString(
			vData[0].section,	//������
			vData[0].key,		//�������
			vData[0].value,		//������ҿ� �ۼ��� ����
			str);				//ini���ϰ��
		vData.clear();
	}
	vIniDatas.clear();
}

char * iniData::loadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	char data[64] = { NULL };
	GetPrivateProfileString(
		section,
		key,
		"",	//�����̸��̳� Ű�̸��� ã�� ���ϸ� ����Ʈ ����� ��Ʈ��
		data,	//Ű������ ����Ű�� ���� ������ ����
		64,		//Ű���� ������ ���� ������
		str);


	return data;
}

int iniData::loadDataIntger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\save/%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	MAX_PATH;


	return GetPrivateProfileInt(section, key, 0, str);
}
