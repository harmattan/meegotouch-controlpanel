#ifndef DCPDESKTOPENTRY_H
#define DCPDESKTOPENTRY_H

#include <duidesktopentry.h>

class QString;

class DcpDesktopEntry : public DuiDesktopEntry
{
    Q_OBJECT

public:
    DcpDesktopEntry(const QString &fileName);
    ~DcpDesktopEntry();

    QString widgetType();

    QString text1();
    QString text2();

    QString image();

    QString buttonCSS();
    QString label1CSS();
    QString label2CSS();

//public slots:

private:

};

#endif // MAINWINDOW_H
