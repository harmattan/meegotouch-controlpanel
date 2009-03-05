#ifndef DCPBUTTONCOMPONENT_H
#define DCPBUTTONCOMPONENT_H

#include "dcpcomponent.h"

class DuiLabel;
class DuiButton;
class DuiLinearLayout;
class DuiGridLayout;
#include <QPixmap>

class DcpButtonComponent: public DcpComponent
{
    Q_OBJECT
public:
    DcpButtonComponent(DcpCategory *category,
                            const QString& title="",
                            QGraphicsWidget *parent=0);
    ~DcpButtonComponent();

    //DcpButton(QString bigLabel, int bigWidth, int bigHeight, QString smallLabel, int smallX, int smallY, int smallWidth, int smallHeight, bool enable = true);

    void setEnable(bool enable);

    //DuiGridLayout* layout();

    virtual void setTitle(const QString& title);
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

        DuiButton* m_SmallButtonOn;
        DuiButton* m_SmallButtonOff;

        DuiButton* m_DisableButton;

        bool m_Enable;


};


#endif // DCPBACKGROUNDCOMPONENT_H
