#if !defined(_TESTA_INCLUDED_H)
#define _TESTA_INCLUDED_H

namespace NSA{
    enum ENUA {
        /*! 枚举值1 */
        ENUA_1,
        
        /*! 枚举值2 */
        ENUA_2,
    };

    namespace NSB {
        /*!
         * \breif 本类是测试类TA
         */
        class TA {
        public:
            TA() {}

        };

        /*!
         * \breif 本类是测试类TB
         */
        class TB {
        public:
            TB() {}
        };
    }
} 

#endif //_TESTA_INCLUDED_H
