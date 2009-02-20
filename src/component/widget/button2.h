#ifndef BUTTON2_H
#define BUTTON2_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duibuttonview.h>

#include <duibutton2view.h>

#include <duiwidgetview.h>
#include <duitheme.h>


class MainContainer : public QObject {

    public:
        MainContainer();

        void add(QString text1, QString text2);
        //void remove();

        DuiGridLayout* layout();

    private:
        DuiGridLayout* m_Layout;

        int m_PosX;
        int m_PosY;

        static const int layoutFieldWidth = 350;
        static const int layoutFieltHeight = 100;

};

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

        DuiWidgetView *m_BigButtonView;
        DuiWidgetView *m_SmallButtonView;

        DuiWidgetView* view;
        DuiButton* button2;

};

#endif
