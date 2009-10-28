#ifndef DCPBRIEFCOMPONENT_H
#define DCPBRIEFCOMPONENT_H

#include "dcpcomponent.h"
class DcpAppletMetadata;
class DcpBriefWidget;

class DcpBriefComponent: public DcpComponent {
    Q_OBJECT
public:
    DcpBriefComponent(DcpAppletMetadata* metadata, DcpCategory *category,
                      const QString& logicalId="");
    ~DcpBriefComponent();
    void setMetadata(DcpAppletMetadata* metadata);

    // Composite Pattern Interface, do nothing
    virtual void add(DcpComponent *) {}
    virtual void remove(DcpComponent *) {}
    virtual void createContents() {}

private:
	DcpBriefWidget* m_BriefWidget;
};

#endif // DCPBRIEFCOMPONENT_H
