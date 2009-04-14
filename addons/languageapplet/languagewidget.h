#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "dcpwidget.h" 

class LanguageButton;
class DuiDialog;
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
    virtual bool back();
protected:
	void initWidget();

private:
    LanguageButton *m_displayButton;
    LanguageButton *m_keyboardButton;
    DuiDialog *m_Dlg;
private slots:
    virtual void displayPage();
    virtual void keyboardPage();
};
#endif // LANGUAGEWIDGET_H
