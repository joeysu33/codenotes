        #include "splay.h"
        #include <stdlib.h>
        #include <stdio.h>
        #include <assert.h>
        //#include "fatal.h"

        #define FatalError assert


        typedef struct _SplayNode *Position;
        static Position NullNode = NULL;  /* Needs initialization */

        SplayTree
        Initialize( void )
        {
            //没有看明白，还是直接使用NullNode == NULL
            /*
            if( NullNode == NULL )
            {
                NullNode = malloc( sizeof( struct _SplayNode ) );
                if( NullNode == NULL )
                    FatalError( "Out of space!!!" );
                NullNode->Left = NullNode->Right = NullNode;
            }
            */
            return NullNode;
        }

        static SplayTree Splay( ElementType Item, Position X );

        SplayTree
        MakeEmpty( SplayTree T )
        {
            if( T != NullNode )
            {
                MakeEmpty( T->Left );
                MakeEmpty( T->Right );
                free( T );
            }
            return NullNode;
        }

        void
        PrintTree( SplayTree T )
        {
            if( T != NullNode )
            {
                PrintTree( T->Left );
                printf( "%d ", T->Element );
                PrintTree( T->Right );
            }
        }

        SplayTree
        Find( ElementType X, SplayTree T )
        {
            return Splay( X, T );
        }

        SplayTree
        FindMin( SplayTree T )
        {
            return Splay( NegInfinity, T );
        }

        SplayTree
        FindMax( SplayTree T )
        {
            return Splay( Infinity, T );
        }

        /* This function can be called only if K2 has a left child */
        /* Perform a rotate between a node (K2) and its left child */
        /* Update heights, then return new root */

        static Position
        SingleRotateWithLeft( Position K2 )
        {
            Position K1;

            K1 = K2->Left;
            K2->Left = K1->Right;
            K1->Right = K2;

            return K1;  /* New root */
        }

        /* This function can be called only if K1 has a right child */
        /* Perform a rotate between a node (K1) and its right child */
        /* Update heights, then return new root */

        static Position
        SingleRotateWithRight( Position K1 )
        {
            Position K2;

            K2 = K1->Right;
            K1->Right = K2->Left;
            K2->Left = K1;

            return K2;  /* New root */
        }

/* START: fig12_6.txt */
        /* Top-down splay procedure, */
        /* not requiring Item to be in tree */

        SplayTree
        Splay( ElementType Item, Position X )
        {
            static struct _SplayNode Header;
            Position LeftTreeMax, RightTreeMin;

            Header.Left = Header.Right = NullNode;
            LeftTreeMax = RightTreeMin = &Header;
            show(1, X, "Splay");
//            NullNode->Element = Item;

            while( Item != X->Element )
            {
                if( Item < X->Element )
                {
                    //原代码这里缺失，存在bug,不是源代码有bug，源代码
                    //通过Null节点，来保证叶子节点的子节点一定不是NULL
                    if(X->Left == NullNode) break;
                    if( Item < X->Left->Element )
                        X = SingleRotateWithLeft( X );
                    /*!可以确定X节点及其右子树均大于Item(包含X节点)*/
                    if( X->Left == NullNode )
                        break;
                    /* Link right */
                    show(1, RightTreeMin, "A->RightTreeMin");
                    RightTreeMin->Left = X; //???? 设置Header.Left
                    RightTreeMin = X;
                    X = X->Left;
                    show(1, RightTreeMin, "B->RightTreeMin");
                }
                else
                {
                    //源代码这里缺失，存在bug，
                    //不是源代码有问题，源代码是通过NULL的叶子节点来保证
                    //叶子节点的子节点一定不是NULL
                    if(X->Right == NullNode) break;
                    if( Item > X->Right->Element )
                        X = SingleRotateWithRight( X );
                    if( X->Right == NullNode )
                        break;
                    /* Link left */
                    show(1, LeftTreeMax, "A->LeftTreeMax");
                    LeftTreeMax->Right = X; //????设置Header.Right
                    LeftTreeMax = X;
                    X = X->Right;
                    show(1, LeftTreeMax, "B->LeftTreeMax");
                }
            }  /* while Item != X->Element */

            /* Reassemble */
            LeftTreeMax->Right = X->Left;
            RightTreeMin->Left = X->Right;
            X->Left = Header.Right;
            X->Right = Header.Left;

            return X;
        }
/* END */




/* START: fig12_7.txt */
        SplayTree
        Insert( ElementType Item, SplayTree T )
        {
            static Position NewNode = NULL;

            if( NewNode == NULL )
            {
                NewNode = malloc( sizeof( struct _SplayNode ) );
                if( NewNode == NULL )
                    FatalError( "Out of space!!!" );
            }
            NewNode->Element = Item;

            if( T == NullNode )
            {
                NewNode->Left = NewNode->Right = NullNode;
                T = NewNode;
            }
            else
            {
                T = Splay( Item, T );
                if( Item < T->Element )
                {
                    NewNode->Left = T->Left;
                    NewNode->Right = T;
                    T->Left = NullNode;
                    T = NewNode;
                }
                else
                if( T->Element < Item )
                {
                    NewNode->Right = T->Right;
                    NewNode->Left = T;
                    T->Right = NullNode;
                    T = NewNode;
                }
                else
                    return T;  /* Already in the tree */
            }

            NewNode = NULL;   /* So next insert will call malloc */
            return T;
        }
/* END */


/* START: fig12_8.txt */
        SplayTree
        Remove( ElementType Item, SplayTree T )
        {
            Position NewTree;

            if( T != NullNode )
            {
                T = Splay( Item, T );
                if( Item == T->Element )
                {
                    /* Found it! */
                    if( T->Left == NullNode )
                        NewTree = T->Right;
                    else
                    {
                        NewTree = T->Left;
                        NewTree = Splay( Item, NewTree );
                        NewTree->Right = T->Right;
                    }
                    free( T );
                    T = NewTree;
                }
            }

            return T;
        }

/* END */

        ElementType
        Retrieve( SplayTree T )
        {
            return T->Element;
        }


        void
random_shuffle(int *d, int cnt) {
    int i, j, k, t;
    for(i=0; i <cnt * 4; ++i) {
        j=rand() % cnt;
        k= rand() % cnt;
        if(j == k) continue;

        t = d[j];
        d[j] = d[k];
        d[k] = t;
    }
}

void
showTree(const int mode, SplayTree t) {
    if(!t) return ;
    if(mode == 0)
        printf("%d ", t->Element);
    showTree(mode, t->Left);
    if(mode == 1)
        printf("%d ", t->Element);
    showTree(mode, t->Right);
    if(mode == 2)
        printf("%d ", t->Element);
}

void
destroyTree(SplayTree t) {
    if(!t) return ;
    destroyTree(t->Left);
    destroyTree(t->Right);
    free(t);
}

void
show(int mode, SplayTree t, const char *s) {
    printf("%s:", s);
    showTree(mode, t);
    printf("\n");
}

