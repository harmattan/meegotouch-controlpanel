#ifndef SECURITY_H
#define SECURITY_H

class DcpAppletMetadata;
class QString;

namespace Security {
    void loadAppletRestricted (const QString& appletName);
    void restrictTo (DcpAppletMetadata* metadata);
};

#endif // SECURITY_H
