#include <QObject>

// copied from widgetsgallery, makes translation reload automatically
class DcpRetranslator : public QObject
{
    Q_OBJECT

public slots:
   void retranslate();
};


