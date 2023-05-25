#pragma once
#include "macro.h"
#include "InputClass.h"
#include "BlockShapeClass.h"


//const int BLOCK_SIZE = 1;
const int SPACE_SIZE = DRAW_ROW * DRAW_COL * DRAW_Z;

 //2023-05-22 ecchoi [��� ��� ����]

class DrawTetris
{

public:
	DrawTetris();
	~DrawTetris();
struct BlockModel
{
	int block[4][4][4] = 
	{	// �� ���
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1}
	};
	int block2[4][4][4] =
	{	// �� ���
		{0,0,0,0},
		{2,0,0,0},
		{2,0,0,0},
		{2,2,2,2}
	};
	int block3[4][4][4]=
	{	// �� ���
		{3,3},
		{3,3}
	};
	int block4[4][4][4]=
	{	// �� ���
		{0,0,0,0},
		{0,0,0,0},
		{0,0,4,4},
		{4,4,0,0}
	};
	int block5[4][4][4]=
	{   // �� ���
		{0,0,0,0},
		{0,5,5,0},
		{0,5,5,0},
		{5,5,5,5}
	};
} BlockShape;
	void DrawTetrisStart()
	{
		cout << "�ʱ�ȭ";
		bInitialize();
		cout << "Ű���� �Է�";
		//KeyControl();
}
	//2023-05-22 ecchoi [ ��Ʈ������ �ʱ�ȭ �ϱ� ���� �Լ� ]
	bool bInitialize();

	// 2023-05-22 ecchoi [ ��Ʈ������ �����ϱ� ���� �Լ� ]
	void Run(); 
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	//2023-05-22 ecchoi [ ���� �׸��� ���� Map ]
	void DrawBlockMap(); 
	
private:
	// 2023-05-22 ecchoi [����� ��ġ ����]
	int m_iBlockPostion;

	int m_iCurrentBlock;
	
	//2023-05-22 ecchoi [��� �� ����]
//	void DrawBlockModel(char Model); 

	// 2023-05-23 ecchio [x,y,z�� ��ġ �̵��� ���� ����]
	int m_iBlockx;
	int m_iBlocky;
	int m_iBlockz;
	InputClass* m_pInputClass;

	BlockShapeClass* m_pBlockShapeClass;
	//2023-05-24 ecchoi [��ϰ� ���� ��� ����]
	vector<int> m_vBlock3;
	//vector<vector<int>>m_vBlock2[];

private:

	void gotoxy(int x, int y);
// 2023-05-22 ecchoi [��� �ٴڸ� ���� �ƴ��� �˻�]
	void Under();
	//bool KeyEvent();
// 2023-05-23 ecchoi [��� Ű �̺�Ʈ �ޱ�]
	int InputKey();
	bool Frame();
// 2023-05-25 ecchoi [��� ��µǴ� ���� �ܼ�â���� ����� ����]
	void ClearScreen();
	// 2023-05-22 ecchoi [��� �̵� ���� �˻�]
	void MoveBlock(int x, int y, int z);

	// 2023-05-25 ecchoi [��� X ��ġ�� ��� �Լ�]
	int SetPostionX(int xpostion);
	// 2023-05-25 ecchoi [��� X ��ġ�� ��� �Լ�]
	void GetPostionX();
	// 2023-05-25 ecchoi [��� Y ��ġ�� ��� �Լ�]
	int SetPostionY(int ypostion);
	// 2023-05-25 ecchoi [��� Y ��ġ�� ��� �Լ�]
	void GetPostionY();
	// 2023-05-25 ecchoi [��� Z ��ġ�� ��� �Լ�]
	int SetPostionZ(int zpostion);
	// 2023-05-25 ecchoi [��� Z ��ġ�� ��� �Լ�]
	void GetPostionZ();
	//void ShowBlock(bool screen[DRAW_ROW][DRAW_COL][DRAW_Z]);
};