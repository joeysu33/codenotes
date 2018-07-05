        #include "splay.h"
        #include <stdlib.h>
        #include "fatal.h"
        
        struct SplayNode
        {
            ElementType Element;
            SplayTree      Left;
            SplayTree      Right;
        };

        typedef struct SplayNode *Position;
        static Position NullNode = NULL;  /* Needs initialization */

        SplayTree
        Initialize( void )
        {
            if( NullNode == NULL )
            {
                NullNode = malloc( sizeof( struct SplayNode ) );
                if( NullNode == NULL )
                    FatalError( "Out of space!!!" );
                NullNode->Left = NullNode->Right = NullNode;
            }
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
            static struct SplayNode Header;
            Position LeftTreeMax, RightTreeMin;

            Header.Left = Header.Right = NullNode;
            LeftTreeMax = RightTreeMin = &Header;
            NullNode->Element = Item;

            while( Item != X->Element )
            {
                if( Item < X->Element )
                {
                    if( Item < X->Left->Element )
                        X = SingleRotateWithLeft( X );
                    /*!可以确定X节点及其右子树均大于Item(包含X节点)*/
                    if( X->Left == NullNode )
                        break;
                    /* Link right */
                    /*! 一直没有搞明白这部分代码的含义
                     * 原来是这样的,起初RightTreeMin和LeftTreeMax都指向
                     * Header，但是一旦RightTreeMin和LeftTreeMax被赋值以后
                     * 就不再指向Header了Header能始终记住最开始的第一个加入
                     * 到LeftTreeMax和RightTreeMin的节点，以后要做的事情就是
                     * 向LeftTreeMax的右侧增加根节点(没有右子树)，以及向RightTreeMin的左侧
                     * 增加根节点(没有左子树）
                     * /
                    RightTreeMin->Left = X;
                    RightTreeMin = X;
                    X = X->Left;
                }
                else
                {
                    if( Item > X->Right->Element )
                        X = SingleRotateWithRight( X );
                    if( X->Right == NullNode )
                        break;
                    /* Link left */
                    LeftTreeMax->Right = X;
                    LeftTreeMax = X;
                    X = X->Right;
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
                NewNode = malloc( sizeof( struct SplayNode ) );
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
