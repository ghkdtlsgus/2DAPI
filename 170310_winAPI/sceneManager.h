#pragma once
#include "singletonBase.h"

//게임노드 전방선언
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

	static gameNode* mCurrentScene;		//현재씬
	mSceneList m_SceneList;				//씬 목록

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가
	gameNode* addScene(string sceneName, gameNode* scene);
	//씬변경
	HRESULT changeScene(string sceneName);
};

