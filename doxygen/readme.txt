# If you want full control over the layout of the generated HTML pages it might
# be necessary to disable the index and replace it with your own. The
# DISABLE_INDEX tag can be used to turn on/off the condensed index (tabs) at top
# of each HTML page. A value of NO enables the index and the value YES disables
# it. Since the tabs in the index contain the same information as the navigation
# tree, you can set this option to YES if you also set GENERATE_TREEVIEW to YES.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

DISABLE_INDEX          = YES

# The GENERATE_TREEVIEW tag is used to specify whether a tree-like index
# structure should be generated to display hierarchical information. If the tag
# value is set to YES, a side panel will be generated containing a tree-like
# index structure (just like the one that is generated for HTML Help). For this
# to work a browser that supports JavaScript, DHTML, CSS and frames is required
# (i.e. any modern browser). Windows users are probably better off using the
# HTML help feature. Via custom style sheets (see HTML_EXTRA_STYLESHEET) one can
# further fine-tune the look of the index. As an example, the default style
# sheet generated by doxygen has an example that shows how to put an image at
# the root of the tree instead of the PROJECT_NAME. Since the tree basically has
# the same information as the tab index, you could consider setting
# DISABLE_INDEX to YES when enabling this option.
# The default value is: NO.
# This tag requires that the tag GENERATE_HTML is set to YES.

GENERATE_TREEVIEW      = NO


控制Doxygen每页上部出现的导航栏的选项是DISABLE_INDEX,
DISABLE_INDEX设置NO,则显示导航栏，否则不显示

控制左侧树视图的是GENERATE_TREEVIEW

在生成qch文档的时候，图片的设置一定是\image html XXXX.png
去掉html,图片不会加入到qch中，在assistant中无法正常显示
\image rtf XXX.png 可以加入到rtf中


可以使用DoxygenLayout.xml文件来配置doxygen文档的组织方式

可以使用\page和\subpage来将多页以文档结构进行组合

可以使用 INPUT变量来控制page在文档结构中的顺序，例如
INPUT = main.dox \
        page1.dox \
        page2.dox


如果要将page1的顺序调整到上面，则
INPUT = main.dox \
        page2.dox \
        page1.dox








