#include "dcptimezonedelegate.h"

#include <DuiTheme>

#include <QPainter>
#include <QModelIndex>
#include <QtDebug>

// TODO make it styleable:
static const int border = 16;
static const QFont font1 = QFont("Nokia Sans", 16);
static const QFont font2 = QFont("Nokia Sans", 14);

DcpTimeZoneDelegate::DcpTimeZoneDelegate()
{
    m_FontAscent = QFontMetrics(font1).ascent();
    m_FontDescent = QFontMetrics(font2).descent();
    // TODO make it styleable:
    m_OkPic = DuiTheme::pixmap("Check-mark");
    setHeight(80);
}


void
DcpTimeZoneDelegate::paint ( QPainter * painter, const QModelIndex & index ) const
{
    Q_UNUSED (index);

    QString line1 = index.data(TextRole1).toString();
    QString line2 = index.data(TextRole2).toString();
    bool isChecked = !index.data(NotCheckedRole).toBool();

    painter->setFont(font1);
    painter->drawText(border, border + m_FontAscent, line1);
    painter->setFont(font2);
    painter->drawText(border, m_Height - border - m_FontDescent, line2);
    painter->drawLine(0, height(), width(), height());

    if (isChecked && m_OkPic) {
        // TODO most values can be cached, and refreshed on setWidth
        int x = width()-border-m_OkPic->width(); // aligned right
        int y = (height() - m_OkPic->height()) / 2; // centered vertically
        painter->drawPixmap(x, y, *m_OkPic);
    }
}

