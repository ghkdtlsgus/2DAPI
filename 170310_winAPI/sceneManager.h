#pragma once
#include "singletonBase.h"

//���ӳ�� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

	static gameNode* mCurrentScene;		//�����
	mSceneList m_SceneList;				//�� ���

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//������
	HRESULT changeScene(string sceneName);
};

