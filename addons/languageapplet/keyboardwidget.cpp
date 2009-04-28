#include "keyboardwidget.h"
#include "dcpspaceritem.h"
#include "keyboardselectcontainer.h"
#include "languagelabelbuttoncontainer.h"
#include "dcplanguage.h"
#include "dcplanguageconf.h"
#include "languagetranslation.h"

#include <duitheme.h>
#include <duilabel.h>
#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <duipannableviewport.h>
#include <QGraphicsSceneMouseEvent>

KeyboardWidget::KeyboardWidget(QGraphicsWidget *parent)
              :DcpWidget(parent), m_background(NULL)
{
    setReferer(DcpLanguage::Main);
    initWidget();
}

KeyboardWidget::~KeyboardWidget()
{
    if (m_background)
    {
        DuiTheme::releasePixmap(m_background);
    }
}

void KeyboardWidget::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    // TODO generalize this with own view?
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor::fromRgb(0,0,0,128));
    painter->drawRect(rect());

    if (m_background)
    {
        qreal left, top;
        getContentsMargins(&left, &top, NULL, NULL);
        painter->drawPixmap(left, top, *m_background);
    }
}

void KeyboardWidget::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    Q_UNUSED(event);

    QSize size = this->size().toSize();
    static const int border = 30;
    if (m_background) {
        DuiTheme::releasePixmap(m_background);
    }
    qreal left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    size.setWidth(size.width()-left-right);
    size.setHeight(size.height()-top-bottom);
    m_background = DuiTheme::boxedPixmap("Mashup-container", size,
                                         border, border, border, border);
}

void KeyboardWidget::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    DuiWidget::mousePressEvent(event);
    event->accept();
}

void KeyboardWidget::initWidget()
{
    // Layout
    DuiLayout *m_mainLayout = new DuiLayout(this);
    m_mainLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(m_mainLayout, Qt::Vertical);
    m_mainLayout->setPolicy(mainLayoutPolicy);
    
    // contWidget
    DuiWidget *contWidget = new DuiWidget(this);
    m_contLayout = new DuiLayout(contWidget);
    m_contLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *contLayoutPolicy =
            new DuiLinearLayoutPolicy(m_contLayout, Qt::Vertical);
    m_contLayout->setPolicy(contLayoutPolicy);

    // titleLayout
    DuiLayout *titleLayout = new DuiLayout(NULL);
    titleLayout->setAnimator(NULL);
    DuiLinearLayoutPolicy *titleLayoutPolicy = 
            new DuiLinearLayoutPolicy(titleLayout, Qt::Horizontal);
    titleLayout->setPolicy(titleLayoutPolicy);
    
    // titleLabel
    DuiLabel *titleLabel = new DuiLabel(DcpLanguage::SelectKeyboardText, contWidget);
    titleLabel->setObjectName("DisplayLanguageTitleLabel");
    titleLabel->setAcceptedMouseButtons(0);
    
    // Add items to titleLayoutPolicy
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(contWidget, 5, 5,
                            QSizePolicy::Expanding, QSizePolicy::Fixed),
                    0, Qt::AlignLeft);
    titleLayoutPolicy->addItemAtPosition(titleLabel, 1, Qt::AlignCenter);
    titleLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(contWidget, 5, 5, 
                        QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignRight);

    // DonwloadedLanguage
    LanguageLabelButtonContainer *downloadedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::DOWNLOADED,
                                             contWidget);
    connect(downloadedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));

    // InstalledLanguage
    LanguageLabelButtonContainer *installedCont =
            new LanguageLabelButtonContainer(LanguageLabelButtonContainer::INSTALLED,
                                             contWidget);
    connect(installedCont, SIGNAL(removeMe(LanguageLabelButtonContainer*)),
            this, SLOT(removeContainer(LanguageLabelButtonContainer*)));

    // LanguageSelectContainer
    KeyboardSelectContainer *selectCont = 
            new KeyboardSelectContainer(DcpLanguage::InDeviceText,
                DcpLanguageConf::instance()->availableKeyboardLanguages(), contWidget);
    
    // Add items to contLayoutPolicy
    contLayoutPolicy->addItemAtPosition(titleLayout, 0, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(downloadedCont, 1, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(installedCont, 2, Qt::AlignCenter);
    contLayoutPolicy->addItemAtPosition(selectCont, 3, Qt::AlignCenter);
    contWidget->setLayout(m_contLayout);

    DuiPannableViewport* viewport = new DuiPannableViewport(this);
    viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    viewport->setWidget(contWidget);
    viewport->setObjectName("LanguageViewport");
    // TODO: remove me
    viewport->setMaximumHeight(DuiDeviceProfile::instance()->height() - 125);
    
    mainLayoutPolicy->addItemAtPosition(viewport, 1, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
                    new DcpSpacerItem(this, 10, 20, QSizePolicy::Expanding, QSizePolicy::Fixed),
                    2, Qt::AlignCenter);
    setContentsMargins(15,20,15,20);
}

void KeyboardWidget::removeContainer(LanguageLabelButtonContainer *cont)
{
    cont->hide();
    int index = m_contLayout->findIndexForItem(static_cast<QGraphicsItem*>(cont));
    if (index != -1)
        m_contLayout->removeAt(index);
}
