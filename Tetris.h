#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"

using namespace std;

class Tetris	//游戏控制 （俄罗斯方块）
{
public:
	//构造函数
	Tetris(int rows,int cols,int left,int top,int blockSize);
	//			行		列		左距离	顶距离		方块大小
	void init();	//初始化
	void play();	//开始游戏


private:
	void keyEvent();
	void updataWindow();

	//返回距离上一次调用该函数，间隔了多少时间（ms）
	//
	int getDelay();
	void drop();	//下降
	void clearLine();
	void moveLeftRight(int offset);


	

private:
	int delay;
	bool updata;	//是否更新

	vector<vector<int>> map;
	int rows;		//
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock;	//右上角预告方块

	Block bakBlock;	//当前方块降落过程中，用来备份上一个合法位置的
};


