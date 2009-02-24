#ifndef MOSTUSEDCONTAINER_H
#define MOSTUSEDCONTAINER_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>


class MostUsedContainer : public QObject {

    public:
        MostUsedContainer();

        void add(QString text1, QString text2, bool enable = true);
        //void remove();

        DuiGridLayout* layout();

    private:
        DuiGridLayout* m_Layout;

        int m_PosX;
        int m_PosY;

        static const int layoutFieldWidth = 350;
        static const int layoutFieltHeight = 100;

};

#endif
