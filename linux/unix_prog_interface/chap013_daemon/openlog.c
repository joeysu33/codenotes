/*!
 * 系统日志
 * #include <syslog.h>
 * void openlog(const char* indent, int options, int facility);
 * void closelog(void);
 * void syslog(int priority, const char *msg, ...);
 */

#include <syslog.h>
#include <stdio.h>
#include <unistd.h>

int
main() {
    openlog("[[[[myindent]]]]", LOG_NDELAY, LOG_LOCAL5);

    syslog(LOG_INFO | LOG_LOCAL1, "ds-test1:%s,%s,%m", "aa","bb");
    syslog(LOG_DEBUG | LOG_LOCAL2, "ds-test2:%s,%s,%m", "aa","bb");
    syslog(LOG_DEBUG , "ds-test2:%s,%s,%m", "aa","bb");

    closelog();

    return 0;
}
