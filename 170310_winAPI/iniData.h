#pragma once
#include "singletonBase.h"

struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase <iniData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

	arrIniDatas vIniDatas;

public:
	iniData();
	~iniData();

	HRESULT init();
	//������ �߰��ϱ�(���� ,Ű ,����)
	void addData(char* section, char* key, char* value);
	//���̺�(���� �̸��� �־ �ڵ� ����)
	void iniSave(char* fileName);
	

	//���ڰ� �ε�
	char* loadDataString(char* fileName, char* section, char* key);
	//������ �ε�
	int loadDataIntger(char* fileName, char* section, char* key);

};

