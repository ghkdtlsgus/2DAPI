#include "stdafx.h"
#include "Maptool.h"


HRESULT Maptool::init()
{
	// Screen  m_x
	m_Screen_X = 0.0f;
	m_Screen_Y = 0.0f;
	
	check_isdata = 0;
	// RC �� �ʱ�ȭ 
	Rc[0] = { 0,0,1100,700 }, Rc[1] = { 1120,0,1450,700 }, Rc[2] = { 1120, 0, 1180, 25 }, Rc[3] = { 1180,0,1240,25 } ,Rc[4] = {10,710,110,760};
	Rc[5] = { 130,710,230,760 };
	// ����ü �ʱ�ȭ
	RcNum = 50;
	// ������ �ʱ�ȭ
	//Page = 0;
	Typebtn = Notting;
	for(int i=0; i<100; i++)
	{
		m_tagMap[i].isdata = false;
		m_tagMap[i].isFrameimg = false;
	}
	ii = 0;
	Maptoolsetup();
	return S_OK;
}

void Maptool::release()
{
	gameNode::release();
	SAFE_DELETE(RcdataC);
	SAFE_DELETE(PagedataC);
}

void Maptool::update()
{
	gameNode::update();
	ii = 0;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//���̺�ε�
		Save_Load();
		RightCollision();
		// �ʿ� �̹��� �ֱ� 
		Applyimg();
		// ��ư Ŭ��
		BtnClick();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		RcdataC->resetinfo();
	}

	// ctrl + leftbtn   = sizeup 
	// ctrl + rightbtn = sizedown 
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		zoomplus();
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		zoommius();
	}
	//������ư
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		PrevValue();
	}
	//X flip
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		
		Xflip();
	}
	// Scroll
	Scroll();
	// ������ ���
	for (int i = 0; i < 100; i++)
	{
		if (!m_tagMap[i].isFrameimg) continue;

		if (m_tagMap[i].isXflip)
		{
			FrameRenderC.XflipUpdate(&m_tagMap[i].Frame_X, &m_tagMap[i].Frame_Y, m_tagMap[i].Frame_Max_X, m_tagMap[i].Frame_Max_Y, &m_tagMap[i].Count);
		}
		else
		FrameRenderC.Update(&m_tagMap[i].Frame_X,&m_tagMap[i].Frame_Y,m_tagMap[i].Frame_Max_X,m_tagMap[i].Frame_Max_Y,&m_tagMap[i].Count);
	}
	
	
}

void Maptool::render()
{
	// �簢�� ����
	Rectangle(getMemDC(), Rc[0].left, Rc[0].top, Rc[0].right, Rc[0].bottom);
	//�ʿ� �׸��� DrawScreenMap
	DrawScreenMap();
	PatBlt(getMemDC(), Rc[1].left, Rc[1].top, Rc[1].right, Rc[1].bottom, BLACKNESS);
	//Rectangle(getMemDC(), Rc[1].left,Rc[1].top,Rc[1].right,Rc[1].bottom);
	Rectangle(getMemDC(), Rc[4].left, Rc[4].top, Rc[4].right, Rc[4].bottom);
	sprintf(strText, "SAVE");
	TextOut(getMemDC(), Rc[4].left+30, Rc[4].top+15, strText, strlen(strText));
	Rectangle(getMemDC(), Rc[5].left, Rc[5].top, Rc[5].right, Rc[5].bottom);
	sprintf(strText, "LOAD");
	TextOut(getMemDC(), Rc[5].left + 30, Rc[5].top + 15, strText, strlen(strText));
	//
	sprintf(strText, "������� %d",ii);
	TextOut(getMemDC(), 0,600,strText, strlen(strText));
	// ���콺 ���� �׸� 
	if (RcdataC->getinfo().isinfo)
	{
		if (!RcdataC->getinfo().isFrameimg)
		{
			if (RcdataC->getinfo().isXflip)
			{
				GDIPMANAGER->renderXFlip(getMemDC(), RcdataC->getinfo().Key, RcdataC->getinfo().Size, _ptMouse.x - RcdataC->getinfo().RCimg.left / 2, _ptMouse.y - RcdataC->getinfo().RCimg.top / 2);
			}
			else {
				GDIPMANAGER->rendersize(getMemDC(), RcdataC->getinfo().Key, RcdataC->getinfo().Size, _ptMouse.x - RcdataC->getinfo().RCimg.left / 2, _ptMouse.y - RcdataC->getinfo().RCimg.top / 2);
			}
		}
		else
		{
			if (RcdataC->getinfo().isXflip)
			{
				GDIPMANAGER->renderFXFlip(getMemDC(), RcdataC->getinfo().Key, RcdataC->getinfo().Size, 0, 0, _ptMouse.x - RcdataC->getinfo().RCimg.left / 2, _ptMouse.y - RcdataC->getinfo().RCimg.top / 2);
			}
			else {
				GDIPMANAGER->renderFsize(getMemDC(), RcdataC->getinfo().Key, RcdataC->getinfo().Size, 0, 0, _ptMouse.x - RcdataC->getinfo().RCimg.left / 2, _ptMouse.y - RcdataC->getinfo().RCimg.top / 2);
			}
		}
		
	}
	
	
	//GDIPMANAGER->renderFlip(getMemDC(), "Map1-1", 500, 500);
	//������ ����
	PagedataC->Render();

	// ���콺 ��ǥ 

	
	wsprintf(strText, "mouseX : %d , mouseY : %d", _ptMouse.x , _ptMouse.y);
	TextOut(getMemDC(), 0, 0, strText, strlen(strText));
	
	/*wsprintf(strText, "check_isdata %d /100", check_isdata);
	TextOut(getMemDC(), 0, 30, strText, strlen(strText));*/
	sprintf(strText, "m_Screen_X :%f  m_Screen_Y : %f",m_Screen_X , m_Screen_Y);
	TextOut(getMemDC(), 0, 60, strText, strlen(strText));
	sprintf(strText, "W_mouseX :%f  W_mouseY : %f", m_Screen_X + _ptMouse.x , m_Screen_Y + _ptMouse.y);
	TextOut(getMemDC(), 0, 90, strText, strlen(strText));


	wsprintf(strText, "m_tag[0].count = %d",m_tagMap[0].Count);
	TextOut(getMemDC(), 0, 120, strText, strlen(strText));
}



