#ifndef DCPSPEC_H
#define DCPSPEC_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duilabel.h>
#include <duiimage.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>


class DcpSpec : public QObject{

    Q_OBJECT;

    public:

        DcpSpec(const QString& image, int width, int height, int smallWidth, int smallHeight, const QString& css);


        DuiGridLayout* layout();

    DuiImage* initImageFix(const QPixmap* pixmap, int x, int y, int width, int height);

    DuiImage* initImageResize(const QPixmap* pixmap, int x, int y, int width, int height, int newWidth, int newHeight);

    private slots:
        void labelButtonClicked();
        //void smallClickedOn();
        //void smallClickedOff();
        //void disableClicked();

    signals:
        void clicked(QString);

    protected:
        DuiGridLayout* m_Layout;


        DuiImage* m_ImageLeftUp;
        DuiImage* m_ImageLeftMiddle;
        DuiImage* m_ImageLeftDown;

        DuiImage* m_ImageUp;
        DuiImage* m_ImageMiddle;
        DuiImage* m_ImageDown;

        DuiImage* m_ImageRightUp;
        DuiImage* m_ImageRightMiddle;
        DuiImage* m_ImageRightDown;
};

#endif
