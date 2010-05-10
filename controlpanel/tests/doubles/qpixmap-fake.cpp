#include <QPaintDevice>
#include <QPixmap>
QPaintDevice::QPaintDevice(){};
QPixmap::QPixmap() : QPaintDevice(){ }
/*
QPixmap::QPixmap(int, int){}
QPixmap::QPixmap(const QString &, const char *, 
                 Qt::ImageConversionFlags){}
QPixmap::QPixmap ( const char * const[] xpm ){}
QPixmap::QPixmap ( const QPixmap &): QPaintDevice(){}
QPixmap::QPixmap ( const QSize &){}
*/
