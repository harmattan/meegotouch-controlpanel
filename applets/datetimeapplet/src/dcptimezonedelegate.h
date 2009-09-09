#ifndef DCPTIMEZONEDELEGATE_H
#define DCPTIMEZONEDELEGATE_H

#include "dcptabledelegate.h"

class QPixmap;

class DcpTimeZoneDelegate: public DcpTableDelegate
{
    Q_OBJECT
public:
    DcpTimeZoneDelegate();
    virtual ~DcpTimeZoneDelegate();

    virtual void setWidth (int width);
    enum {
        TextRole1 = 1000,
        TextRole2,
        CheckedRole
    };

    virtual void paint ( QPainter * painter, const QModelIndex & index ) const;

private:
    int m_FontAscent;
    int m_FontDescent;
    const QPixmap* m_OkPic;
    const QPixmap* m_LinePic;
};


#endif // DCPTIMEZONEDELEGATE_H
