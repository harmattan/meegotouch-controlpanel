#ifndef DCPBASICCOMPONENT_H
#define DCPBASICCOMPONENT_H

#include "dcpcomponent.h"
#include <QColor>
#include <duigridlayoutpolicy.h>

#include <QString>
#include "dcpwidgettypes.h"

#include "dcpbutton.h"

class DcpAppletMetadata;

class DcpBasicComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpBasicComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpBasicComponent();

    virtual void setEnableButton(bool /*enable*/) {}

    void setMetadata(DcpAppletMetadata* metadata);
    DcpAppletMetadata* metadata() const;

    void setTitleAlignment(Qt::Alignment align);

    // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}

//    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    virtual void createContents();

	void setLine(bool line);

protected:
    void initLayout();

    void addItem ( QGraphicsLayoutItem * item );

public slots:
    void bigClicked();

protected:
    //DuiLayout* m_Layout;
    class DuiLinearLayoutPolicy* m_Layout;

    class DuiLayout *m_MainLayout;

    DuiLinearLayoutPolicy *m_MainLayoutPolicy;

    class DuiLayout *m_WidgetLayout;
    class DuiGridLayoutPolicy *m_WidgetLayoutPolicy;


    DcpAppletMetadata *m_Metadata; 

	bool m_LineBool;

	DcpButton *m_Button;

    Qt::Alignment m_Alignment;

protected slots:
    void onMetadataChanged();

};

inline DcpAppletMetadata* DcpBasicComponent::metadata() const
{
    return m_Metadata;
}

inline void DcpBasicComponent::setLine(bool line)
{
	m_LineBool = line;
	m_Button->setLine(line);
}

#endif // DCPBASICCOMPONENT_H
