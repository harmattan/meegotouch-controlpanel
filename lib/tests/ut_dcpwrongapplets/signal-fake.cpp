#include "signal-fake.h"
#include <signal.h>

QSet<int> connectedSignals;

sighandler_t signal(int signum, sighandler_t t)
{
    connectedSignals.insert (signum);
    return t;
}

