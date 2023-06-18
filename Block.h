#pragma once
#include<graphics.h>	//IMAGE所需头文件
#include<vector>
#include <vector>

using namespace std;

struct Point
{
	int row;
	int col;

};




class Block	//方块类
{
public:
	Block();
	void drop();
	void moveLeftRight(int offset);
	void retate();//旋转
	void draw(int leftMargin, int topMargin);
	static IMAGE** getImages();
	Block& operator=(const Block& other);	//重载&运算符

	bool blockInMap(const vector<vector<int>>& map);
	//Point* getSmallBlock();

	void solidify(vector<vector<int>>& map);

private:
	int blockType;	//方块的类型
	Point smallBlocks[4];	
	IMAGE *img;	//图片指针

	static IMAGE* imgs[7];
	static int size;
};
