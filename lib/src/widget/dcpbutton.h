/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiStylableWidget>

class DuiLabel;
class QGraphicsLayout;
class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;
class DcpButtonPrivate;

/*!
 * Base class of the widgets used as 'brief widgets' lines that represent
 * applets in the main view and category pages of the control panel.
 *
 * TODO if design stays the way it is we could use here an empty
 * WidgetController which supports margins set by css
 */
class DcpButton: public DuiStylableWidget
{
    Q_OBJECT
    Q_PROPERTY (QString text1 READ getText1 WRITE setText1)
    Q_PROPERTY (QString text2 READ getText2 WRITE setText2)

public:
	explicit DcpButton (DuiWidget* parent = 0);
    ~DcpButton ();

    void setText (const QString& text1, const QString& text2);
    virtual void setText1 (const QString& text);
    virtual void setText2 (const QString& text);
    virtual QString getText1 () const;
    virtual QString getText2 () const;

signals:
    void clicked();

protected:
    DcpButton (DuiWidget* parent, bool);
    virtual QGraphicsLayout *createLayout();
    QGraphicsGridLayout *textLayout ();
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

private:
    void updateLabelSizes();
    DcpButtonPrivate * const d_ptr;
};

#endif

