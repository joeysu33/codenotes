#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void addRectToPolyClockwise(QPolygon &p, QRect & r) {
    p.append(r.topLeft());
    p.append(r.topRight());
    p.append(r.bottomRight());
    p.append(r.bottomLeft());
    p.append(r.topLeft());
}

void addRectToPolyAntiClockwise(QPolygon &p, QRect &r) {
    p.append(r.topLeft());
    p.append(r.bottomLeft());
    p.append(r.bottomRight());
    p.append(r.topRight());
    p.append(r.topLeft());
}

/*!
 * \brief MainWindow::paintEvent
 * \param event
 *
 * QPainter中的Qt::OddEventFill和Qt::WindingFill的区别
 * 多边形的填充，一般采用的算法都是扫描线算法
 * 大致的原理是，找到多边形的外界矩形，然后水平（或垂直）
 * 的扫描，一旦和多边形有了交点，则根据交点来判断该交点
 * 是在多边形内部还是外部，问题的难点主要在于判断的部分
 *
 * 奇偶填充是通过，填充奇数交点到偶数交点来实现的，例如
 * 我们在正方形的中间，绘制一条水平线，则水平线和正方形存在
 * 两个交点，从左到右，这些交点依次标记上1,2,,,...，碰到奇数到
 * 偶数的，则认为落到了图形内部，否则认为在图形外部（对于
 * 五角星，五角星的五个角会被绘制，但是中间的五边形却不会被
 * 绘制，就是因为奇偶绘制的原理，只从奇数向偶数进行绘制)
 *
 * WindingFill也是从图形中绘制一条水平（或垂直）线，然后将该条
 * 直线中与图形的交点进行判断，如果交点是图形的顺时针方向则减一（或加一），
 * 否则加一（或减一），只要最后的结果不为0，则认为该点在图形内部，
 * 否则在图形的外部。这个方法绘制的时候，对于执行图形的线条的顺序（也就是
 * 图形的方向）是很重要的。最经典的例子就是同心圆，两个同心圆在绘制的时候
 * 如果绘制方向一致（即点的指向方向相同），则最中间的圆心会填充，否则不填充
 * ，当然也可以将同心圆换成两个同心的矩形
 *
 * Winding填充（缠绕填充)
 * 1.Qt::OddEventFill指的是奇偶填充，
 * 2.Qt::WindingFill 指的是缠绕填充，又称为非0的WindingFill，根据计数来判断
 *
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);
    QRect r1 = rect();
    QRect r2 = r1, r3 = r1;

    /*! r2和r3分别占据两个半边 */
    r2.setWidth(r1.width() / 2);
    r3.setWidth(r2.width());
    r3.moveLeft(r3.width());

    QRect lr[2], rr[2];
    int span1 = 30, span2 = 50;
    lr[0] = r2.adjusted(span1, span1, -span1, -span1);
    lr[1] = r2.adjusted(span2, span2, -span2, -span2);

    rr[0] = r3.adjusted(span1, span1, -span1, -span1);
    rr[1] = r3.adjusted(span2, span2, -span2, -span2);

    /*! 特别需要注意这里 */
    QPolygon p1, p2;
    addRectToPolyClockwise(p1, lr[0]);
    addRectToPolyClockwise(p1, lr[1]);

    addRectToPolyClockwise(p2, rr[0]);
    addRectToPolyAntiClockwise(p2, rr[1]);

    QBrush b1, b2;
    b1.setColor(Qt::yellow);
    b2.setColor(Qt::blue);
    b1.setStyle(Qt::SolidPattern);
    b2.setStyle(Qt::SolidPattern);

    QPen pen1, pen2;
    pen1.setColor(QColor(Qt::green));
    pen2.setColor(QColor(Qt::gray));
    pen1.setWidth(3);
    pen2.setWidth(3);

    p.setBrush(b1);
    p.setPen(pen1);
    /*!这里如果是Qt::WindingFill，那么整个都会填充，
     * 否则仅填充两个四边形的中间间隙*/
    p.drawPolygon(p1, Qt::WindingFill);

    p.setBrush(b2);
    p.setPen(pen2);
    p.drawPolygon(p2, Qt::WindingFill);
}

