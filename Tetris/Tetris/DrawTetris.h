#pragma once
#include "macro.h"
#include "InputClass.h"
#include "BlockShapeClass.h"


//const int BLOCK_SIZE = 1;
const int SPACE_SIZE = DRAW_ROW * DRAW_COL * DRAW_Z;

 //2023-05-22 ecchoi [블록 모양 결정]

class DrawTetris
{

public:
	DrawTetris();
	~DrawTetris();
struct BlockModel
{
	int block[4][4][4] = 
	{	// ㅡ 모양
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1}
	};
	int block2[4][4][4] =
	{	// ㄴ 모양
		{0,0,0,0},
		{2,0,0,0},
		{2,0,0,0},
		{2,2,2,2}
	};
	int block3[4][4][4]=
	{	// ㅁ 모양
		{3,3},
		{3,3}
	};
	int block4[4][4][4]=
	{	// ㄹ 모양
		{0,0,0,0},
		{0,0,0,0},
		{0,0,4,4},
		{4,4,0,0}
	};
	int block5[4][4][4]=
	{   // ㅗ 모양
		{0,0,0,0},
		{0,5,5,0},
		{0,5,5,0},
		{5,5,5,5}
	};
} BlockShape;
	void DrawTetrisStart()
	{
		cout << "초기화";
		bInitialize();
		cout << "키보드 입력";
		//KeyControl();
}
	//2023-05-22 ecchoi [ 테트리스를 초기화 하기 위한 함수 ]
	bool bInitialize();

	// 2023-05-22 ecchoi [ 테트리스를 실행하기 위한 함수 ]
	void Run(); 
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	//2023-05-22 ecchoi [ 맵을 그리기 위한 Map ]
	void DrawBlockMap(); 
	
private:
	// 2023-05-22 ecchoi [블록의 위치 갱신]
	int m_iBlockPostion;

	int m_iCurrentBlock;
	
	//2023-05-22 ecchoi [블록 모델 생성]
//	void DrawBlockModel(char Model); 

	// 2023-05-23 ecchio [x,y,z축 위치 이동을 위한 변수]
	int m_iBlockx;
	int m_iBlocky;
	int m_iBlockz;
	InputClass* m_pInputClass;

	BlockShapeClass* m_pBlockShapeClass;
	//2023-05-24 ecchoi [블록과 맵을 담기 위해]
	vector<int> m_vBlock3;
	//vector<vector<int>>m_vBlock2[];

private:

	void gotoxy(int x, int y);
// 2023-05-22 ecchoi [블록 바닥면 인지 아닌지 검사]
	void Under();
	//bool KeyEvent();
// 2023-05-23 ecchoi [블록 키 이벤트 받기]
	int InputKey();
	bool Frame();
// 2023-05-25 ecchoi [계속 출력되는 맵을 콘솔창에서 지우기 위해]
	void ClearScreen();
	// 2023-05-22 ecchoi [블록 이동 가능 검사]
	void MoveBlock(int x, int y, int z);

	// 2023-05-25 ecchoi [블록 X 위치를 담는 함수]
	int SetPostionX(int xpostion);
	// 2023-05-25 ecchoi [블록 X 위치를 담는 함수]
	void GetPostionX();
	// 2023-05-25 ecchoi [블록 Y 위치를 담는 함수]
	int SetPostionY(int ypostion);
	// 2023-05-25 ecchoi [블록 Y 위치를 담는 함수]
	void GetPostionY();
	// 2023-05-25 ecchoi [블록 Z 위치를 담는 함수]
	int SetPostionZ(int zpostion);
	// 2023-05-25 ecchoi [블록 Z 위치를 담는 함수]
	void GetPostionZ();
	//void ShowBlock(bool screen[DRAW_ROW][DRAW_COL][DRAW_Z]);
};