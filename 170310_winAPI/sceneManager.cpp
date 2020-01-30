#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

//스태틱변수 현재씬은 널값으로 초기화
gameNode* sceneManager::mCurrentScene = nullptr;


HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	//반복자를 통해서 맵을 돌면서 하나씩 삭제한다.
	miSceneList iter = m_SceneList.begin();
	for (iter; iter != m_SceneList.end();)
	{
		//삭제 
		if (iter->second != NULL)
		{
			if (iter->second == mCurrentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = m_SceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	m_SceneList.clear();
}

void sceneManager::update()
{
	if (mCurrentScene) mCurrentScene->update();
}

void sceneManager::render()
{
	if (mCurrentScene) mCurrentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;
	m_SceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = m_SceneList.find(sceneName);

	//못찾앗으면 E_FAIL
	if (find == m_SceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재씬이랑 같으면 E_FAIL
	if (find->second == mCurrentScene) return E_FAIL;

	//여기까지 왔으면 문제가 없으니 씬을 초기화하고 변경해준다.
	if (SUCCEEDED(find->second->init()))
	{
		//기존씬이 있으면 릴리즈
		if (mCurrentScene) mCurrentScene->release();
		mCurrentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
