#ifndef LANGUAGELISTITEM_H
#define LANGUAGELISTITEM_H

#include <DuiWidget>

class DuiLabel;
class DuiButton;
class DuiLinearLayout;

class LanguageListItem : public DuiWidget
{
    Q_OBJECT

public:
    LanguageListItem(const QString &text, 
                     bool checked = false,
                     DuiWidget *parent = 0);
    ~LanguageListItem();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void checked(bool ok);
    bool isChecked();
    bool isClicked();
    QString text() const;

protected:
    void initWidget();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString 	    m_labelText;
    DuiLinearLayout *m_labelLayout;
    DuiLabel	    *m_normalLabel;
    DuiLabel        *m_highlightLabel;
    DuiButton       *m_checkMark;
    bool    	    m_checked;
    bool            m_clicked;
signals:
    void            clicked();
};
#endif // LANGUAGELISTITEM_H
