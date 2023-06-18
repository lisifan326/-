#include "Tetris.h"		
#include<time.h>		
#include<stdlib.h>
#include"Block.h"
#include<conio.h>
const int SPEED_NORMAL = 300;//ms ��ͨ�ٶ�
const int SPEED_QUICK = 50;//�����½��ٶ�

 Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
	 //Tetris��Ĺ��캯����������Ϸ�������������������߾ࡢ�ϱ߾�ͷ����С
{
	 this->rows = rows; //��ʼ����Ա����rows����ʾ��Ϸ��������
	 this->cols = cols; //��ʼ����Ա����cols����ʾ��Ϸ��������
	 this->leftMargin = left; //��ʼ����Ա����leftMargin����ʾ��Ϸ������߾�
	 this->topMargin = top; //��ʼ����Ա����topMargin����ʾ��Ϸ�����ϱ߾�
	 this->blockSize = blockSize; //��ʼ����Ա����blockSize����ʾ�����С

	 for (int i = 0; i < rows; i++) { //ѭ������һ����ά����map�����ڴ洢��Ϸ����ķ���״̬
		 vector<int>mapRow; //����һά����mapRow
		 for (int j = 0; j < cols; j++) { //ѭ��Ϊһά����mapRow���Ԫ��
			 mapRow.push_back(0); //���ֵΪ0��Ԫ�ص�һά����mapRowĩβ	�����

		 }
		 map.push_back(mapRow); //��һά����mapRow��ӵ���ά����mapĩβ	�б���
	 }


}

 void Tetris::init() //��ʼ����Ϸ�����ĺ���
 {
	 delay = SPEED_NORMAL; //��ʼ���ӳٲ���delay
	
	 srand(time(NULL)); //��ʼ�����������

	 initgraph(938, 896);//��ʼ����Ϸ����

	 loadimage(&imgBg, "res/bg2.png");//���ر���ͼƬ

	 char data[20][10];
	 for (int i = 0; i < rows; i++)
	 {
		 for (int j = 0; j < cols; j++)
		 {
			 map[i][j] = 0;
		 }
	 }

}

 void Tetris::play() //��ʼ��Ϸ�ĺ���
 {
	 init(); 
	 nextBlock = new Block;
	 curBlock = new Block;
	 nextBlock = new Block;

	 int timer = 0; //��ʼ����ʱ������timerΪ0
	 while (1) { //����ѭ��
		 //�����û�����
		 keyEvent(); //���ý����û�����ĺ���

		 timer += getDelay(); //���¼�ʱ������timer
		 if (timer > delay) { //�����ʱ������timer�����ӳٲ���delay
			 timer = 0; //����ʱ������timer����Ϊ0
			
			 drop(); //�������亯��

			 updata = true; //��������Ϸ�����־��Ϊtrue


		 }
		 if (updata) { //���������Ϸ�����־Ϊtrue
			 updata = false; //��������Ϸ�����־��Ϊfalse


			 //��Ⱦ��Ϸ����
			 updataWindow(); //���ø�����Ϸ����ĺ���

			 //������Ϸ����
			 clearLine(); //��������еĺ���
		 }


	 }
 }

 void Tetris::keyEvent() //�����û�����ĺ���
 {
	 unsigned char ch;

	 bool rotateFlag = false;	//��ת���
	 int dx = 0;

	 if (_kbhit() ){
		ch = _getch();

		if (ch == 224) {
			ch = _getch();
			switch(ch){
				case 72:
					rotateFlag = true;		//��ת����
					break;
				case 80:
					delay = SPEED_QUICK;
					break;
				case 75:
					dx = -1;
					break;
				case 77:
					dx = 1;
					break;
				default:
					break;

			}
		}
	 }

	 if (rotateFlag) {

		 //��ת����
	 }

	 if (dx != 0)
	 {
		 moveLeftRight(dx);//ʵ�������ƶ�
		 updata = true;
	 }


 }

 void Tetris::updataWindow() //������Ϸ����ĺ���
 {
	 putimage(0, 0, &imgBg);	//���Ʊ���ͼƬ

	 IMAGE** imgs = Block::getImages();
	 BeginBatchDraw();

	 for (int i = 0; i < rows; i++)
	 {
		 for (int j = 0; j < cols; j++)
		 {
			 if (map[i][j] == 0)continue;
			 int x = j * blockSize + leftMargin;
			 int y = i * blockSize + topMargin;
			 putimage(x, y, imgs[map[i][j]-1]);
		 }
	 }
	 curBlock->draw(leftMargin, topMargin);
	 nextBlock->draw(689, 150);
	 EndBatchDraw();
 }

 int Tetris::getDelay() //��ȡ��Ϸ�ӳٲ���delay�ĺ���
 {
	 static unsigned long long lastTime = 0;
	 unsigned long long currentTime = GetTickCount();

	 if (lastTime == 0)
	 {
		 lastTime = currentTime;
		 return 0;
	 }
	 else {
		 int ret = currentTime - lastTime;
		 lastTime = currentTime;
		 return ret;
	 }

 }

 void Tetris::drop() //�����Զ�������ĺ���
 {
	 bakBlock = *curBlock;
	 curBlock->drop();

	 if (!curBlock->blockInMap(map)) {
		 //�̶�����
		 bakBlock.solidify(map);
		 delete curBlock;
		 curBlock = nextBlock;
		 nextBlock = new Block;

	 }

	 delay = SPEED_NORMAL;

 }

 void Tetris::clearLine() //����Ѿ�������еĺ���
 {
 }

 void Tetris::moveLeftRight(int offset)
 {
	 bakBlock = *curBlock;
	 curBlock->moveLeftRight(offset);

	 if (!curBlock->blockInMap(map)) {
		 *curBlock = bakBlock;
	 }
 }
