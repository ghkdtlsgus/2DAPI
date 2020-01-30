#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

//����ƽ���� ������� �ΰ����� �ʱ�ȭ
gameNode* sceneManager::mCurrentScene = nullptr;


HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	//�ݺ��ڸ� ���ؼ� ���� ���鼭 �ϳ��� �����Ѵ�.
	miSceneList iter = m_SceneList.begin();
	for (iter; iter != m_SceneList.end();)
	{
		//���� 
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

	//��ã������ E_FAIL
	if (find == m_SceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ E_FAIL
	if (find->second == mCurrentScene) return E_FAIL;

	//������� ������ ������ ������ ���� �ʱ�ȭ�ϰ� �������ش�.
	if (SUCCEEDED(find->second->init()))
	{
		//�������� ������ ������
		if (mCurrentScene) mCurrentScene->release();
		mCurrentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
