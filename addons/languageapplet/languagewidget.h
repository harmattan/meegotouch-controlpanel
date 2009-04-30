#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "dcpwidget.h" 

class LanguageButton;
class DcpDialog;

class LanguageWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	LanguageWidget(QGraphicsWidget *parent = 0);
	virtual ~LanguageWidget();
    // !reimp
	void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    // !reimp_end
    virtual bool back();
    
protected:
	void initWidget();
    void updateLanguageButtons();

private:
    LanguageButton *m_DisplayButton;
    LanguageButton *m_KeyboardButton;
    DcpDialog *m_Dlg;
    
private slots:
    virtual void displayPage();
    virtual void keyboardPage();
};
#endif // LANGUAGEWIDGET_H
