#include <QLocalSocket>
#include <QtDebug>

int main(int argc, const char** argv)
{
    QLocalSocket socket;
    socket.connectToServer ("dcpbriefs");
    socket.waitForConnected ();
    socket.write ("watch Skeleton\n");
    socket.waitForBytesWritten ();
    while (true) {
        socket.waitForReadyRead ();
        qDebug() << socket.readAll();
    }
}

