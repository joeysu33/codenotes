#include "treemodel.h"
#include <QDebug>

TreeModel::TreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    m_root = new TreeNode("Root");
    TreeNode *s1 = new TreeNode("s1");
    TreeNode *s2 = new TreeNode("s2");
    TreeNode *s3 = new TreeNode("s3");
    TreeNode *s4 = new TreeNode("s4");
    TreeNode *s5 = new TreeNode("s5");

    m_root->addChild(s1);
    s1->addChild(s2);
    s2->addChild(s3);
    s3->addChild(s4);
    s4->addChild(s5);

    //10^20
    m_root->setTotalChild(10000);
    s1->setTotalChild(10000);
    s2->setTotalChild(10000);
    s3->setTotalChild(10000);
    s4->setTotalChild(10000);

    s1->setLevel(1);
    s2->setLevel(2);
    s3->setLevel(3);
    s4->setLevel(4);
    s5->setLevel(5);
}

TreeModel::~TreeModel()
{
    delete m_root;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    //[case 2]
    if(!hasIndex(row, column, parent)) return QModelIndex();

    TreeNode * tn =  parent.isValid() ? indexToItem(parent) : m_root;
    Q_ASSERT(tn);
    //Check index validation
    //[case 1]
    if(tn->child(row))
        return createIndex(row, column, tn->child(row));
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid()) return QModelIndex();
    TreeNode *tn = indexToItem(child);
    Q_ASSERT(tn);
    if(tn->parent() == m_root) return QModelIndex();
    return itemToIndex(tn->parent());
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) return m_root->rowCount(); //parent <=> root
    TreeNode *tn = indexToItem(parent);
    Q_ASSERT(tn);
    return tn->rowCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return FIXCOLUMN;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole) return QVariant();
    if(!index.isValid()) return QVariant();

    TreeNode *tn = indexToItem(index);
    Q_ASSERT(tn);

    if(tn->text() == "s2" && rowCount(index.parent()) < 10) {
        const_cast<TreeModel*>(this)->testCacheMore(index);
    }
    return tn->text();
}

void TreeModel::cacheMore(const QModelIndex& index)
{
    if(canFetchMore(index)) fetchMore(index);
}

void TreeModel::fetchMore(const QModelIndex &parent)
{
    TreeNode *tn = (parent.isValid()) ? indexToItem(parent) : m_root;
    Q_ASSERT(tn);
    if(tn->level() >= MAXLEVEL) return ;

    int row = rowCount(parent);
    int cnt = qMin(CACHE, tn->totalChildCount() - row);

    beginInsertRows(parent, row,  row+cnt - 1);
    for(int i = row; i < row+cnt; ++i) {
        TreeNode *ii =new TreeNode(QString("cached:%1").arg(i+1));
        ii->setLevel(tn->level() + 1);
        tn->addChild(ii);

        //set total of child count
        if(ii->level() < MAXLEVEL) {
            TreeNode *jj = new TreeNode(QString("%1").arg(1+ii->level()));
            jj->setLevel(ii->level() + 1);
            ii->addChild(jj);
            ii->setTotalChild(10000);
        }
    }
    endInsertRows();

    emit loadMore(cnt);
}

bool TreeModel::canFetchMore(const QModelIndex &parent) const
{
    return false;
    TreeNode *tn;
    if(!parent.isValid()) {
        //fetch more for root node
        tn = m_root;
    }
    tn = indexToItem(parent);
    if(tn->level() == MAXLEVEL ) return false;

    Q_ASSERT(tn);
    if(tn->totalChildCount() > tn->rowCount()) {
        return true;
    }
    return false;
}

void TreeModel::testCacheMore(const QModelIndex &index)
{
    beginInsertRows(index.parent(), rowCount(index.parent()), rowCount(index.parent()) + 1000 -1);
        TreeNode *p = indexToItem(index.parent());
        for(int i=0; i<1000; ++i) {
            p->addChild(new TreeNode(QString("new-%1").arg(i+1), p));
        }
        endInsertRows();

}

TreeNode *TreeModel::indexToItem(const QModelIndex &index) const
{
    if(!index.isValid()) return m_root;
    return static_cast<TreeNode*>(index.internalPointer());
}

const QModelIndex TreeModel::itemToIndex(TreeNode *n) const
{
    if(n->parent()) {
        int row = n->parent()->indexOf(n);
        return createIndex(row, 0, n);
    }

    return QModelIndex();
}
