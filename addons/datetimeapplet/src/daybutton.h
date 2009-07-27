#ifndef DAYBUTTON_H
#define DAYBUTTON_H

#include <DuiButton>

#include <QString>

class DayButton : public DuiButton {
	
	Q_OBJECT

	public:
		DayButton(QString text) : 
			m_Text(text)
		{
			connect(this, SIGNAL(pressed()), this, SLOT(clicked()));
            this->setObjectName("DayButton");
            this->setCheckable(true);
		}
	
	public Q_SLOTS:
		
		void clicked()
		{
			emit key(m_Text);
		}

	signals:
		void key(QString);
	
	protected:
		QString m_Text;

};

#endif // DAYBUTTON_H
