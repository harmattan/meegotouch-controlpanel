#ifndef DCPCOMMONDIALOG_H
#define DCPCOMMONDIALOG_H

#include <dcpdialog.h>

class DuiPannableViewport;
class DuiContainer;
class DuiLayout;
class DuiLinearLayoutPolicy;
class DuiSeparator;
class DuiLabel;

class DcpCommonDialog : public DcpDialog
{
    Q_OBJECT

public:
    DcpCommonDialog(const QString &text, DuiWidget* parent = 0);
    virtual ~DcpCommonDialog();
    void setCentralWidget(DuiWidget *widget);
    DuiWidget* centralWidget();
    void setTitle(const QString& title);

protected:
    void initDialog();

private:
    DuiPannableViewport *m_Viewport;
    DuiContainer *m_MainWidget;
    DuiLayout *m_ContainerLayout;
    DuiLinearLayoutPolicy *m_ContainerLayoutPolicy;
    DuiSeparator *m_GreySeparator;
    DuiLabel* m_TitleLabel;
};

#endif // DCPCOMMONDIALOG_H

