#ifndef DCPDECLWIDGET_H
#define DCPDECLWIDGET_H

#include "dcpwidget.h"

class DcpDeclWidget: public DcpWidget
{
    Q_OBJECT
public:
    DcpDeclWidget(const QString& xmlPath);

private:
    void createErrorLabel(const QString& text);

};


#endif // DCPDECLWIDGET_H
