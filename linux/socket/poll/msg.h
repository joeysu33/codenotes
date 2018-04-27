#if !defined(POLL_CHATROOM_MSG_)
#define POLL_CHATROOM_MSG_

/*!
 * 变长数据
 */
typedef struct chatmsg {
    int  m_sender[20];
    char m_msg[1024];
} chatmsg_t;

static const int chatMsgLen = sizeof(chatmsg_t);

#endif
