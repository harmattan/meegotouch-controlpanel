#include <DcpContentItem>
#include <QHash>

class DcpAppletObject;
static QHash<const DcpContentItem*, DcpAppletObject*> applets;

DcpContentItem::DcpContentItem(DcpAppletObject* applet, QGraphicsItem*): d_ptr(0)
{
    setApplet(applet);
}

DcpContentItem::~DcpContentItem(){}

void DcpContentItem::setApplet(DcpAppletObject* applet)
{
    applets[this] = applet;
}

DcpAppletObject* DcpContentItem::applet() const{ return applets[this]; }

void DcpContentItem::setMattiID(const QString&) {}
QString DcpContentItem::mattiID() const {return QString(); }
void DcpContentItem::updateContents(){}
void DcpContentItem::retranslateUi(){}
void DcpContentItem::showEvent(QShowEvent*){}
void DcpContentItem::hideEvent(QHideEvent*){}
void DcpContentItem::constructRealWidget(){}
void DcpContentItem::updateText(){}
void DcpContentItem::updateImage(){}
void DcpContentItem::setImageFromFile(const QString&){}
void DcpContentItem::setImageName(const QString&){}
void DcpContentItem::releaseImage(){}
void DcpContentItem::invertTwoLineMode(){}

