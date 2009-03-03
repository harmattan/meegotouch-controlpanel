#ifndef DCPLABEL_H
#define DCPLABEL_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duilabel.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>

class DcpLabel : public QObject{

    Q_OBJECT;

    public:

        DcpLabel(const QString& upLabel, const QString& downLabel, int width, int upHeight, int downHeight, const QString& cssButton = "", const QString& cssUpLabel = "", const QString& cssDownLabel = "");


        DuiGridLayout* layout();

    private slots:
        void labelButtonClicked();
        //void smallClickedOn();
        //void smallClickedOff();
        //void disableClicked();

    signals:
        void clicked(QString);

    protected:
        DuiGridLayout* m_Layout;

        DuiButton* m_Button;

        DuiLabel* m_UpLabel;
        DuiLabel* m_DownLabel;
};

#endif
