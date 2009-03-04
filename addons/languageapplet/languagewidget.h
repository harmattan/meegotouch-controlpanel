#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include <DuiWidget>

class LanguageWidget : public DuiWidget 
{
	Q_OBJECT
		
public:
	LanguageWidget(QGraphicsWidget *parent = 0);
	virtual ~LanguageWidget();

	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget = 0);

protected:
	void initWidget();
};
#endif // LANGUAGEWIDGET_H
