#!/usr/bin/python

import os


libs = ['lib', 'libfree']

cmd=''
#libs
for i in libs:
    cmd = 'make -C %s' % (i,)
    print '----%s' % (cmd,)
    os.system(cmd)

for i in os.listdir('.'):
    if os.path.isdir(i) and not i.startswith('lib'):
        cmd = 'make -C %s' %(i,)
        print '----%s' % (cmd,)
        os.system(cmd)

