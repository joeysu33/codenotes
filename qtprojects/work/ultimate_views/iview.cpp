#include "iview.h"

IView::IView(QObject *parent)
    :QObject(parent), m_duplicateSupported(false)
{}

bool IView::duplicateSupported() const
{
    return m_duplicateSupported;
}

void IView::setDuplicateSupported(bool duplicatesSupported)
{
    m_duplicateSupported = duplicatesSupported;
}

