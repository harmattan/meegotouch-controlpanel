#ifndef DCPBASIC_H
#define DCPBASIC_H

#include "dcpcomponent.h"
#include <QPixmap>
#include <QColor>

class DuiLabel;
class DuiButton;
class DuiImage;
class DuiLinearLayout;
class DuiGridLayout;
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

    virtual void setEnable(bool /*enable*/) {}

    void setMetadata(DcpAppletMetadata* metadata);
    DcpAppletMetadata* metadata() const;

    void setTitleAlignment(Qt::Alignment align);

    // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}

//    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    virtual void createContents();


    void initLayout();

    void initRow(int height);
    void initRow2(int height);

    void initColumn(int s1, int s2, int s3);
    void initColumn(int s1, int s2, int s3, int s4, int s5);
    
    DuiButton* newButton(int size, const QString &name);

    DuiButton* newButton(int width, int height, const QString &name);

    DuiLabel* newLabel(int height, const QString &text, const QString &objectName, Qt::Alignment alignment);

    DuiImage* newImage(const QString &name, int size, int borderSize, const QColor &color = QColor(128, 128, 128));

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);
    virtual void switchToSubPage();
    void bigClicked();
protected:
    void addItem ( QGraphicsLayoutItem * item );

protected:
    DuiLinearLayout* m_Layout;

    DuiGridLayout* m_GridLayout;

    DuiButton* m_BigButton;

    DuiButton* m_TriangleButton;

    DuiLabel* m_UpLabel;

    bool m_Enable;
    DcpAppletMetadata *m_Metadata; 

    int m_Z;

};

inline void DcpBasicComponent::setMetadata(DcpAppletMetadata* metadata)
{
  m_Metadata = metadata;
}

inline DcpAppletMetadata* DcpBasicComponent::metadata() const {
  return m_Metadata;
}

#endif // DCPBACKGROUNDCOMPONENT_H
