#ifndef DCPLABELCOMPONENT_H
#define DCPLABELCOMPONENT_H

#include "dcpcomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabelComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpLabelComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabelComponent();

    //DcpButton(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable = true);gi 

    void setMetadata(DcpAppletMetadata* metadata) {m_Metadata = metadata;};
    DcpAppletMetadata* metadata() const {return m_Metadata;};
    //DuiGridLayout* layout();

    void setTitleAlignment(Qt::Alignment align);

        // Composite Pattern Interface
    virtual void add(DcpComponent *){}
    virtual void remove(DcpComponent *){}

//    virtual void paint (QPainter * painter,
//                        const QStyleOptionGraphicsItem * option,
//                        QWidget * widget = 0 );

    virtual void createContents();

public slots:
    virtual void onOrientationChange (const Dui::Orientation &orientation);

protected:
    void addItem ( QGraphicsLayoutItem * item );

private:
    DuiLinearLayout* m_Layout;

  /*  private slots:
        void bigClicked();
        void smallClickedOn();
        void smallClickedOff();
        void disableClicked();

    signals:
        void clicked(QString);
*/
    protected:
        DuiGridLayout* m_GridLayout;

        DuiButton* m_BigButton;

        DuiButton* m_TriangleButton;

        DuiLabel* m_Label;

        DcpAppletMetadata *m_Metadata; 
};


#endif // DCPBACKGROUNDCOMPONENT_H
