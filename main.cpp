/*开发日志
* 1.创建项目
* 2.拷贝文件（倒入素材）
* 3.C++开发
* 4.设计C++项目模块
*	设计类：
*	Block 表示方块
*	Tetris 标识俄罗斯方块
* 5.设计各个模块接口
* 6.启动游戏
*/

#include"Tetris.h"
int main(void)
{
	Tetris game(20, 10, 263, 133, 36);
	game.play();
	
	//system("pause");
	return 0;
}