#ifndef BUTTON2_H
#define BUTTON2_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>



class CButton2 : public QObject{

    Q_OBJECT;

    public:

        CButton2(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable = true);

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
