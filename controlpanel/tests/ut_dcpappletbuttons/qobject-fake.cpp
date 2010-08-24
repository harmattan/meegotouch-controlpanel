#include <QObject>

// this disables the timer event to run automatically
int QObject::startTimer ( int ) { return 1; }

