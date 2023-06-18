#include "Tetris.h"		
#include<time.h>		
#include<stdlib.h>
#include"Block.h"
#include<conio.h>
const int SPEED_NORMAL = 300;//ms 普通速度
const int SPEED_QUICK = 50;//快速下降速度

 Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
	 //Tetris类的构造函数，传入游戏界面的行数、列数、左边距、上边距和方块大小
{
	 this->rows = rows; //初始化成员变量rows，表示游戏界面行数
	 this->cols = cols; //初始化成员变量cols，表示游戏界面列数
	 this->leftMargin = left; //初始化成员变量leftMargin，表示游戏界面左边距
	 this->topMargin = top; //初始化成员变量topMargin，表示游戏界面上边距
	 this->blockSize = blockSize; //初始化成员变量blockSize，表示方块大小

	 for (int i = 0; i < rows; i++) { //循环创建一个二维数组map，用于存储游戏界面的方块状态
		 vector<int>mapRow; //创建一维数组mapRow
		 for (int j = 0; j < cols; j++) { //循环为一维数组mapRow添加元素
			 mapRow.push_back(0); //添加值为0的元素到一维数组mapRow末尾	点变行

		 }
		 map.push_back(mapRow); //将一维数组mapRow添加到二维数组map末尾	行变面
	 }


}

 void Tetris::init() //初始化游戏参数的函数
 {
	 delay = SPEED_NORMAL; //初始化延迟参数delay
	
	 srand(time(NULL)); //初始化随机数种子

	 initgraph(938, 896);//初始化游戏窗口

	 loadimage(&imgBg, "res/bg2.png");//加载背景图片

	 char data[20][10];
	 for (int i = 0; i < rows; i++)
	 {
		 for (int j = 0; j < cols; j++)
		 {
			 map[i][j] = 0;
		 }
	 }

}

 void Tetris::play() //开始游戏的函数
 {
	 init(); 
	 nextBlock = new Block;
	 curBlock = new Block;
	 nextBlock = new Block;

	 int timer = 0; //初始化计时器参数timer为0
	 while (1) { //无限循环
		 //接受用户输入
		 keyEvent(); //调用接受用户输入的函数

		 timer += getDelay(); //更新计时器参数timer
		 if (timer > delay) { //如果计时器参数timer大于延迟参数delay
			 timer = 0; //将计时器参数timer重置为0
			
			 drop(); //调用下落函数

			 updata = true; //将更新游戏画面标志设为true


		 }
		 if (updata) { //如果更新游戏画面标志为true
			 updata = false; //将更新游戏画面标志设为false


			 //渲染游戏界面
			 updataWindow(); //调用更新游戏界面的函数

			 //更新游戏画面
			 clearLine(); //调用清除行的函数
		 }


	 }
 }

 void Tetris::keyEvent() //接受用户输入的函数
 {
	 unsigned char ch;

	 bool rotateFlag = false;	//旋转标记
	 int dx = 0;

	 if (_kbhit() ){
		ch = _getch();

		if (ch == 224) {
			ch = _getch();
			switch(ch){
				case 72:
					rotateFlag = true;		//旋转功能
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

		 //旋转处理
	 }

	 if (dx != 0)
	 {
		 moveLeftRight(dx);//实现左右移动
		 updata = true;
	 }


 }

 void Tetris::updataWindow() //更新游戏界面的函数
 {
	 putimage(0, 0, &imgBg);	//绘制背景图片

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

 int Tetris::getDelay() //获取游戏延迟参数delay的函数
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

 void Tetris::drop() //方块自动往下落的函数
 {
	 bakBlock = *curBlock;
	 curBlock->drop();

	 if (!curBlock->blockInMap(map)) {
		 //固定方块
		 bakBlock.solidify(map);
		 delete curBlock;
		 curBlock = nextBlock;
		 nextBlock = new Block;

	 }

	 delay = SPEED_NORMAL;

 }

 void Tetris::clearLine() //清除已经满格的行的函数
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
