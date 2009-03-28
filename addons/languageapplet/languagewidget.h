#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "dcpwidget.h" 

class LanguageButton;

class LanguageWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	LanguageWidget(QGraphicsWidget *parent = 0);
	virtual ~LanguageWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);

protected:
	void initWidget();

private:
    LanguageButton *m_displayButton;
    LanguageButton *m_keyboardButton;
};
#endif // LANGUAGEWIDGET_H
