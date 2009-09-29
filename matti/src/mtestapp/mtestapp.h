#ifndef __MTESTAPP_H
#define __MTESTAPP_H

#include <QObject>
#include <QDebug>
#include <DuiApplicationWindow>
#include <DuiApplicationPage>
#include <DuiApplication>
#include <duigridlayoutpolicy.h>


class MTestPageFactory;

class MTestApp : public DuiApplicationPage
{
    Q_OBJECT

    public:
      MTestApp(MTestPageFactory *factory, Qt::Orientations direction = Qt::Vertical);
      ~MTestApp();
      virtual void createContent();

      static void debug(QString row);


    private:
      DuiGridLayoutPolicy *createLayout(DuiWidget *panel);
      DuiGridLayoutPolicy *_layout;
      MTestPageFactory *_f;
      Qt::Orientations _direction;

};

#define TESTDEBUG(Param) MTestApp::debug(Param);


#define MTESTAPP_MAIN(ClassName) \
int main(int argc, char *argv[]) { \
                                   DuiApplication app(argc,argv); \
                                   DuiApplication::setAnimator(NULL);  \
                                   DuiApplicationWindow window; \
                                   window.show(); \
                                   ClassName pagefactory; \
                                   MTestApp testApp(&pagefactory); \
                                   testApp.appear(); \
                                   return app.exec(); \
                               } \




#endif
