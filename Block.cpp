#include "Block.h"
#include<stdlib.h>
#include<time.h>


IMAGE* Block::imgs[7] = { NULL , };
int Block::size = 36;

Block::Block() //����Block��Ĺ��캯��
{
	if (imgs[0] == NULL) { //�������ͼƬΪ��
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");//���ط���ͼƬ

		SetWorkingImage(&imgTmp); //������ͼƬ����Ϊ������
		for (int i = 0; i < 7; i++) { //ѭ�����ط���ͼƬ
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();	//�ָ�������
		srand(time(NULL));
	}


	int blocks[7][4] = {//���巽������ͺ���״
		1,3,5,7, // I
		2,4,5,7, // S 
		3,5,4,6, // Z 
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // ��

	};

	//�������һ�ֶ���˹����
	blockType = rand() % 7;	//��7���������������һ����������

	//��ʼ�� samllBlocks
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;

	}
	img = imgs[blockType - 1]; //���õ�ǰ�����Ӧ��ͼƬ
}
void Block::drop() //�����Զ�����ĺ���
{
	for (auto &block :smallBlocks)
	{
		block.row++;
	}
}

void Block::moveLeftRight(int offset) //�����ƶ�����ĺ���
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}

void Block::retate() //��ת����ĺ���
{
}

void Block::draw(int leftMargin, int topMargin) //�ڽ����ϻ��Ʒ���ĺ���
{
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + smallBlocks[i].col * size;
		int y = topMargin + smallBlocks[i].row * size;
		putimage(x, y, img); //��ָ��λ�û��Ʒ���
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return * this;		//�����һ������ĵ�ַ�����Լ��������ص�ǰ������
	
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
		//���ù̶�λ�ò��̶�
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}
