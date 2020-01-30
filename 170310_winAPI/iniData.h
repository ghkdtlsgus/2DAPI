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
	//데이터 추가하기(섹션 ,키 ,벨류)
	void addData(char* section, char* key, char* value);
	//세이브(파일 이름만 넣어도 자동 저장)
	void iniSave(char* fileName);
	

	//문자값 로드
	char* loadDataString(char* fileName, char* section, char* key);
	//정수값 로드
	int loadDataIntger(char* fileName, char* section, char* key);

};

