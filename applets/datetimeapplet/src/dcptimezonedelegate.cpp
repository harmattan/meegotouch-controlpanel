#include "dcptimezonedelegate.h"

#include <DuiTheme>

#include <QPainter>
#include <QModelIndex>
#include <QtDebug>

// TODO make it styleable:
static const int border = 16;
static const int lineBorder = 4;
static const QFont font1 = QFont("Nokia Sans", 16);
static const QFont font2 = QFont("Nokia Sans", 12);
static const QColor textColor = Qt::white;

DcpTimeZoneDelegate::DcpTimeZoneDelegate()
{
    m_FontAscent = QFontMetrics(font1).ascent();
    m_FontDescent = QFontMetrics(font2).descent();
    // TODO make it styleable:
    m_OkPic = DuiTheme::pixmap("Check-mark");
    m_LinePic = DuiTheme::pixmap("Task-switcher-background-bottom-lines");
    setHeight(80);
}

DcpTimeZoneDelegate::~DcpTimeZoneDelegate()
{
    if (m_OkPic) DuiTheme::releasePixmap(m_OkPic);
    if (m_LinePic) DuiTheme::releasePixmap(m_LinePic);
}

void
DcpTimeZoneDelegate::paint ( QPainter * painter, const QModelIndex & index ) const
{
    Q_UNUSED (index);

    QString line1 = index.data(TextRole1).toString();
    QString line2 = index.data(TextRole2).toString();
    bool isChecked = !index.data(NotCheckedRole).toBool();

    painter->setPen(textColor);
    painter->setFont(font1);
    painter->drawText(border, border + m_FontAscent, line1);
    painter->setFont(font2);
    painter->drawText(border, m_Height - border - m_FontDescent, line2);
/*
    painter->setPen(lineColor);
    painter->drawLine(lineBorder, height(), width()-lineBorder, height());
 */
    if (m_LinePic) {
        painter->drawPixmap(lineBorder, m_Height-m_LinePic->height(), *m_LinePic);
    }

    if (isChecked && m_OkPic) {
        // TODO most values can be cached, and refreshed on setWidth
        int x = width()-border-m_OkPic->width(); // aligned right
        int y = (height() - m_OkPic->height()) / 2; // centered vertically
        painter->drawPixmap(x, y, *m_OkPic);
    }
}


void
DcpTimeZoneDelegate::setWidth(int width)
{
    int pixmapWidth = width -2*lineBorder;
    if (!m_LinePic || m_LinePic->width() != pixmapWidth) {
        int height = 3;
        if (m_LinePic) {
            height = m_LinePic->height();
            DuiTheme::releasePixmap(m_LinePic);
        }
        m_LinePic = DuiTheme::pixmap("Task-switcher-background-bottom-lines",
                QSize(pixmapWidth, height));
    }
    DcpTableDelegate::setWidth(width);
}

