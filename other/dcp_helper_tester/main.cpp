#include <QLocalSocket>
#include <QTextStream>
#include <QtDebug>

int main(int argc, const char** argv)
{
    QLocalSocket socket;
    socket.connectToServer ("dcpbriefs");
    socket.waitForConnected ();

    QTextStream input (stdin);
    QString line;
    do {
        line = input.readLine();
        socket.write ("watch Skeleton\n");
        socket.waitForBytesWritten ();

        socket.waitForReadyRead ();
        qDebug() << socket.readAll();
    } while (!line.isNull());
}

