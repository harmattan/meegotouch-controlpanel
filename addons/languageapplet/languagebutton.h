#ifndef LANGUAGEBUTTON_H
#define LANGUAGEBUTTON_H

#include <DuiButton>
class DuiLabel;
class QPixmap;

class LanguageButton : public DuiButton 
{
        Q_OBJECT
                
public:
    LanguageButton(QString upText, 
                   QString downText, 
                   DuiWidget *parent = 0);

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
    DuiLabel *m_upLabel;
    DuiLabel *m_downLabel;
    const QPixmap *m_Background;
};
#endif
