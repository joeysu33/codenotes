#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QList>
#include <QString>
#include <QAbstractItemModel>

#define FIXCOLUMN (1)
#define CACHE (50)
#define VISUALCACHE (30)
#define MAXLEVEL (5)

class TreeNode {
public:
    TreeNode(const QString& text , TreeNode *parent = Q_NULLPTR) :
        m_text(text), m_parent(parent) {}
    ~TreeNode() {
        qDeleteAll(m_children);
    }
    void addChild(TreeNode *n) {
        if(n && m_children.indexOf(n) < 0) {
            m_children.append(n);
            n->m_parent = this;
        }
    }
    TreeNode* child(int row) {
        Q_ASSERT(row >= 0 && row < rowCount());
        if(row < 0 || row >= rowCount()) return Q_NULLPTR;
        return m_children[row];
    }

    QString childText(int row) const {
        if(row < 0 || row >= rowCount()) return QString();
        return m_children[row]->m_text;
    }

    void setChildText(int row, const QString& str) {
        if(row < 0 || row >= rowCount()) return ;
        m_children[row]->m_text = str;
    }

    int totalChildCount() const { return m_totalChild; }
    void setTotalChild(int n) { if(m_totalChild != n)  m_totalChild = n ; }
    TreeNode* parent() const { return m_parent; }

    int rowCount() const { return m_children.size(); }
    int columnCount() const { return FIXCOLUMN ;}
    int indexOf(TreeNode *n) const { return m_children.indexOf(n); }

    int level() const { return m_level; }
    void setLevel(int level) { m_level = level; }
    void setText(const QString& text) { m_text = text; }
    QString text() const { return m_text; }
private:
    QString m_text;
    int m_totalChild {1};
    QList<TreeNode*> m_children;
    TreeNode* m_parent {Q_NULLPTR};
    int m_level {0};
};

/*! Model/View to support huge data view */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject *parent  = Q_NULLPTR);
    ~TreeModel();
public:
    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const ;
    virtual QModelIndex parent(const QModelIndex &child) const ;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const ;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;

    void cacheMore(const QModelIndex & index);
    virtual void fetchMore(const QModelIndex &parent);
    virtual bool canFetchMore(const QModelIndex &parent) const;
    void testCacheMore(const QModelIndex& index);

    TreeNode* indexToItem(const QModelIndex & index) const ;
    const QModelIndex itemToIndex(TreeNode* n) const ;
signals:
    void loadMore(int);
private:
    TreeNode * m_root {Q_NULLPTR};
};

#endif // TREEMODEL_H
