#ifndef DCPDEBUG_H
#define DCPDEBUG_H

#include <QtDebug>

namespace DcpDebug {
    void time(const QString& msg = "");
    void start(const QString& msg = "");
    void end(const QString& msg = "");
    void dcpMsg(QtMsgType type, const char *msg);
};

#if 0
inline void DcpDebug::time(const QString& msg = "") {}
inline void DcpDebug::start(const QString& msg = "") {}
inline void DcpDebug::end(const QString& msg = "") {}

#else

#define DCP_FUNC_START DcpDebug::start(Q_FUNC_INFO);
#define DCP_FUNC_END DcpDebug::end(Q_FUNC_INFO);

#endif

#endif // DCPDEBUG_H
