#ifndef _MTESTPAGEFACTORY_H

#include <QObject>
#include <DuiWidget>
#include <DuiButton>

class MTestPageFactory : public QObject {
	Q_OBJECT

	public:

        DuiButton *createToolbarButton(QString text, bool checkable = true );

        virtual DuiWidget *addMainContent();
        virtual DuiWidget *addToolbar();
};


#endif
