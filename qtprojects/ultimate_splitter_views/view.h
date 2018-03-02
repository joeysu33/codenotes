#if !defined(_VIEW_INCLUDED_H)
#define _VIEW_INCLUDED_H

#include <QWidget>
class ViewOrSplitter;
class View : public QWidget {
    Q_OBJECT
public:
    View(ViewOrSplitter *vs, QWidget *parent = Q_NULLPTR) ;
private:
    ViewOrSplitter *m_vs {Q_NULLPTR};
};


#endif //_VIEW_INCLUDED_H
