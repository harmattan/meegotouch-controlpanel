#ifndef DCPIMAGEUTILS_H
#define DCPIMAGEUTILS_H

#include <QPixmap>
#include <QString>
class QPixmapCache;

class DcpImageUtils {
public:
    static DcpImageUtils* instance();
    static QPixmap borderCorrectScale(const QPixmap& pixmap,
                           int newWidth, int newHeight = -1,
                           int borderSize = 20);
    QPixmap scaledPixmap(const QString& id, int newWidth,
                          int newHeight = -1, int borderSize = 20);

protected:
    DcpImageUtils();
    static DcpImageUtils* sm_Instance;

    QPixmapCache* m_PixmapCache;
};


inline DcpImageUtils* DcpImageUtils::instance() {
    if (!sm_Instance) sm_Instance = new DcpImageUtils;
    return sm_Instance;
}

#endif // DCPIMAGEUTILS_H
