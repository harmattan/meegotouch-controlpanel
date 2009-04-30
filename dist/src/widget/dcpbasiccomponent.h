#ifndef DCPBASICCOMPONENT_H
#define DCPBASICCOMPONENT_H

#include "dcpcomponent.h"
#include <QColor>
#include <duigridlayoutpolicy.h>

#include <QString>
#include "dcpwidgettypes.h"

#include "dcpbutton.h"

class DuiLabel;
class DuiButton;
class DuiImage;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;
class DuiLayout;

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

    int getType();

	void setLine(bool line);

protected:
    void initLayout();

    void initRow(int height);
    void initRow2(int height);

    void initColumn(int s1, int s2, int s3);
    void initColumn(int s1, int s2, int s3, int s4, int s5);
    
    DuiButton* newButton(int size, const QString &name);

    DuiButton* newButton(int width, int height, const QString &name);

    DuiLabel* newLabel(int height, const QString &text, const QString &objectName, Qt::Alignment alignment);

    DuiImage* newImage(const QString &name, int size, int borderSize, const QColor &color = Qt::gray);


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


    //DuiGridLayout* m_GridLayout;

    DuiButton* m_BigButton;

    DuiButton* m_TriangleButton;

    DuiLabel* m_UpLabel;

    bool m_EnableButton;
    DcpAppletMetadata *m_Metadata; 

    int m_Z;

    int m_Type;

    bool m_EnableToggle;

	bool m_LineBool;

    static const int m_LabelWidth = 186;   //2
    static const int m_LabelWidth2 = 306;   //2

    static const int m_TriangleSize = 16;

    static const int m_Width = 392;

    static const int m_Height = 88;

protected:
		DcpButton *m_Button;

};

inline void DcpBasicComponent::setMetadata(DcpAppletMetadata* metadata)
{
    m_Metadata = metadata;
}

inline DcpAppletMetadata* DcpBasicComponent::metadata() const
{
    return m_Metadata;
}

inline int DcpBasicComponent::getType()
{
    return m_Type;
}

inline void DcpBasicComponent::setLine(bool line)
{
	m_LineBool = line;
	m_Button->setLine(line);
}

#endif // DCPBASICCOMPONENT_H
