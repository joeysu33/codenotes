'''
https://stackoverflow.com/questions/6314982/what-is-recvmsg-equivalent-in-python
pytohn socket的sendmsg和recvmsg并没有实现
瞎忙活
'''
import os
from socket import *
import struct
from unix_sendmsg import *

if __name__ == '__main__':
    os.unlink(UNIX_PATH)

    s = socket(AF_UNIX)
    s.bind(UNIX_PATH)
    s.listen(8)
    cs, caddr = s.accept()

    data, ancdata, msg_flags, address = cs.recvmsg(1024,1024)
    fileno = struct.unpack('<i', ancdata)
    os.write(fileno, b"Written from server!\n")
    os.close(fileno)

