#ifndef DCPAPPLETOBJECT_P_H
#define DCPAPPLETOBJECT_P_H

class DcpBrief;
class DcpAppletIf;

class DcpAppletObjectPrivate
{
public:
    DcpAppletObjectPrivate();
    ~DcpAppletObjectPrivate();
    DcpAppletIf *applet;
    DcpBrief* m_Brief;
    DcpAppletMetadata *m_Metadata;
};
#endif // DCPAPPLETOBJECT_P_H

