#ifndef DCPIMAGEUTILS_H
#define DCPIMAGEUTILS_H

#include <QPixmap>


QPixmap borderCorrectScale(const QPixmap& pixmap,
                           int newWidth, int newHeight = -1,
                           int borderSize = 20);


#endif // DCPIMAGEUTILS_H
