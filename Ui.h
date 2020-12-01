#pragma once

class Layout;
class UiManager;
class GameManager;
class Button;

namespace Ui
{
	extern Layout nullLayout;
	extern Layout gameLayout;
	extern Layout pauseLayout;

	void Init(GameManager* game, UiManager* mgr);
}