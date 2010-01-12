#ifndef DCP_RETRANSLATOR_H
#define DCP_RETRANSLATOR_H

#include <QObject>
class DuiLocale;

/*! \brief makes translation reload automatically
 *  \details DuiApplication's localeSettingsChanged signal should be connected
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
    DcpRetranslator();

protected:
    static void installAppletTranslations(DuiLocale& locale);

public slots:
   void retranslate();
};

#endif // DCP_RETRANSLATOR_H

