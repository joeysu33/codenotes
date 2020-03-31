#include <QCoreApplication>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a);
    QStringList args;
    args << argv[0] <<"aa"<<"bb"<<"--file=aa.txt"<<"-d"<<"/etc/mtools.conf"<<"-x"<<"haha";
    QCommandLineOption opt1(QStringList()<<"f"<<"file", "file", "fil");
    QCommandLineOption opt2(QStringList()<<"d"<<"dir", "directory", "dir");
    QCommandLineParser parser;
    parser.addOptions(QList<QCommandLineOption>{opt1,opt2});
    bool ok= parser.parse(args);
    QString file = parser.value("f");
    QString file2 = parser.value(opt1);
    QString dir  = parser.value(opt2);
    qDebug()<<"ok="<<ok<<" file="<<file<<", file2"<<file2<<", dir="<<dir;

    return 0;
}
