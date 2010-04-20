/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCP_RETRANSLATOR_H
#define DCP_RETRANSLATOR_H

#include <QObject>
class MLocale;
class DcpAppletMetadata;
#include <QList>

typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;

/*! \brief makes translation reload automatically
 *  \details MApplication's localeSettingsChanged signal should be connected
 *  on the retranslate slot, which loads the new translation.
 *  Also handles loading applet translations, they just should have the filename
 *  "duicontrolpanel-<appletname>.qm"
 *
 * Widgets have to define their retranslateUi() virtual function properly, so
 * that changes (new translations) could be shown immediately. */
class DcpRetranslator : public QObject
{
    Q_OBJECT
public:
    static DcpRetranslator* instance();
    DcpRetranslator(); // FIXME, this is deprecated, only for compatibility, suw uses it

    void ensureTranslationsAreLoaded(const DcpAppletMetadataList& list);
    void ensureTranslationLoaded(DcpAppletMetadata* metadata);
    void unloadTranslation(DcpAppletMetadata* metadata);

public slots:
   void retranslate();

protected:
    void loadAppletTranslation (
            MLocale               &locale,
            const DcpAppletMetadata *metadata);
    class DcpRetranslatorPriv* priv;
};

#endif

