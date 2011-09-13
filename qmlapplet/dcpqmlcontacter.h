#ifndef DCPQMLCONTACTER_H
#define DCPQMLCONTACTER_H

#include <QObject>

class DcpQmlContacter: public QObject
{
    Q_OBJECT
    Q_PROPERTY (bool isStandalone READ isStandalone)

public:
    DcpQmlContacter();
    virtual ~DcpQmlContacter();

    bool isStandalone () const;
    Q_INVOKABLE void popupMainPageAlone ();

};


#endif // DCPQMLCONTACTER_H

