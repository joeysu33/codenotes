/*
 * 非阻塞式的消息格式
 *
 */

#if !defined(_NONBLOCK_MSG_INCLUDED_)
#define _NONBLOCK_MSG_INCLUDED_

#define MSG_SIZE 60000
#define MSG_PORT 6666

typedef struct nb_chatmsg {
    char m_from[20];
    char m_to[20];
    char m_msg[MSG_SIZE];
} nb_chatmsg_t;

static const int nbChatMsgLen = sizeof(nb_chatmsg_t);


#endif
