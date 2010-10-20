#include "reader.h"

#include <QTextStream>
#include <QIODevice>


Reader::Reader(QObject* parent):
    QThread (parent),
    m_Input (new QTextStream (stdin, QIODevice::ReadOnly))
{
    m_Input->setCodec ("UTF-8");
}

void Reader::run()
{
    connect (m_Input->device(), SIGNAL (readyRead()),
             this, SLOT(onReadyRead()));
    exec ();
}

void Reader::onReadyRead ()
{
    QString st;
    do {
        st = m_Input->readLine ();
        if (!st.isEmpty()) {
            emit newCommand (st);
        } else {
            if (st.isNull()) {
                // end of data
                return;
            }
        }
    } while (!m_Input->atEnd());
}

void Reader::setIODevice (QIODevice* device)
{
    m_Input->setDevice (device);
    m_Input->setCodec ("UTF-8");
}

