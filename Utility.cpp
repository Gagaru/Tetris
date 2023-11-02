#include<windows.h>

//颜色控制函数
void color(const unsigned short COLorl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLorl);

}

void gotoXY(int goRow, int goCol)
{
	COORD pos = { 2 * goCol,goRow };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

//隐藏光标函数
void HideCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,isVisible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}