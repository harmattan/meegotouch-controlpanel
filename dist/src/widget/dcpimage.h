#ifndef DCPIMAGE_H
#define DCPIMAGE_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duilabel.h>
#include <duiimage.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>



class DcpImage : public QObject{

    Q_OBJECT;

    public:

        DcpImage(const QString& label, const QString& image, int width, int upHeight, int downHeight, int imageWidth, const QString& cssButton = "", const QString& cssLabel = "");


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

        DuiLabel* m_Label;
        DuiImage* m_Image;
};

#endif
