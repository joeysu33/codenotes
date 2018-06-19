#if !defined(_SVMSQ_MSG_INCLUDED_H_)
#define _SVMSQ_MSG_INCLUDED_H_

/*!
 * 变长消息格式
 */
typedef struct svmsq_msg {
    long mtype;
    char msg[];
} svmsq_msg_t;

/*!
 * 固定长度消息格式
 */

#define MAXMSG 1024  /*! 指定最大的消息大小 */
typedef struct svmsq_msg2 {
    long mtype;
    char msg[MAXMSG];
} svmsq_msg2_t;

#endif //_SVMSQ_MSG_INCLUDED_H_


