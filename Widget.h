//Widget.h: �ؼ�����

#pragma once

#include <qobject.h>

class QPainter;



//�ؼ���ê��λ��
enum class Anchor
{
	Center,
	LeftBottom
};



/**
* Widget (QObject)
* ����ui�еĿؼ��ĳ���ӿ�����
*/
class Widget : public QObject
{
	Q_OBJECT

public:

	int x;
	int y;

	int w;
	int h;

	//ê��λ��(Ĭ��Ϊ����)
	Anchor anchor;

	bool visible;

	//�Ƿ��ڵ�ǰ�Ľ���
	bool inCurrentLayout;



	Widget();
	
	virtual ~Widget();


	virtual void Reset();

	virtual void Update(int time);

	virtual void Draw(QPainter* painter) const;



	virtual void OnKeyPressEvent(int key);

	virtual void OnKeyReleaseEvent(int key);

	virtual void OnMouseMoveEvent(int mouseX, int mouseY);

	virtual void OnMouseLeftBtnPressEvent();

	virtual void OnMouseLeftBtnReleaseEvent();

protected:
	
	//�������Ƿ��ڿؼ���
	bool isMouseHover(int mouseX, int mouseY) const;

};
