#pragma once
#include "singletonBase.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//����Ʈ Ŭ������ ���� ����
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//����Ʈ Ŭ������ ����ִ� ���͸� ���� ��
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//��� ����Ʈ�� ������ ����(����Ʈ�� ����ִ� ���͸� ���� ���� �ٽ� ���� ����)
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//���� ��� ����Ʈ�� ��� �ִ� ����
	vTotalEffect m_vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();
	
	//����Ʈ �߰�(Ű��, �̹����̸�, �̹�������ũ��,����ũ��, �������� ����ũ��,����ũ��, FPS, ����Ʈ �ӵ�, ���۰���)
	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	//����Ʈ �÷���(Ű��, ��ǥ)
	void play(string effectKey, int x, int y);
};

