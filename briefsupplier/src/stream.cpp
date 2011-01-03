#include "stream.h"

#include <QTextStream>
#include <QLocalSocket>


Stream::Stream(QObject* parent):
    QObject (parent),
    m_Text (new QTextStream ())
{
}

Stream::~Stream ()
{
    delete m_Text;
}

void Stream::onReadyRead ()
{
    QString st;
    do {
        {
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
    m_Text->flush ();
    QLocalSocket* socket = qobject_cast<QLocalSocket*>(m_Text->device());
    if (socket) socket->flush ();
}

void Stream::writeLine (const QString& st)
{
    *m_Text << st << "\n";
}

