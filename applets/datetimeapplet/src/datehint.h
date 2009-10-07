#ifndef DATEHINT_H
#define DATEHINT_H

#include <QObject>

namespace Cellular {
    class NetworkTime;
};
class QDateTime;

class DateHint: public QObject
{
    Q_OBJECT
public:
    static void startHintIfNeeded();
    static bool isDateValid();
    static bool isDateValid(const QDateTime&);

protected slots:
    void onDateTimeChanged (QDateTime dateTime, int timezone, int dst);

protected:
    DateHint(QObject* parent = 0);
    static DateHint* sm_Instance;

    Cellular::NetworkTime* m_NetworkTime;
};


#endif // DATEHINT_H

