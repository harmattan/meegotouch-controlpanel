#ifndef LANGUAGELABEL_H
#define LANGUAGELABEL_H

#include <DuiWidget>

class LanguageLabel : public DuiWidget
{
    Q_OBJECT

public:
    LanguageLabel(const QString &upText, 
                  const QString &downText,
                  DuiWidget *parent = 0);
    LanguageLabel(const QString &text,
                  DuiWidget *parent = 0);
    virtual ~LanguageLabel();

    //! \reimp
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = 0);
    //! \reimp_end

protected:
    void initWidget();

protected slots:
   void onOrientationAngleChanged();

private:
    QString m_upText;
    QString m_downText;
};
#endif // LANGUAGELABEL_H
