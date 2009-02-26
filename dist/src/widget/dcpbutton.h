#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>



class DcpButton : public QObject{

    Q_OBJECT;

    public:

        DcpButton(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable = true);

        void setEnable(bool enable);

        DuiGridLayout* layout();

    private slots:
        void bigClicked();
        void smallClickedOn();
        void smallClickedOff();
        void disableClicked();

    signals:
        void clicked(QString);

    protected:
        DuiGridLayout* m_Layout;

        DuiButton* m_BigButton;

        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;

        DuiButton* m_DisableButton;

        bool m_Enable;
};

#endif
