#include "dcpimageutils.h"


#include <QPainter>

/** @brief Scales a pixmap with preserving its border size to avoid artifacts.
  * @param pixmap       The pixmap
  * @param newWidth     The new width, if -1, leaves the width the same.
  * @param newHeight    The new height, if -1, leaves the height the same.
  * @param borderSize   The size of the border that is to be preserved during
  *                     the scale.
  */
QPixmap borderCorrectScale(const QPixmap& pixmap,
                           int newWidth, int newHeight, int borderSize) {
    QPixmap result(newWidth, newHeight);
    result.fill(Qt::transparent);
    QPainter painter(&result);

    /* The picture is cutted to these pieces:
       pic11 | pic12 | pic13
       ---------------------  -> borderSize
       pic21 | pic22 | pic23
       ---------------------  -> height2
       pic31 | pic32 | pic33
             |       V
             V     width2
         borderSize

       and scaled to:
       pic11 |  <->  | pic13
       ---------------------  -> borderSize
          L  |   *   |   L
       ---------------------  -> newHeight2
       pic31 |  <->  | pic33
             |       V
             V    newWidth2
         borderSize
     */
    int height  = pixmap.height();
    int width   = pixmap.width();
    int height2 = height - borderSize;
    int width2  = width - borderSize;

    if (newHeight <= 0) {
        newHeight = height;
    }
    if (newWidth <= 0) {
        newWidth = width;
    }
    int newHeight2  = newHeight - borderSize;
    int newWidth2   = newWidth - borderSize;

    // paint the CORNERS (they dont need to be scaled):
    QRect fromRect(0,0,borderSize,borderSize);
    QRect toRect(0,0,borderSize,borderSize);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.moveTop(height2);
    toRect.moveTop(newHeight2);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.moveLeft(width2);
    toRect.moveLeft(newWidth2);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.moveTop(0);
    toRect.moveTop(0);
    painter.drawPixmap(toRect, pixmap, fromRect);

    // paint the edges:
    fromRect.setRect(borderSize, 0, width2-borderSize, borderSize);
    toRect.setRect(borderSize, 0, newWidth2-borderSize, borderSize);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.moveTop(height2);
    toRect.moveTop(newHeight2);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.setRect(0, borderSize, borderSize, height2 - borderSize);
    toRect.setRect(0, borderSize, borderSize, newHeight2 - borderSize);
    painter.drawPixmap(toRect, pixmap, fromRect);

    fromRect.moveLeft(width2);
    toRect.moveLeft(newWidth2);
    painter.drawPixmap(toRect, pixmap, fromRect);

    // paint the content:
    fromRect.setRect(borderSize, borderSize,
                     width2-borderSize, height2-borderSize);
    toRect.setRect(borderSize, borderSize,
                   newWidth2-borderSize, newHeight2-borderSize);
    painter.drawPixmap(toRect, pixmap, fromRect);
    return result;
}

