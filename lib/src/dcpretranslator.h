#ifndef DCP_RETRANSLATOR_H
#define DCP_RETRANSLATOR_H

#include <QObject>

// copied from widgetsgallery, makes translation reload automatically
class DcpRetranslator : public QObject
{
    Q_OBJECT

public slots:
   void retranslate();
};

#endif // DCP_RETRANSLATOR_H

