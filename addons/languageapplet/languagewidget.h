#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "dcpwidget.h" 

class DcpButton2;
class DcpDialog;

class LanguageWidget : public DcpWidget 
{
	Q_OBJECT
		
public:
	LanguageWidget(QGraphicsWidget *parent = 0);
	virtual ~LanguageWidget();
    virtual bool back();
    
protected:
	void initWidget();
    void updateLanguageButtons();

private:
    DcpButton2 *m_DisplayButton;
    DcpButton2 *m_KeyboardButton;
    DcpDialog *m_Dlg;
    
public slots:
    virtual void displayPage();
    virtual void keyboardPage();
};
#endif // LANGUAGEWIDGET_H

