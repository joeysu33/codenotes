############################################################
    2019-10-30 by davidsu33@qq.com
############################################################

How to generator "qch"
1. Make comments in your source files, like your *.cpp, *.cxx,*.cc,
  and using the qoc tags:
  see also:
  Qt 5.8/QDoc Manual/Command Index
2. Edit your *.qdocconf ,like this:

    project = testlib
    description = This is a example for qdoc
    version = 1.0


    #It's needed
    sourcedirs = .
    #It's needed
    headerdirs = .
    outputdir = html
    #It's needed
    sources.fileextensions = *.cc *.cpp *.cxx
    #It's needed
    headers.fileextensions = *.h *.hpp
    sourceencoding = UTF-8

    #sources = testlib.cpp
    #headers = testlib.h
    #outputencoding = UTF-8

    #It's needed
    qhp.projects = TestLib
    qhp.TestLib.file = testlib.qhp
    qhp.TestLib.namespace = org.Testing.TestLib
    qhp.TestLib.virtualFolder = testlib
    qhp.TestLib.indexTitle = TestLib Modulor
    qhp.TestLib.indexRoot =

    #It's needed
    qhp.TestLib.subprojects.classes.title = Classes
    qhp.TestLib.subprojects.classes.title = TestLib Classes
    qhp.TestLib.subprojects.classes.indexTitle = Qt Quick C++ Classes
    qhp.TestLib.subprojects.classes.selectors = class fake:headerfile
    qhp.TestLib.subprojects.classes.sortPages = true

3.run qdoc command,like this, $$QTBIN/qdoc mytest.qdocconf
4.enter your doc output directory (here it's "html") and execute command 'qhelpgenerator mytest.qhp -o mytest.qch'
5.open your qt assistant and load mytest.qch, then you can see your installed classes, when you using them in coding.







