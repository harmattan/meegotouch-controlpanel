/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBUTTON_H
#define DCPBUTTON_H

#include <DuiWidget>

class DuiLabel;
class QGraphicsLayout;
class QGraphicsGridLayout;
class QGraphicsSceneMouseEvent;
class DcpButtonPrivate;

/*
 * This DcpButton class is originally based on the DuiStylableWidget class, but
 * the actual style was not implemented. When I implemented the elements needed
 * for the actual style it turned out that the libdui is crashing. I believe the
 * bug is in the libdui, I found no actual example of a class based on the
 * DuiStylableWidget. I did not want to delete the style stuff, so started to
 * use the USE_STYLABLE_WIDGET. Please define this macro to check if the 
 * DuiStylableWidget is working. until such a time we can use the DuiWidget
 * instead.
 */
#ifdef USE_STYLABLE_WIDGET
#include <DuiStylableWidget>
class DUI_EXPORT DcpButtonStyle : public DuiWidgetStyle
{
    Q_OBJECT
    DUI_STYLE(DcpButtonStyle)

    DUI_STYLE_ATTRIBUTE(bool,    drawTiledHorizontal, DrawTiledHorizontal)
};

class DUI_EXPORT DcpButtonStyleContainer : public DuiWidgetStyleContainer
{
    DUI_STYLE_CONTAINER(DcpButtonStyle)
};
#endif

/*!
 * \brief Widget used as part of the brief widget.
 *
 * The #DcpButton is a widget the DuiControlpanel uses as part of the brief
 * widgets representing one applet variant in the main page and the category
 * pages of the control panel UI.
 * TODO if design stays the way it is we could use here an empty
 * WidgetController which supports margins set by css
 */
#ifdef USE_STYLABLE_WIDGET
class DcpButton: public DuiStylableWidget
#else
class DcpButton: public DuiWidget
#endif
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
    DcpButton (DuiWidget *parent, bool);
    virtual QGraphicsLayout *createLayout();
    QGraphicsGridLayout *textLayout ();
    virtual void mousePressEvent (QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

private:
    void updateLabelSizes();
    DcpButtonPrivate * const d_ptr;
    #ifdef USE_STYLABLE_WIDGET
    DUI_STYLABLE_WIDGET (DcpButtonStyle)
    #endif
};



#endif

