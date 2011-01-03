#ifndef STREAM_H
#define STREAM_H

class QTextStream;
class QIODevice;
#include <QObject>

class Stream: public QObject
{
    Q_OBJECT

public:
    Stream (QObject* parent);
    ~Stream ();

    void setIODevice (QIODevice* device);
    void flush ();
    void writeLine (const QString& st);

signals:
    void newCommand (const QString& command);

protected slots:
    void onReadyRead ();

private:
    QTextStream* m_Text;
};


#endif // STREAM_H

