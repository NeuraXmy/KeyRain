//Ui.h ui的初始化

#pragma once

class Layout;



namespace Ui
{
	extern Layout nullLayout;
	extern Layout gameLayout;
	extern Layout pauseLayout;

	//初始化ui
	void Init();
}