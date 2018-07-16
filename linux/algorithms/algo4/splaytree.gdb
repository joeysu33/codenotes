r
n
l
l 1
b insert 
r
n
b 264
help breakpoints 
help break
info b
help bt
bt
help reakpoints
help breakpoints 
disable breakpoints insert
info b
disable breakpoints 1
info b
l 264
r
s
s
n
n
n
s
q
r
print r
r
bt
q
b 308
r
print k
print *ip@10
print j
print *ip@24967,2
print *(ip+24967)@3
find(k, t)
call find(k,t)
call find(99975800, t)
call find(99977710, t)
print 
print t
t->m_l
print t->m_elem
print t->m_l->m_elem 
call find(94338924, t)
q
q
l
r
b 323
r
l
info b
l 323
q
l 323
b 323
r
q
b 323 327
info b
b 323
b 327
info b
l 323
r
b 341
b 346
r
call dump2(t, "test")
print j
call find(j, t)
call find(4613,t)
call find(91646,t)
call find(36655,t)
help jump
j 326
jump 326
bt
j 325
q
info b
b 323
b 327
help hist
b 341
b 346
info b
r
call dump2(t, "test")
print k
l
b insert 
r
n
display c
n
q
q
l
b insert 
r
b splay
r
r
n
s
s
n
s
b splay_topdown 
n
b splay_topdown 
r
r
r
n
n
b splay_topdown 
r
n
call showTree(t)
l 284
t
print t
call show(t, "aabb")
n
l
help b
b insert if k==5
r
s
n
s
b splay_topdown if k==5
call showTree(t)
call show(t, "aa")
print t->m_val
n
display t->m_val
display t->m_l
display t->m_r
n
print t->m_r
print t->m_r->m_l
print t->m_r->m_r
print t->m_r->m_r->m_r
print t->m_r->m_r->m_l
print t->m_r->m_r->m_r
print t->m_r->m_r->m_r->m_r
print t->m_r->m_r->m_r->m_r->m_r
print t->m_r->m_r->m_r->m_r->m_r->m_r
print t->m_r->m_r->m_r->m_r->m_r->m_r->m_r
n
n
t->m_l->m_val
print t->m_l->m_val
n
n
b splay_topdown if k==5
r
n
display t->m_val, t->m_l, t->m_r
n
display t->m_val
display t->m_l
display t->m_r
n
n
call show(t, "aa")
call show(l.m_l, "bb")
display call show(t, "aa")
help display 
display l
display r
n
help save
apropos save
set history save
record save
record save splaytree-1.rec
record save splaytree-1.rec
apropos save
record save
help record save
apropos record
set record full 
show history filename
n
n
source ./.gdb_history 
l
help breakpoints 
show b
show breakpoint 
file ../bin_dir/splaytree 
b splay_topdown if k==5
r
n
n
apropos logging
show logging 
n
show logging 
apropos logging
set logging on
set history filename splaytree.gdb
b splay_topdown if k==5
set history save on
apropos hist
show history filename
show history save
b splay_topdown if k==5
display t
n
display t->m_l
display t->m_r
shell ls
history
ls
shell ls
show history save
shot history filename
show history filename 
shell cat ./.gdb_history 
n
display t->m_val
n
call show(t,"a")
call show(m_l.m_l, "b")
call show(l.m_l, "b")
n
call show(l.m_l, "a")
call show(t, "b")
n
call show(t, "c")
n
n
call show(t,"a")
call show(l.m_l, "b")
n
call show(t,"a")
call show(l.m_l,"")
print l
print r
print t
n
print l.m_l
print l.m_l->m_r
print l.m_l->m_r->m_val
q
