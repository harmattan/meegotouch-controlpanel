#ifndef TESTWIDGET_H__
#define TESTWIDGET_H__

#include <DuiLabel>

class TestWidget : public DuiLabel
{
    Q_OBJECT

    public:
        TestWidget(QString const &text, DuiWidget *parent=0);
        virtual ~TestWidget();

};

#endif // TESTWIDGET_H__
