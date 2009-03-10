#ifndef DCPIMAGECOMPONENT_H
#define DCPIMAGECOMPONENT_H

#include "dcpcomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiImage;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpImageComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpImageComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpImageComponent();


    void setEnable(bool enable);
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

        DuiButton* m_Button;

        DuiLabel* m_Label;
        DuiImage* m_Image;


        DcpAppletMetadata *m_Metadata; 


};


#endif // DCPBACKGROUNDCOMPONENT_H
