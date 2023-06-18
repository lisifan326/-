#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"

using namespace std;

class Tetris	//��Ϸ���� ������˹���飩
{
public:
	//���캯��
	Tetris(int rows,int cols,int left,int top,int blockSize);
	//			��		��		�����	������		�����С
	void init();	//��ʼ��
	void play();	//��ʼ��Ϸ


private:
	void keyEvent();
	void updataWindow();

	//���ؾ�����һ�ε��øú���������˶���ʱ�䣨ms��
	//
	int getDelay();
	void drop();	//�½�
	void clearLine();
	void moveLeftRight(int offset);


	

private:
	int delay;
	bool updata;	//�Ƿ����

	vector<vector<int>> map;
	int rows;		//
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock;	//���Ͻ�Ԥ�淽��

	Block bakBlock;	//��ǰ���齵������У�����������һ���Ϸ�λ�õ�
};


