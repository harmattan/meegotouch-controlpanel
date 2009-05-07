#ifndef LANGUAGELABEL_H
#define LANGUAGELABEL_H

#include <DuiWidget>

class DuiSeparator;

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

protected:
    void initWidget();

protected slots:
   void onOrientationAngleChanged();

private:
    QString m_UpText;
    QString m_DownText;
    DuiSeparator *m_GreySeparator;
};
#endif // LANGUAGELABEL_H
