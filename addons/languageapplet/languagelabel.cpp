#include "languagelabel.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>

const int height = 88;

LanguageLabel::LanguageLabel(const QString &upText,
                            const QString &downText,
                            DuiWidget *parent)
              :DuiWidget(parent),
               m_upText(upText),
               m_downText(downText)
{
    initWidget();
}

LanguageLabel::LanguageLabel(const QString &text,
                             DuiWidget *parent)
              :DuiWidget(parent),
               m_upText(text),
               m_downText(QString(""))
{
    initWidget();
}

LanguageLabel::~LanguageLabel()
{
}

void LanguageLabel::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *parent)
{
    Q_UNUSED(option);
    Q_UNUSED(parent);

    int borderWidth = 2;
    QColor lineColor = QColor(80, 80, 80, 244);
    QPen pen = painter->pen();
    pen.setWidth(1);
    pen.setColor(lineColor);
    painter->setPen(pen);
                            
    qreal y = size().height();
    painter->drawLine(borderWidth, y,
                      geometry().size().width() - 2 * borderWidth, y);
}

void LanguageLabel::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayoutPolicy->setContentsMargins(20.0, 1.0, 12.0, 1.0);
    mainLayoutPolicy->setSpacing(2);
    this->setAcceptedMouseButtons(0);

    if (m_downText.isEmpty()) 
    {
        // single label
        DuiLabel *label = new DuiLabel(m_upText, this);
        label->setObjectName("LanguageLeftLabel");
        label->setAcceptedMouseButtons(0);
        mainLayoutPolicy->addItemAtPosition(
                     new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                     0, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(label, 1, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(
                     new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                     2, Qt::AlignCenter);   
    } else {
        // upLabel
        DuiLabel *upLabel = new DuiLabel(m_upText, this);
        upLabel->setObjectName("LanguageUpLabel");
        upLabel->setAcceptedMouseButtons(0);

        // downLabel
        DuiLabel *downLabel = new DuiLabel(m_downText, this);
        downLabel->setObjectName("LanguageDownLabel");
        downLabel->setAcceptedMouseButtons(0);

        mainLayoutPolicy->addItemAtPosition(
                        new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                        0, Qt::AlignCenter);
        mainLayoutPolicy->addItemAtPosition(upLabel, 1, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(downLabel, 2, Qt::AlignLeft | Qt::AlignVCenter);
        mainLayoutPolicy->addItemAtPosition(
                        new DcpSpacerItem(this, 10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding),
                        3, Qt::AlignCenter);
    }

    this->setLayout(mainLayout);

    // fixed sizes
    setMinimumHeight(height);
    setMaximumHeight(height);

    connect(DuiDeviceProfile::instance(), SIGNAL(orientationAngleChanged (DuiDeviceProfile::DeviceOrientationAngle)),
            this, SLOT(onOrientationAngleChanged ()));
    onOrientationAngleChanged();
}


void LanguageLabel::onOrientationAngleChanged()
{
    setMinimumWidth(DuiDeviceProfile::instance()->width() / 2 - 20);
    setMaximumWidth(DuiDeviceProfile::instance()->width() / 2 - 20);
}