void Maptool::Save(char* MapKey)
{
	char* Mapkeyf = ".map";
	strcat(MapKey, Mapkeyf);
	
	HANDLE file;
	DWORD write;
	file = CreateFile(MapKey,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, m_tagMap, sizeof(tagMap)*Max, &write, NULL);
	//WriteFile(file, m_pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
}

void Maptool::Load(char * MapKey)
{
	char* Mapkeyf = ".map";
	strcat(MapKey, Mapkeyf);
	
	HANDLE file;
	DWORD read;
	file = CreateFile(MapKey,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, m_tagMap, sizeof(tagMap)*Max, &read, NULL);
	//ReadFile(file, m_pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
}

void Maptool::RightCollision()
{
	for (int i = 0; i < RcdataC->_vvInfo.size(); i++)
	{
		for (int j = 0; j < RcdataC->_vvInfo[i].size(); j++)
		{
			if (PtInRect(&RcdataC->_vvInfo[i][j].RC, _ptMouse) && PagedataC->Page == i)
			{
				RcdataC->setinfo(RcdataC->_vvInfo, i, j);
				break;
			}		
		}
	}
}

void Maptool::Applyimg()
{
	if (RcdataC->getinfo().isinfo && PtInRect(&Rc[0], _ptMouse))
	{
		for (int i = 0; i < 100; i++)
		{
			if (m_tagMap[i].isdata)
			{
				continue;
			}
			else
			{
				m_tagMap[i].type = Typebtn;
				m_tagMap[i].mapkey = RcdataC->getinfo().Key;
				m_tagMap[i].size = RcdataC->getinfo().Size;
				m_tagMap[i].rc.left = ((_ptMouse.x + m_Screen_X  )- (RcdataC->getinfo().RCimg.left / 2)) ;
				m_tagMap[i].rc.top = ((_ptMouse.y  + m_Screen_Y) - RcdataC->getinfo().RCimg.top / 2 ) ;
				m_tagMap[i].rc.right = ( m_tagMap[i].rc.left + (RcdataC->getinfo().RCimg.left  * RcdataC->getinfo().Size));
				m_tagMap[i].rc.bottom = (m_tagMap[i].rc.top +  (RcdataC->getinfo().RCimg.top * RcdataC->getinfo().Size));
				m_tagMap[i].isFrameimg = RcdataC->getinfo().isFrameimg;
				m_tagMap[i].Frame_Max_X = RcdataC->getinfo().Frame_Max_X;
				m_tagMap[i].Frame_Max_Y = RcdataC->getinfo().Frame_Max_Y;
				m_tagMap[i].Frame_X = 0;
				m_tagMap[i].Frame_Y = 0;
				if (RcdataC->getinfo().isXflip) m_tagMap[i].Frame_Y = m_tagMap[i].Frame_Max_Y;
				m_tagMap[i].Count = 0;
				m_tagMap[i].isXflip = RcdataC->getinfo().isXflip;
				m_tagMap[i].isYflip = RcdataC->getinfo().isYflip;
				m_tagMap[i].isdata = true;
				break;
			}
		}
	}
}

void Maptool::Maptoolsetup()
{
	//�ؽ�Ʈâ 
	H_edit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 1200, 720, 200, 30, _hWnd, HMENU(100), _hInstance, NULL);
	// RCdata Ŭ���� 
	RcdataC = new Rcdata;
	RcdataC->init();
	// Pagedata Ŭ����
	PagedataC = new Pagedata;
	PagedataC->init();
	// Mapname �ʱ�ȭ
	GetWindowText(H_edit, MapName, sizeof(MapName));
	//SetWindowText(H_edit, "�����̸� �Է�");
}

