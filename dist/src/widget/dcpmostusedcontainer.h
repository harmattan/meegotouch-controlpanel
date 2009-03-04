#ifndef DCPMOSTUSEDCONTAINER_H
#define DCPMOSTUSEDCONTAINER_H

#include <DuiApplicationPage>

#include "duigridlayout.h"

#include <duibutton.h>
#include <duibuttonview.h>

#include <duiwidgetview.h>
#include <duitheme.h>
class DcpAppletMetadata;

class DcpMostUsedContainer : public QObject {

    public:
        DcpMostUsedContainer();

        void add(const QString& file);
        void add(DcpAppletMetadata *metadata);
        void addButton(const QString& text1, const QString& text2, bool enable = true, int length = 1);
        void addLabel(const QString& text1, const QString& text2);

        void addLabelCSS(const QString& text1, const QString& text2, const QString& cssButton, const QString& cssUpLabel, const QString& cssDownLabel);

        void addImageCSS(const QString& text, const QString& image, const QString& cssButton, const QString& cssUpLabel);

        //void remove();

        DuiGridLayout* layout();

        void addPos();
        void addPos2();

    private:
        DuiGridLayout* m_Layout;

        int m_PosX;
        int m_PosY;

        static const int layoutFieldWidth = 350;
        static const int layoutFieltHeight = 100;
};

#endif
