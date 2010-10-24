#ifndef STREAM_H
#define STREAM_H

class QTextStream;
class QIODevice;
#include <QThread>
#include <QMutex>

class Stream: public QThread
{
    Q_OBJECT

public:
    Stream (QObject* parent);
    ~Stream ();
    void run();

    void setIODevice (QIODevice* device);
    void flush ();
    void writeLine (const QString& st);

signals:
    void newCommand (const QString& command);

protected slots:
    void onReadyRead ();

private:
    QTextStream* m_Text;
    QMutex m_Lock;
};


#endif // STREAM_H

