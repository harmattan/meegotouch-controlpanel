#ifndef READER_H
#define READER_H

class QTextStream;
class QIODevice;
#include <QThread>

class Reader: public QThread
{
    Q_OBJECT

public:
    Reader (QObject* parent);
    void run();

    void setIODevice (QIODevice* device);

signals:
    void newCommand (const QString& command);

protected slots:
    void onReadyRead ();

private:
    QTextStream* m_Input;

};


#endif // READER_H
