#ifndef DCPBUTTON2_H
#define DCPBUTTON2_H

#include <DuiButton>
class DuiLabel;
class QGraphicsLayout;
class QGraphicsGridLayout;

class DcpButton2: public DuiButton{
    Q_OBJECT
public:
	explicit DcpButton2(DuiWidget* parent = 0);

    void setText(const QString& text1, const QString& text2);
    virtual void setText1(const QString& text);
    virtual void setText2(const QString& text);

protected:
    DcpButton2(DuiWidget* parent, bool);
    virtual QGraphicsLayout* createLayout();
    QGraphicsGridLayout* textLayout();

private:
    void updateLabelSizes();
    QGraphicsGridLayout* m_TextLayout;
    DuiLabel* m_Label1;
    DuiLabel* m_Label2;
    DuiWidget* m_Triangle;
};

#endif // DCPBUTTON2_H

