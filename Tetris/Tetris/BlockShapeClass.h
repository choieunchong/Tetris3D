#pragma once
#include "macro.h"

class BlockShapeClass
{
public:
	BlockShapeClass();
	~BlockShapeClass();
	bool Initialize();
private:
	int m_iBlockShape;
	vector<vector<vector<int>>> m_vBlock;
	list<int> m_listBlockShape;
};

