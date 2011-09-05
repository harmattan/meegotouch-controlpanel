#include <QtCore>
#include <QtDeclarative>

class MGConfItem;

 class DcpQmlGConfItem : public QObject
 {
     Q_OBJECT
     Q_PROPERTY(QString key READ key WRITE setKey)
     Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

 public:
     DcpQmlGConfItem(QObject *parent = 0);
     
     const QString key() const;
     void setKey(const QString key);
     
     const QString value() const;
     void setValue(const QString value);

 signals:
     void valueChanged();
     
 private:
     MGConfItem *item;
 };
