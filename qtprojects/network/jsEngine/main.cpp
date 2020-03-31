#include <QCoreApplication>
#include <QApplication>
#include <QSocketNotifier>
#include <QTextStream>
#include <QDebug>
#include <unistd.h>
#include <QNetworkAccessManager>
#include <QJSEngine>
#include <QJSValue>
#include <QJSValueIterator>
#include <QWebEngineView>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>

static QTextStream in(stdin, QIODevice::ReadOnly),
    ou(stdout, QIODevice::WriteOnly);

class Foo : public QObject{
    Q_OBJECT
public:
    //ctor must be implements
    Q_INVOKABLE Foo() {}
    Q_INVOKABLE void fa() { ou<<"fa"<<endl; }
    Q_INVOKABLE int add(int x,int y) { return x+y;}
private slots:
    void slotFa() { ou<<"slotFa()"<<endl; }
    int slotSub(int a, int b) { return a-b;}
};

#include "main.moc"

#define METAOBJ(var,x) var[#x] = &x::staticMetaObject;

void installMetaObjects(QJSEngine& eng) {
    QMap<QString, const QMetaObject*> metaObj;
    METAOBJ(metaObj, Foo);
    METAOBJ(metaObj, QNetworkAccessManager);
    METAOBJ(metaObj, QWebEngineView);
    METAOBJ(metaObj, QLineEdit);
    METAOBJ(metaObj, QTextEdit);

    for(auto i=metaObj.begin(); i != metaObj.end(); ++i) {
        auto name = i.key();
        auto v = i.value();
        eng.globalObject().setProperty(name, eng.newQMetaObject(v));
    }

    //metaObj["Foo"] = &Foo::staticMetaObject;
    //metaObj["QNetworkAccessManager"] = &QNetworkAccessManager::staticMetaObject;
    //metaObj["QWebEngineView"] = &QWebEngineView::staticMetaObject;
    eng.globalObject().setProperty("lineEdit", eng.newQObject(new QLineEdit));
}
#undef METAOBJ


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QJSEngine jsEng;
    jsEng.installExtensions(QJSEngine::AllExtensions);
    installMetaObjects(jsEng);

    QSocketNotifier sn(STDIN_FILENO, QSocketNotifier::Read);
    QObject::connect(&sn, &QSocketNotifier::activated, [&]()->void{
                         auto ln = in.readLine();
                         ou<<jsEng.evaluate(ln).toString()<<endl;
                     });
    return a.exec();
}
