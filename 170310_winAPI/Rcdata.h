#pragma once
#include <vector>

struct info
{
	RECT RC;
	RECT RCimg;
	string Key;
	bool isinfo;
	bool isFrameimg;
	bool isXflip;
	bool isYflip;
	int Frame_Max_X;
	int Frame_Max_Y;
	float Size;
};
class Rcdata
{
protected:
	info _info;
	//����� ��
	info _saveinfo;
protected:
	typedef vector<info> vInfo;
	typedef vector<info> ::iterator viInfo;
	typedef vector<vector<info>> vvInfo;
	typedef vector<vector<info>> ::iterator vviInfo;
public:
	vInfo _vInfo;
	viInfo _viInfo;

	vvInfo _vvInfo;
	vviInfo _vviInfo;
	// ���� �� �ҷ�����,�����ϱ� �Լ�
	info getinfo() { return _saveinfo; }
	void setinfosize(float size) { _saveinfo.Size = size; }
	void setinfo(vvInfo _vvInfo, int i, int j) { _saveinfo = _vvInfo[i][j]; }
	void setXflip(bool xflip) { _saveinfo.isXflip = xflip; }
	void setYflip(bool yflip) { _saveinfo.isYflip = yflip; }
	void resetinfo() { _saveinfo.isinfo = false; }
	// =======================
	void init();
	Rcdata();
	~Rcdata();
};

