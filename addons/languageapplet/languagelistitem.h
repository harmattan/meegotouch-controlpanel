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
    LanguageListItem(const QString &text, 
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
    QString 	            m_labelText;
    DuiGridLayoutPolicy     *m_labelLayoutPolicy;
    DuiLabel	            *m_normalLabel;
    DuiButton               *m_checkMark;
    bool    	            m_checked;
    bool                    m_clicked;
    bool                    m_first;

signals:
    void            clicked();
};
#endif // LANGUAGELISTITEM_H
