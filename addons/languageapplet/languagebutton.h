#ifndef LANGUAGEBUTTON_H
#define LANGUAGEBUTTON_H

#include <DuiWidget>
class DuiGridLayout;
class DuiButton;
class DuiLabel;

class LanguageButton : public DuiWidget 
{
        Q_OBJECT
                
public:
    LanguageButton(QString upText, 
                   QString downText, 
                   QGraphicsWidget *parent = 0);

    virtual ~LanguageButton();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

    void resizeEvent(QGraphicsSceneResizeEvent *event);
    
protected:
    void initWidget();

private:
    QString m_upText;
    QString m_downText;
    DuiGridLayout *mainLayout;
    DuiButton *m_bigButton;
    DuiLabel *m_leftLabel;
    DuiLabel *m_rightLabel;
};
#endif
