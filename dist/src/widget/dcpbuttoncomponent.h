#ifndef DCPBUTTONCOMPONENT_H
#define DCPBUTTONCOMPONENT_H

#include "dcpcomponent.h"
#include <QPixmap>

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
class DcpAppletMetadata;
class DcpButtonComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpButtonComponent(DcpCategory *category,
                       DcpAppletMetadata* metadata,
                       const QString& title="",
                       QGraphicsWidget *parent=0);
    ~DcpButtonComponent();

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
        DuiLabel *m_upLabel;
        DuiLabel *m_downLabel;

        // DuiButton* m_SmallButtonOn;
        // DuiButton* m_SmallButtonOff;

        // DuiButton* m_DisableButton;

        bool m_Enable;
        DcpAppletMetadata *m_Metadata; 


};


#endif // DCPBACKGROUNDCOMPONENT_H
