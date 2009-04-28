#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <DuiWidget>

class DuiLabel;
class DuiButton;
class DuiGridLayoutPolicy;

class LanguageListItem : public DuiWidget
{
    Q_OBJECT

public:
    LanguageListItem(const QString &langCode,
                     const QString &text, 
                     DuiWidget *parent = 0);
    virtual ~LanguageListItem();

    //! reimp
    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    //! reimp_end

    void checked(bool ok);
    bool isChecked();
    bool isClicked();
    QString text() const;
    QString langCode() const;

protected:
    void initWidget();
    //! reimp
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //! reimp_end

protected slots:
    void onOrientationAngleChanged();

private:
    QString m_LangCode;
    QString m_LabelText;
    DuiGridLayoutPolicy *m_LabelLayoutPolicy;
    DuiLabel *m_NormalLabel;
    DuiButton *m_CheckMark;
    bool m_Checked;
    bool m_Clicked;
    bool m_First;
    
signals:
    void clicked(LanguageListItem *item);
};
#endif // LANGUAGELISTITEM_H
