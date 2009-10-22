#include <QObject>

// copied from widgetsgallery, makes translation reload automatically
class Retranslator : public QObject
{
    Q_OBJECT

public slots:
   void retranslate();
};


