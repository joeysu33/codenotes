#include "iconprovider.h"

IconProvider *IconProvider::instance()
{
    static IconProvider provider;
    if(!provider.isInitialized()) {
        provider.init();
    }
    return &provider;
}

QIcon IconProvider::getIcon(StandardIcon icon)
{
    if(m_stdIcon.contains(icon))  return m_stdIcon[icon];
    return QIcon();
}

QIcon IconProvider::getIcon(const QString &name)
{
    //TODO
    Q_UNUSED(name)
    return QIcon();
}

void IconProvider::init()
{
    m_stdIcon[SI_PREV] = QIcon(":/utils/images/prev.png");
    m_stdIcon[SI_NEXT] = QIcon(":/utils/images/next.png");
    m_stdIcon[SI_SPLIT_HORIZONTAL] = QIcon(":/utils/images/splitbutton_horizontal.png");
    m_stdIcon[SI_SPLIT_VERTICAL] = QIcon(":/utils/images/prev.png");
    m_stdIcon[SI_CLOSE] = QIcon(":/utils/images/close.png");
    m_stdIcon[SI_CLOSE_SPLIT_BOTTOM] = QIcon(":/utils/images/splitbutton_closebottom.png");
    m_stdIcon[SI_CLOSE_SPLIT_TOP] = QIcon(":/utils/images/splitbutton_closetop.png");
    m_stdIcon[SI_CLOSE_SPLIT_LEFT] = QIcon(":/utils/images/splitbutton_closeleft.png");
    m_stdIcon[SI_CLOSE_SPLIT_RIGHT] = QIcon(":/utils/images/splitbutton_closeright.png");
}

bool IconProvider::isInitialized()
{
    return !(m_stdIcon.size() < 1);
}

IconProvider::IconProvider()
{

}
