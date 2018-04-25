/*!
 * chat msg的消息格式
 */

#if !defined(_CHATMSG_INCLUDED_H)
#define _CHATMSG_INCLUDED_H

#define MSG_SIZE 65535 

typedef struct chatmsg {
    char m_name[32];
    char m_msg[MSG_SIZE];
    char m_extra[4];
} chatmsg_t;

static const int chatMsgLen = sizeof(chatmsg_t);

#endif //_CHATMSG_INCLUDED_H

