#include <MTheme>

const QPixmap * MTheme::pixmap (
        const QString &, const QSize &)
{
    return (QPixmap*)1; // !!! please do not use this pixmap ever
                        // it is an easy solution to avoid running
                        // QPixmap's constructor which requires
                        // a QApplication which requires X
}

void MTheme::releasePixmap (const QPixmap *)
{
}

