#ifndef DCP_RETRANSLATOR_H
#define DCP_RETRANSLATOR_H

#include <QObject>

/*! \brief copied from widgetsgallery, makes translation reload automatically
 *  \details DuiApplication's localeSettingsChanged signal should be connected
 *  on the retranslate slot, which loads the new translation.
 *
 * Widgets have to define their retranslateUi() virtual function properly, so
 * that changes (new translations) could be shown immediately. */
class DcpRetranslator : public QObject
{
    Q_OBJECT

public slots:
   void retranslate();
};

#endif // DCP_RETRANSLATOR_H

