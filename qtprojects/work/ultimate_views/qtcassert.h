#if !defined(QTC_ASSERT_INCLUDED_H)
#define QTC_ASSERT_INCLUDED_H

//#include "utils_global.h"
#include "utils.h"

//namespace Utils { QTCREATOR_UTILS_EXPORT void writeAssertLocation(const char *msg); }

#define QTC_ASSERT_STRINGIFY_HELPER(x) #x
#define QTC_ASSERT_STRINGIFY(x) QTC_ASSERT_STRINGIFY_HELPER(x)
#define QTC_ASSERT_STRING(cond) Utils::writeAssertLocation(\
    "\"" cond"\" in file " __FILE__ ", line " QTC_ASSERT_STRINGIFY(__LINE__))

// The 'do {...} while (0)' idiom is not used for the main block here to be
// able to use 'break' and 'continue' as 'actions'.

#define QTC_ASSERT(cond, action) if (cond) {} else { QTC_ASSERT_STRING(#cond); action; } do {} while (0)
#define QTC_CHECK(cond) if (cond) {} else { QTC_ASSERT_STRING(#cond); } do {} while (0)
#define QTC_GUARD(cond) ((cond) ? true : (QTC_ASSERT_STRING(#cond), false))

#endif //QTC_ASSERT_INCLUDED_H

