/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "pagefactory.h"
#include "dcpsinglecomponent.h"
#include "pages.h"

#include "dcpdebug.h"


DcpSingleComponent::DcpSingleComponent (
        QGraphicsWidget     *parent,
        const QString       &logicalId,
        const QString       &title,
        const QString       &subTitle)
: MContentItem(subTitle.isEmpty() ? MContentItem::SingleTextLabel:
                                MContentItem::TwoTextLabels, parent)
{
    setTitle(title);
    setSubtitle(subTitle);

    connect(this, SIGNAL (clicked()),
            this, SLOT (activate()));

    m_MattiID = "DcpSingleComponent::" + logicalId;
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void
DcpSingleComponent::activate ()
{
    PageFactory *pageFactory = PageFactory::instance();
    pageFactory->changePage (subPage());
}