void Maptool::BtnClick()
{
	if (PtInRect(&Rc[2], _ptMouse) && PagedataC->Page !=0)
	{
		PagedataC->SetPage(PagedataC->Page - 1);
	}
	else if (PtInRect(&Rc[3], _ptMouse)) //������������ ����ؼ� ��������� 
	{
		PagedataC->SetPage(PagedataC->Page + 1);
	}
}


float Maptool::zoomplus()
{
	RcdataC->setinfosize(RcdataC->getinfo().Size + 0.05f);
	return NULL;
}

float Maptool::zoommius()
{
	RcdataC->setinfosize(RcdataC->getinfo().Size - 0.05f);
	return NULL;
}

void Maptool::Save_Load()
{
	//save
	if (PtInRect(&Rc[4], _ptMouse))
	{
		GetWindowText(H_edit, MapName, sizeof(MapName));
		if (MapName[0] == NULL)
		{
			SetWindowText(H_edit, "�����̸��� �Է��ϼ���");
		}
		else if (MapName != "�����̸��� �Է��ϼ���")
		{
			Save(MapName);
		}
	}
	//load
	else if (PtInRect(&Rc[5], _ptMouse))
	{
		GetWindowText(H_edit, MapName, sizeof(MapName));
		if (MapName[0] == NULL)
		{
			SetWindowText(H_edit, "�����̸��� �Է��ϼ���");
		}
		else if (MapName != "�����̸��� �Է��ϼ���")
		{
			Load(MapName);
		}
	}
}

void Maptool::PrevValue()
{
	check_isdata = 0;
	for (int i = 0; i < 100; i++)
	{
		if (m_tagMap[i].isdata) check_isdata++;
	}
	if (check_isdata == 0) return;
	
	m_tagMap[check_isdata - 1].isdata = false;
}

void Maptool::Xflip()
{
	if (!RcdataC->getinfo().isXflip)
	{
		RcdataC->setXflip(true);
	}
	else
	{
		RcdataC->setXflip(false);
	}
}

void Maptool::Yflip()
{
	if (!RcdataC->getinfo().isYflip)
	{
		RcdataC->setYflip(true);
	}
	else
	{
		RcdataC->setYflip(false);
	}
}

void Maptool::Scroll()
{
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && m_Screen_Y<800)
	{
		m_Screen_Y += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && m_Screen_Y>0)
	{
		m_Screen_Y -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && m_Screen_X > 0)
	{
		m_Screen_X -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && m_Screen_X < 900)
	{
		m_Screen_X += 5.0f;
	}
}

void Maptool::DrawScreenMap()
{
	// �ʿ� �׸��� 
	for (int i = 0; i < 100; i++)
	{
		if (!m_tagMap[i].isdata)
		{
			break;
		}
		else if (m_tagMap[i].rc.left - m_Screen_X< 1100 && m_tagMap[i].rc.right - m_Screen_X > 0 && m_tagMap[i].rc.top - m_Screen_Y < 700 && m_tagMap[i].rc.bottom - m_Screen_Y > 0)
		{
			ii += 1;
			if (!m_tagMap[i].isFrameimg) {
				if (m_tagMap[i].isXflip)
				{
					GDIPMANAGER->renderXFlip(getMemDC(), m_tagMap[i].mapkey, m_tagMap[i].size, m_tagMap[i].rc.left - m_Screen_X, m_tagMap[i].rc.top - m_Screen_Y);
				}
				else GDIPMANAGER->rendersize(getMemDC(), m_tagMap[i].mapkey, m_tagMap[i].size, m_tagMap[i].rc.left - m_Screen_X, m_tagMap[i].rc.top - m_Screen_Y);
			}
			else
			{
				if (m_tagMap[i].isXflip)
				{
					GDIPMANAGER->renderFXFlip(getMemDC(), m_tagMap[i].mapkey, m_tagMap[i].size, m_tagMap[i].Frame_X, m_tagMap[i].Frame_Y, m_tagMap[i].rc.left - m_Screen_X, m_tagMap[i].rc.top - m_Screen_Y);
				}
				else GDIPMANAGER->renderFsize(getMemDC(), m_tagMap[i].mapkey, m_tagMap[i].size, m_tagMap[i].Frame_X, m_tagMap[i].Frame_Y, m_tagMap[i].rc.left - m_Screen_X, m_tagMap[i].rc.top - m_Screen_Y);
			}
		}
	}
	PatBlt(getMemDC(),1100, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(),0, 700, 1100, 700, WHITENESS);
}

Maptool::Maptool()
{
}


Maptool::~Maptool()
{
}
