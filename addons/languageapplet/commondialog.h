#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <dcpdialog.h>

class DuiContainer;
class DuiLayout;
class DuiLinearLayoutPolicy;

class CommonDialog : public DcpDialog
{
    Q_OBJECT

public:
    CommonDialog(const QString &text);
    virtual ~CommonDialog();
    void setCentralWidget(DuiWidget *widget);
    DuiWidget* centralWidget();

protected:
    void initDialog();
    
private:
    QString m_TitleText;
    DuiContainer *m_MainWidget;
    DuiLayout *m_ContainerLayout;
    DuiLinearLayoutPolicy *m_ContainerLayoutPolicy;

private slots:
    virtual void onOrientationAngleChanged();
};
#endif // COMMONDIALOG_H
