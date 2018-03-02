#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QtGlobal>
#include <QIcon>
#include <QString>
#include <QMap>

enum StandardIcon {
    //editortoolbar
    SI_PREV,
    SI_NEXT,
    SI_SPLIT_HORIZONTAL,
    SI_SPLIT_VERTICAL,
    SI_CLOSE,
    SI_CLOSE_SPLIT_BOTTOM,
};

class IconProvider
{
public:
    static IconProvider* instance();
    QIcon getIcon(StandardIcon icon);
    QIcon getIcon(const QString& name);
private:
    void init();
    bool isInitialized() ;
private:
    IconProvider();
    Q_DISABLE_COPY(IconProvider)
    QMap<StandardIcon, QIcon> m_stdIcon;
};

#endif // ICONPROVIDER_H

