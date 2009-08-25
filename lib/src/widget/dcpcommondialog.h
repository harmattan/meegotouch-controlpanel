#ifndef DCPCOMMONDIALOG_H
#define DCPCOMMONDIALOG_H

#include <dcpdialog.h>

class DuiPannableViewport;
class DuiContainer;
class DuiLayout;
class DuiLinearLayoutPolicy;
class DuiSeparator;

class DcpCommonDialog : public DcpDialog
{
    Q_OBJECT

public:
    DcpCommonDialog(const QString &text, DuiWidget* parent = 0);
    virtual ~DcpCommonDialog();
    void setCentralWidget(DuiWidget *widget);
    DuiWidget* centralWidget();

protected:
    void initDialog();

private:
    QString m_TitleText;
    DuiPannableViewport *m_Viewport;
    DuiContainer *m_MainWidget;
    DuiLayout *m_ContainerLayout;
    DuiLinearLayoutPolicy *m_ContainerLayoutPolicy;
    DuiSeparator *m_GreySeparator;

};

#endif // DCPCOMMONDIALOG_H

