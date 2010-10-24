#include "stream.h"

#include <QTextStream>
#include <QIODevice>
#include <QMutexLocker>


Stream::Stream(QObject* parent):
    QThread (parent),
    m_Text (new QTextStream ())
{
}

Stream::~Stream ()
{
    delete m_Text;
}

void Stream::run()
{
    exec ();
}

void Stream::onReadyRead ()
{
    QString st;
    do {
        {
            QMutexLocker (&this->m_Lock);
            st = m_Text->readLine ();
        }
        if (!st.isEmpty()) {
            emit newCommand (st);
        } else {
            if (st.isNull()) {
                // end of data
                return;
            }
        }
    } while (!st.isNull());
}

void Stream::setIODevice (QIODevice* device)
{
    QMutexLocker (&this->m_Lock);
    QIODevice* lastDevice = m_Text->device ();

    device->open (QIODevice::Text | QIODevice::ReadWrite);
    m_Text->setDevice (device);
    m_Text->setCodec ("UTF-8");

    // close the last connection:
    if (lastDevice) {
        lastDevice->close();
        delete lastDevice;
    }

    connect (device, SIGNAL (readyRead()),
             this, SLOT(onReadyRead()));
    if (device->canReadLine()) {
        onReadyRead ();
    }
}

void Stream::flush ()
{
    QMutexLocker (&this->m_Lock);
    m_Text->flush ();
}

void Stream::writeLine (const QString& st)
{
    QMutexLocker (&this->m_Lock);
    *m_Text << st << "\n";
}

