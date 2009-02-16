#ifndef BUTTON2_H
#define BUTTON2_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>



class CButton2 : public QObject{

    Q_OBJECT;

    public:

        CButton2(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight);

        DuiGridLayout* layout();

    private slots:
        void bigClicked();
        void smallClicked();

    signals:
        void clicked(QString);

    protected:
        DuiGridLayout* m_Layout;

        DuiButton* m_BigButton;
        DuiButton* m_SmallButton;
};

#endif
