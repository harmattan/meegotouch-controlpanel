#ifndef LANGUAGEBUTTON_H
#define LANGUAGEBUTTON_H

#include <DuiButton>
class DuiLabel;
// class QPixmap;

class LanguageButton : public DuiButton 
{
    Q_OBJECT
                
public:
    LanguageButton(QString upText, 
                   QString downText, 
                   DuiWidget *parent = 0);

    virtual ~LanguageButton();

    //! \reimp
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
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
    // const QPixmap *m_Background;
};
#endif
