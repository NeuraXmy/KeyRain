//UiManager.h�� ui����������

#pragma once

#include <qwidget.h>

#include <list>

class Layout;
class GameManager;



/**
* UiManager (QWidget)
* ����ui�ĵ�������
*/
class UiManager : public QWidget
{
	Q_OBJECT

public:

	static UiManager* GetInstance();

	static void ReleaseInstance();



	UiManager();

	~UiManager();



	//�������
	void Enter(Layout* layout);

	//������һ������
	void Back();



	//����
	void Draw(QPainter* painter) const;

	//��layout��ӵ������б�
	void AddDrawList(Layout* layout);



	void OnKeyPressEvent(int key);

	void OnKeyReleaseEvent(int key);

	void OnMouseMoveEvent(int mouseX, int mouseY);

	void OnMouseLeftBtnPressEvent();

	void OnMouseLeftBtnReleaseEvent();

protected:

	void timerEvent(QTimerEvent* event) override;

private:

	std::list<Layout*> layouts;

	std::list<Layout*> drawList;

	int time;

	int timerId;
};
