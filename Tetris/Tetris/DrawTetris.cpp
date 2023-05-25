#include "DrawTetris.h"

DrawTetris::DrawTetris()
{
	//cout << "생성자";
	//m_cDrawTetris[DRAW_ROW][DRAW_COL] = { 0 };
	m_iBlockPostion = 0;
	m_iBlockx = 0;
	m_iBlocky = 0;
	m_iBlockz = 0;
	m_iCurrentBlock = 0;
}

DrawTetris::~DrawTetris()
{
}

void DrawTetris::gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

bool DrawTetris::bInitialize()
{

	m_pInputClass = new InputClass;
	if (!m_pInputClass)
	{
		return false;
	}
	m_pInputClass->Initialize();

	m_pBlockShapeClass = new BlockShapeClass;
	if (!m_pBlockShapeClass)
	{
		return false;
	}
	cout << "bInitialize" << endl;

	return m_pBlockShapeClass->Initialize();

}
void DrawTetris::ClearScreen()
{
	system("cls");
}

void DrawTetris::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg); // WM_CHAR 메시지를 만들어 메시지 큐에 덧붙인다.
			DispatchMessage(&msg); // 메시지를 윈도우 프로시저로 보낸다
		}
		else
		{
			// 그 외에는 KeyEvent 함수를 처리합니다.
			if (!Frame());
				break;
		}
	}
}
bool DrawTetris::Frame()
{
	if (m_pInputClass->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	
}


int DrawTetris::InputKey()
{
	char Key = 224;
	while (1) 
	{
		if (_kbhit())
		{
			if (Key == -32)
			{	

				switch (Key)
				{
				case UP:
					cout << "KeyControl_up";
					
					 MoveBlock(0, 0, 1);
					break;
				case DOWN:
					cout << "down";
					MoveBlock(0, 1, 0);
					break;
				case RIGHT:
					cout << "KeyControl_Right";
					MoveBlock(1, 0, 0);
					break;
				case LEFT:
					cout << "LEFT";
					MoveBlock(-1, 0, 0);
					break;
				case SPACE:
					cout << "SPACE";
					MoveBlock(0, 1, 0);
					break;
				case Z:
					cout << "Z";
					MoveBlock(0, 0, 1);
					break;
				case X:
					cout << "X";
					MoveBlock(0, 0, -1);
					break;
				case Y:
					cout << "Y";
					break;
				case ONE:
					cout << "1";
					DrawBlockMap();
					break;
				}
			}
		}
	}
	return 0;
}




void DrawTetris::MoveBlock(int x, int y, int z)
{

	//int xPos; //x 축 위치 블록 검사
	//int yPos; // y 축 위치 블록 검사
	//int zPos; // z 축 위치 블록 검사
	/*if (yPos != DRAW_ROW || xPos != DRAW_COL) 
	{
*/
	if (m_iBlockx + x < 0 || m_iBlockx + x >= DRAW_COL ||
		m_iBlocky + y < 0 || m_iBlocky + y >= DRAW_ROW ||
		m_iBlockz + z < 0 || m_iBlockz + z >= DRAW_Z) {
		cout << "블록을 이동할 수 없습니다!" << endl;
		return;
	}

	// 블록을 이동한 위치로 업데이트
	m_iBlockx += x;
	m_iBlocky += y;
	m_iBlockz += z;

	cout << "MoveBlockm_iBlockX:" << m_iBlockx << endl;
	cout << "MoveBlockm_iBlockY:" << m_iBlocky << endl;
	cout << "MoveBlockm_iBlockZ:" << m_iBlockz << endl;
	/*}*/

	cout << "이동 못함";
	/*m_iBlockPostion =*/
	//KeyControl();
}

LRESULT DrawTetris::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
	{
		m_pInputClass->KeyDown((unsigned int)wparam);
		return 0;
	}
	case WM_KEYUP:
	{
		m_pInputClass->KeyUp((unsigned int)wparam);
		return 0;

		break;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void DrawTetris::DrawBlockMap()
{

	for (int y = 0; y < DRAW_ROW + 2; ++y)
	{
		for (int x = 0; x < DRAW_COL + 2; ++x)
		{
			if ((y == 0 && (x == 0 || x == DRAW_COL + 1)) ||
				(x == 0) || (y == DRAW_ROW + 1) || (x == DRAW_COL + 1))
				cout << "■";
			 
			else
				cout << "  ";
			//m_cDrawTetris[y][x][0];
		}
		cout << endl;
	}

	cout << endl;
//	cout << "m_cDrawTetris" << m_cDrawTetris<<endl;
	Under();
}

// 블록의 위치를 맴버 변수로 선언을 해 기억해야 하는거 아닌가?
void DrawTetris::Under()
{
	cout << "Under" << endl;
	// 테트리스 규격 설정
	int screen[DRAW_ROW][DRAW_COL+1][DRAW_Z] = { false };
	
	//m_cDrawTetris[DRAW_ROW][DRAW_COL][DRAW_Z] = { false };
	if (m_iBlockx == 0 || m_iBlocky == 0 || m_iBlockz == 0)
	{
		int blockX = (DRAW_COL - 2) / 2; // 블록의 시작 위치를 가운데로 조정
		int blockY = 0;
		int blockZ = 0;
		m_iBlockx = blockX;
		m_iBlocky = blockY;
		m_iBlockz = blockZ;
	}
	else 
	cout << "m_iBlockx:" << m_iBlockx<<endl;
	cout << "m_iBlocky:" << m_iBlocky<<endl;
	cout << "m_iBlockz:" << m_iBlockz<<endl;

	//vector<int>::iterator it = m_vBlock3.end();
	while (m_iBlocky !=DRAW_ROW)
	{	// 블록이 바닥면에 닿았는지 그리고 밑에 블록이 있는지 검사 해야함
		// 다음 블록을 위해 이전 블록이 바닥에 떨어진 모습과 새로운 블록을 떨어 트려야 한다
		if (m_iBlocky != DRAW_ROW || m_iBlockx != DRAW_COL || m_iBlocky < 0)
		{
			ClearScreen();

				for (int x = 0; x < 4; ++x)
				{
					//	screen[blockY+x][blockX][blockZ] = true;
					screen[m_iBlocky][m_iBlockx + x][m_iBlockz] = true;
					cout << "screen" << screen << endl;
					cout << "blockY" << m_iBlocky << endl;
					cout << "blockX" << m_iBlockx << endl;
					//m_cDrawTetris[blockX][blockY][blockZ] = true;
						//cout << "m_cDrawTetris" << m_cDrawTetris << endl;
				}
			
			// 기존에 있던 프레임을 삭제하고 한칸씩 내려가는 블록을 만들어야 한다
			//vector<int>vBlock;
			for (int i = 0; i < DRAW_ROW+1; ++i)
			{
				for (int j = 0; j < DRAW_COL+2; ++j)
				{
					// 맵을 돌며 블록이 중간에서 내려가는 모션으로
					if (screen[i][j][0])
						cout << "■";
					else if ((i == 0 && (j == 0 || j == DRAW_COL+1)) ||
						(j == 0) || (i == DRAW_ROW+1) || (j == DRAW_COL+1))
						cout << "■";
					else
						cout << "  ";
					// 백터로 바닥에 닿은 블록 저장 후 다음 블록  보여주기
					 // m_vBlock3.push_back(screen[i][j][0]);
					//m_vBlock3.push_back(it, &i);
				//	cout << "m_vBlock3.end - 1:" <<	m_vBlock3.end - 1;

			//		cout << "m_vBlock.end():" << m_vBlock3.end - 1;
			//		cout <<"m_vBlock3.size():"<< m_vBlock3.size();

					// 테트리스 맵과 이전 블록의 위치를 저장하기 위해
					//if(m_iBlocky == DRAW_ROW || m_iCurrentBlock == )
					//vBlock.push_back(j);
				}
				cout << endl;
				//m_vBlock2[i].size();
				
			}
		
			this_thread::sleep_for(1s);

			for (int x = 0; x < 4; ++x)
			{
			//	screen[blockY+x][blockX][blockZ] = false;
				screen[m_iBlocky][m_iBlockx +x][m_iBlockz] = false;
				cout << "screen22" << screen;
			}
			m_iBlocky++;
			cout<< "blockY" << m_iBlocky << endl;
			// 한줄 떨어지면 그 다음 블록 생성 후 시작
			if (m_iBlocky == DRAW_ROW+1)
				break;
			else if (m_iBlockx == DRAW_ROW +1)
				break;
				m_vBlock3.push_back(m_iBlockx);
				m_vBlock3.push_back(m_iBlocky);
				m_vBlock3.push_back(m_iBlockz);
				
				cout << "m_vBlock3.size():" << m_vBlock3.size() << endl;
			
				// x,y,z 좌표 다들어감
				vector<int>::iterator it;
				for (it = m_vBlock3.begin(); it != m_vBlock3.end(); ++it)
				{
					cout <<"it" <<*it<<endl;
				}
				// 담은 좌표를 현재의 맵에 마지막 좌표만 넣어준다.

		}
	}
	MoveBlock(m_iBlockx, m_iBlocky, m_iBlockz);
	cout << "게임 종료" << endl;
}

int DrawTetris::SetPostionX(int xpostion)
{
	 m_iBlockx += xpostion;;
	 return m_iBlockx;
}
void DrawTetris::GetPostionX()
{
	m_iBlockx;
}
int DrawTetris::SetPostionY(int ypostion)
{
	return m_iBlocky += ypostion;
}

void DrawTetris::GetPostionY()
{
	m_iBlocky;
}

int DrawTetris::SetPostionZ(int zpostion)
{
	return m_iBlockz;
}

void DrawTetris::GetPostionZ()
{
	m_iBlockz;
}


//void DrawTetris::ShowBlock(bool screen[DRAW_ROW][DRAW_COL][DRAW_Z])
//{
//	for (int i = 0; i < DRAW_ROW; ++i)
//	{
//		for (int j = 0; j < DRAW_COL; ++j)
//		{
//			if (screen[i][j][0])
//				cout << "■";
//			else
//				cout << "  ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
