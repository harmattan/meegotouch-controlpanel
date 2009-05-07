#ifndef LANGUAGEBUTTON_H
#define LANGUAGEBUTTON_H

#include <DuiButton>

class DuiLabel;
class DuiSeparator;

class LanguageButton : public DuiButton 
{
    Q_OBJECT
                
public:
    LanguageButton(QString upText, 
                   QString downText, 
                   DuiWidget *parent = 0);
    virtual ~LanguageButton();
    //! \reimp
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    //! \reimp_end
    void setUpText(const QString &text);
    void setDownText(const QString &text);
    
protected:
    void initWidget();

private:
    QString m_UpText;
    QString m_DownText;
    DuiLabel *m_UpLabel;
    DuiLabel *m_DownLabel;
    DuiSeparator *m_GreySeparator;

private slots:
    virtual void onOrientationAngleChange();
};
#endif
