#pragma once
class FrameRender
{
private:
	int *m_count;
	int *m_Frame_X;
	int *m_Frame_Y;
public:
	void Update(int *Frame_X,int *Frame_Y,int Frame_Max_X,int Frame_Max_Y,int *Count);
	void XflipUpdate(int *Frame_X, int *Frame_Y, int Frame_Max_X, int Frame_Max_Y, int *Count);
public:
	FrameRender();
	~FrameRender();
};

