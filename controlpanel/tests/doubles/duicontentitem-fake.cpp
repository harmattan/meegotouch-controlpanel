#include <duicontentitem.h>

/* Fake DuiContentItem
 */
class DuiContentItemFake 
{
public:
    QString m_Title;
    QString m_Subtitle;
};

DuiContentItemFake f;

DuiContentItem::DuiContentItem(DuiContentItem::ContentItemStyle,
                               QGraphicsItem*)
{
}

DuiContentItem::DuiContentItem(DuiContentItemPrivate*, DuiContentItemModel*,
                               QGraphicsItem* )
{}

DuiContentItem::~DuiContentItem(){}

QPixmap DuiContentItem::pixmap() const{ return QPixmap(); }
QImage DuiContentItem::image() const{ return QImage(); }

QString DuiContentItem::title() const
{
    return f.m_Title;
}

QString DuiContentItem::subtitle() const
{
    return f.m_Subtitle;
}

DuiContentItem::ContentItemMode DuiContentItem::itemMode() const
{
    return Default;
}

DuiContentItem::ContentItemStyle DuiContentItem::itemStyle() const
{
    return TwoTextLabels;
}

DuiWidget* DuiContentItem::additionalItem() const{ return 0; }
DuiWidget* DuiContentItem::smallItem() const{ return 0; }
QPixmap DuiContentItem::optionalPixmap() const{ return QPixmap(); }
QImage DuiContentItem::optionalImage() const{ return QImage(); }
void DuiContentItem::setPixmap(const QPixmap &){}
void DuiContentItem::setImage(const QImage &){}

void DuiContentItem::setTitle(const QString &title)
{
    f.m_Title = title;
}

void DuiContentItem::setSubtitle(const QString &subtitle)
{
    f.m_Subtitle = subtitle;
}
void DuiContentItem::setItemMode(ContentItemMode){}
void DuiContentItem::setAdditionalItem(DuiWidget*){}
void DuiContentItem::enableProgressBar(){}
void DuiContentItem::setSmallItem(DuiWidget*){}
void DuiContentItem::setSmallText(QString){}
void DuiContentItem::setOptionalPixmap(const QPixmap&){}
void DuiContentItem::setOptionalImage(const QImage&){}
void DuiContentItem::click(){}
QVariant DuiContentItem::itemChange(GraphicsItemChange, const QVariant &)
{
    return QVariant();
}



