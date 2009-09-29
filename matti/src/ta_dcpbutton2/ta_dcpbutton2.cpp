#include <mtestapp.h>
#include <DuiButton>
#include <QGraphicsLinearLayout>
#include "ta_dcpbutton2.h"

static QGQGraphicsLinearLayout *createLayout(DuiWidget *parent) {
    QGraphicsLinearLayout *lay = new QGraphicsLinearLayout(Qt::Horizontal, parent);
    parent->setLayout(lay);
    return lay;
}

void ta_dcpbutton2::toggleText1(bool checked) {
    m_subject->setText1(checked ? "First 1" : "Second 1");
}

void ta_dcpbutton2::toggleText2(bool checked) {
    m_subject->setText2(checked ? "First 2" : "Second 2");
}

void ta_dcpbutton2::clicked(bool checked) {
    Q_UNUSED(checked);
    ++m_clickCounter;
    m_clickCounterLabel->setText(QString::number(m_clickCounter));
}

DuiWidget *Ta_DcpButton2::addMainContent() {
    // TODO: Add the main content here
    DuiWidget *panel = new DuiWidget();
    QGraphicsLinearLayout *layout = createLayout(panel);

    m_subject = new DcpButton2();
    m_subject->setObjectName("DcpButton2-0");
    m_subject->setText("Text1", "Text2");

    m_clickCounterLabel = new DuiLabel("0");
    m_clickCounterLabel->setObjectName("ClickCounter");

    layout->addItem(m_subject);
    layout->addItem(m_clickCounterLabel);

    m_clickCounter = 0;

    connect(m_subject, SIGNAL(clicked(bool)), this, SLOT(clicked(bool)));
    return panel;
}

DuiWidget *Ta_DcpButton2::addToolbar() {
    DuiWidget *panel = new DuiWidget();
    QGraphicsLinearLayout *layout = createLayout(panel);

    DuiButton *change1 = createToolbarButton("Toggle Text 1");
    layout->addItem(change1);
    DuiButton *change2 = createToolbarButton("Toggle Text 2");
    layout->addItem(change2);

    connect(change1, SIGNAL(clicked(bool)), this, SLOT(toggleText1(bool)));
    connect(change2, SIGNAL(clicked(bool)), this, SLOT(toggleText2(bool)));

    return panel;
}



MTESTAPP_MAIN(Ta_DcpButton2);
