#ifndef DCPAPPLETMETADATA_FAKE_H__
#define DCPAPPLETMETADATA_FAKE_H__

#include <QString>
#include "dcpappletmetadata.h"

namespace DcpAppletMetadataFake {

// set this variable before calling DcpAppletMetadata functions
// depending on whether you want to test binary or dsl loading
enum AppletType {
    TYPE_BINARY,
    TYPE_DSL
};

static AppletType appletType = TYPE_BINARY;

} // namespace

// DcpAppletLoader::load() decides the applet type based on non-emptyness
// of the return value of fullBinary() and dslFilename()
QString DcpAppletMetadata::fullBinary() const
{
    if (DcpAppletMetadataFake::appletType == 
        DcpAppletMetadataFake::TYPE_BINARY) {
        return "dummy-binary";
    }
    return QString();
}

QString DcpAppletMetadata::dslFilename() const
{
    if (DcpAppletMetadataFake::appletType == 
        DcpAppletMetadataFake::TYPE_DSL) {
        return "dummy-dsl";
    }
    return QString();
}

#endif
