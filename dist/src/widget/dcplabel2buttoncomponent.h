#ifndef DCPLABEL2BUTTON_H
#define DCPLABEL2BUTTON_H

#include "dcpcomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;

class DcpLabel2ButtonComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpLabel2ButtonComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpLabel2ButtonComponent();

    //DcpButton(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable = true);

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
    virtual void switchToSubPage();
    void bigClicked();
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

        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;
        DuiButton* m_DisableButton;

        DuiLabel* m_UpLabel;
        DuiLabel* m_DownLabel;

        bool m_Enable;
        DcpAppletMetadata *m_Metadata; 


};


#endif // DCPBACKGROUNDCOMPONENT_H
