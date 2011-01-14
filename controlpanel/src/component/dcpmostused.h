#ifndef DCPMOSTUSED_H
#define DCPMOSTUSED_H

#include <MContainer>

class DcpMostUsed: public MContainer
{
    Q_OBJECT

public:
    DcpMostUsed (QGraphicsWidget* parent);
    bool itemsAvailable() { return m_ItemsAvailable; }

public slots:
    void refresh ();

protected slots:
    void retranslateUi ();

signals:
    void itemsBecameAvailable ();

private:
    void checkItemsAvailable ();
    bool m_ItemsAvailable;
    class DcpAppletButtons* m_AppletButtons;
};


#endif // DCPMOSTUSED_H

