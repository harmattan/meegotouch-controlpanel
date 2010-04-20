#ifndef TESTWIDGET_H__
#define TESTWIDGET_H__

#include <MLabel>

class TestWidget : public MLabel
{
    Q_OBJECT

    public:
        TestWidget(QString const &text, MWidget *parent=0);
        virtual ~TestWidget();

};

#endif // TESTWIDGET_H__
