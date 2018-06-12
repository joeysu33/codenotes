import time
from socket import *
import struct
from unix_sendmsg import *

if __name__ == '__main__':
    s = socket(AF_UNIX, SOCK_STREAM,0)
    s.connect(UNIX_PATH)
    f = open(FILE_PATH, 'w+', encoding='utf-8')

    f.write('Written from client!\n')
    data = struct.pack('<i',f.fileno())
    ancillary = [(SOL_SOCKET, SCM_RIGHTS, data),]
    sndcnt = s.sendmsg(bytes('aabbcc', encoding='utf8'))
    # sndcnt = s.sendmsg('aabb'.encode(), ancillary)

    '''
    这里直接写成s.sendmsg(b'aabb',XXX)失败，
    只能是用str.encod()来转换？？？
    '''
    # buff = b'aabb'
    # s.sendmsg(buff)
    # time.sleep(5)
    s.close()
    f.close()

