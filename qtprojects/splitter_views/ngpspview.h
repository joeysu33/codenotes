#if !defined(NGPSPVIEW_INCLUDED_H_)
#define NGPSPVIEW_INCLUDED_H_

#include <QWidget>
#include <QList>

class ISPView;
class QSplitter;
class NGPSPViewOrSplitter;

class NGPSPViewPrivate;
/*
 * SplitterView包封类，作为一个容器来放置content
 * ISPView的存储由本类负责释放，如果发生赋值操作则删除上一次的赋值
 */
class NGPSPView : public QWidget{
    Q_OBJECT
public:
    ~NGPSPView();

    ISPView* getContent() const ;
    QWidget* getContentAsWidget() const;
    NGPSPViewOrSplitter* getParentSplitterOrView() const;
private:
    void setContent(QWidget* content);
    void setContent(ISPView* content);
    void setParentSplitterOrView(NGPSPViewOrSplitter* sp);
private:
    explicit NGPSPView(NGPSPViewOrSplitter* sp, ISPView* content , QWidget* parent = Q_NULLPTR);
    explicit NGPSPView(NGPSPViewOrSplitter* sp, QWidget* content, QWidget* parent= Q_NULLPTR);
    void init(NGPSPViewOrSplitter* sp, ISPView* content);
    Q_DISABLE_COPY(NGPSPView)
private:
    friend class NGPSPViewOrSplitter;
    friend class NGPSPViewOrSplitterPrivate;
    NGPSPViewPrivate *m_d {Q_NULLPTR};
};

class NGPSPViewOrSplitterPrivate;
/*!
 * NGPSPView或QSplitter
 * 传入NGPSPViewOrSplitter的ISPView内存由NGPSPView释放
 */
class NGPSPViewOrSplitter : public QWidget {
    Q_OBJECT
public:
    enum SplitOrientation {
        SO_LEFT,
        SO_RIGHT,
        SO_TOP,
        SO_BOTTOM,
    };

    NGPSPViewOrSplitter(ISPView* view, QWidget *parent = Q_NULLPTR);
    NGPSPViewOrSplitter(QWidget* content, QWidget* parent=Q_NULLPTR);
    ~NGPSPViewOrSplitter();

    //split操作
    NGPSPView* add(QWidget* content , SplitOrientation orentation=SO_RIGHT);
    NGPSPView* addByDuplicate();
    //unsplit操作
    bool remove(QWidget* content);
    void removeByDuplicate();

    NGPSPViewOrSplitter* findParentViewOrSplitter() const;

    bool isSplitter() const;
    bool isView() const;

    NGPSPView* getView() const;
    QSplitter* getSplitter() const;
    NGPSPView* findViewForSPView(ISPView *view) const;
    NGPSPView* findViewForQWidget(QWidget* content) const;
    NGPSPView* findViewForSPViewRecursively(ISPView *view) const;
    NGPSPView* findViewForQWidgetRecursively(QWidget* content) const;

    ISPView* getContentAsView() const ;
    QList<ISPView*> getContentsAsSplitter() const;
    QList<ISPView*> getContentsAsSplitterRecursively() const;
private:
    NGPSPView* add(ISPView* view,SplitOrientation orentation=SO_RIGHT);
    bool remove(ISPView* view);
    bool remove(NGPSPView* sview);
    void init(ISPView *iv);
signals:
    void aboutToAdd(QWidget* content);
    void finishToAdd(NGPSPView* view);
    void aboutToRemove(NGPSPView* view);
    void finishToRemove(QWidget* content);
private:
    NGPSPViewOrSplitterPrivate *m_d {Q_NULLPTR};
    Q_DISABLE_COPY(NGPSPViewOrSplitter)
};

#endif //NGPSPVIEW_INCLUDED_H_

