#include "Block.h"
#include<stdlib.h>
#include<time.h>


IMAGE* Block::imgs[7] = { NULL , };
int Block::size = 36;

Block::Block() //创建Block类的构造函数
{
	if (imgs[0] == NULL) { //如果方块图片为空
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");//加载方块图片

		SetWorkingImage(&imgTmp); //将方块图片设置为工作区
		for (int i = 0; i < 7; i++) { //循环加载方块图片
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();	//恢复工作区
		srand(time(NULL));
	}


	int blocks[7][4] = {//定义方块的类型和形状
		1,3,5,7, // I
		2,4,5,7, // S 
		3,5,4,6, // Z 
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田

	};

	//随机生成一种俄罗斯方块
	blockType = rand() % 7;	//在7个方块中随机生成一个方块类型

	//初始化 samllBlocks
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;

	}
	img = imgs[blockType - 1]; //设置当前方块对应的图片
}
void Block::drop() //方块自动下落的函数
{
	for (auto &block :smallBlocks)
	{
		block.row++;
	}
}

void Block::moveLeftRight(int offset) //左右移动方块的函数
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}

void Block::retate() //旋转方块的函数
{
}

void Block::draw(int leftMargin, int topMargin) //在界面上绘制方块的函数
{
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + smallBlocks[i].col * size;
		int y = topMargin + smallBlocks[i].row * size;
		putimage(x, y, img); //在指定位置绘制方块
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return * this;		//如果另一个对象的地址等于自己本身，返回当前对象本身
	
	this->blockType = other.blockType;
	
	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;

}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++)
	{
		if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
			smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
			map[smallBlocks[i].row][smallBlocks[i].col])
		{
			return false;
		}
	}

	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++) {
		//设置固定位置并固定
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}
