#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include <DuiWidget>

class LanguageButton;

class LanguageWidget : public DuiWidget 
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
