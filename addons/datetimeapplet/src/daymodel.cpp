#include <DuiGrid>
#include <DuiWidgetFactory>
#include <DuiWidgetFactoryPlugins>

#include "daymodel.h"
#include "daybutton.h"

#include <QtDebug>
#include <DuiButton>
#include <DuiGridItem>
#include <QList>

int DayModel::rowCount(const QModelIndex &parent) const
{

    Q_UNUSED(parent);

    return m_MaxDay + m_FirstDay;
}

void DayModel::toggle(QString txt)
{
    QList<DuiButton*> buttonList = m_ButtonGroup->buttons();
    QListIterator<DuiButton*> iter(buttonList);
    while (iter.hasNext()) {
        DuiButton *item = iter.next();
        if (item->text() == txt) {
                item->setChecked(true);
                break;
        } 
    }
}

QVariant DayModel::data(const QModelIndex &index, int role) const
{

	if (role == Qt::DisplayRole && index.row()>0) {
		
		DayButton *tmp = new DayButton(QString::number(index.row()-m_FirstDay+1));
		tmp->setText(QString::number(index.row()-m_FirstDay+1));

		if(index.row()<=(m_FirstDay-1)){
			tmp->setText("");
			tmp->setState(DuiButtonModel::Released);
			tmp->setCheckable(true);
			tmp->setEnabled(false);
		}

		connect(tmp, SIGNAL(key(QString)), this, SLOT(keySlot(QString)));
		
//  		if (PINPANELBOOL[index.row()-1])
//			tmp->hide();

		tmp->setMinimumSize(85, 40);
		tmp->setMaximumSize(85, 40);

		if(m_Actual!=-1 && index.row()==(m_Actual+m_FirstDay)) {
			tmp->setState(DuiButtonModel::Pressed);
			tmp->setCheckable(true);
			tmp->setEnabled(false);
		}

		if(index.row()==1)
			tmp->setVisible(false);
/*
		tmp->setPreferredSize(80, 80);
		tmp->setMaximumSize(80, 80);

		tmp->setMaximumWidth(80);
*/

/*
		DuiGridItem* item = new DuiGridItem();
		item->setThumbnail("stretchbutton");
	    item->setTitle(QString::number(index.row()));
		//item->setSubtitle("Subtitle");

		qDebug() << "gridItem: " << item->preferredSize();

		item->model()->setText("111");
*/
		
		
		DuiWidgetPtr w;
	
		QVariant v;
		w = tmp;
//		w = item;
		v.setValue(w);
        m_ButtonGroup->addButton(tmp);

		return v;
	}

    return QVariant();
}

void DayModel::keySlot(QString text)
{
	keySignal(text);
}

