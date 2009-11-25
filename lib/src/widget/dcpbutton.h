#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiStylableWidget>
class DuiLabel;
class QGraphicsLayout;
class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;

// TODO if design stays the way it is we could use here an empty WidgetController
// which supports margins set by css
class DcpButton: public DuiStylableWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text1 READ text1 WRITE setText1)
    Q_PROPERTY(QString text2 READ text2 WRITE setText2)
public:
	explicit DcpButton(DuiWidget* parent = 0);

    void setText(const QString& text1, const QString& text2);
    virtual void setText1(const QString& text);
    virtual void setText2(const QString& text);
    virtual QString text1() const;
    virtual QString text2() const;

signals:
    void clicked();

protected:
    DcpButton(DuiWidget* parent, bool);
    virtual QGraphicsLayout* createLayout();
    QGraphicsGridLayout* textLayout();
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

private:
    void updateLabelSizes();
    QGraphicsGridLayout* m_TextLayout;
    DuiLabel* m_Label1;
    DuiLabel* m_Label2;
};

#endif // DCPBUTTON_H

