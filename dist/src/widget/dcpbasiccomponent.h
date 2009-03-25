#ifndef DCPBASICCOMPONENT_H
#define DCPBASICCOMPONENT_H

#include "dcpcomponent.h"
#include <QColor>

#include <QString>

class DuiLabel;
class DuiButton;
class DuiImage;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

static const QString  WIDGETNAME[] = {
    "DcpLabel",
    "DcpLabel2",
    "DcpLabelButton",
    "DcpLabel2Button",
    "DcpLabel2Image"
};

enum WIDGETTYPEID {
    DCPLABEL,           //"DcpLabel"
    DCPLABEL2,          //"DcpLabel2"
    DCPLABELBUTTON,     //"DcpLabelButton"
    DCPLABEL2BUTTON,    //"DcpLabel2Button"
    DCPLABEL2IMAGE,      //"DcpLabel2Image"
    WIDGETN
};

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
    virtual void switchToSubPage();
    void bigClicked();

protected:
    DuiLinearLayout* m_Layout;

    DuiGridLayout* m_GridLayout;

    DuiButton* m_BigButton;

    DuiButton* m_TriangleButton;

    DuiLabel* m_UpLabel;

    bool m_EnableButton;
    DcpAppletMetadata *m_Metadata; 

    int m_Z;

    int m_Type;

    static const int m_LabelWidth = 186;   //2
    static const int m_LabelWidth2 = 306;   //2
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

#endif // DCPBASICCOMPONENT_H
