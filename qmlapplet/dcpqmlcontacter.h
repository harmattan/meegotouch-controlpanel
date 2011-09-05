#ifndef DCPQMLCONTACTER_H
#define DCPQMLCONTACTER_H

#include <QObject>

class DcpQmlContacter: public QObject
{
    Q_OBJECT

public:
    DcpQmlContacter();
    virtual ~DcpQmlContacter();

    Q_INVOKABLE void newPage (const QString& url);
};


#endif // DCPQMLCONTACTER_H

