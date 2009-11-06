#ifndef DCPBUTTON2_H
#define DCPBUTTON2_H

#include <DuiButton>
#warning "DcpButton2 is DEPRECATED, and will be removed soon! Use DcpButton instead."

class DuiLabel;
class QGraphicsLayout;
class QGraphicsGridLayout;

// TODO if design stays the way it is we could use here an empty WidgetController
// which supports margins set by css
class DcpButton2: public DuiButton{
    Q_OBJECT
    Q_PROPERTY(QString text1 READ text1 WRITE setText1)
    Q_PROPERTY(QString text2 READ text2 WRITE setText2)
public:
	explicit DcpButton2(DuiWidget* parent = 0);

    void setText(const QString& text1, const QString& text2);
    virtual void setText1(const QString& text);
    virtual void setText2(const QString& text);
    virtual QString text1() const;
    virtual QString text2() const;

    // optimization, remove this if you want background:
    virtual void paintWindowFrame (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0);
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=0);

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

