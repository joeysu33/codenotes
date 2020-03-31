#include <QCoreApplication>
#include <QSocketNotifier>
#include <unistd.h>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextStream>
#include <QIODevice>
#include <cassert>

#include <QScriptValue>
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptable>
#include <QNetworkProxy>
#include <QNetworkProxyFactory>

using namespace std;

static QTextStream ou(stdout,QIODevice::WriteOnly);

class TestNAM : public QObject {
    Q_OBJECT
public:
    TestNAM(QObject * p = nullptr): QObject(p) {
        m_nam = new QNetworkAccessManager(this);
//        QNetworkProxyFactory::usesSystemConfiguration();
//        QNetworkProxy proxy = QNetworkProxy::applicationProxy();
        QNetworkProxy proxy;
        proxy.setHostName("Proxy7.bj.petrochina");
        proxy.setPort(8080);
        proxy.setType(QNetworkProxy::HttpProxy);
        qDebug()<<"application proxy:"<<proxy;
        m_nam->setProxy(proxy);

        connect(m_nam,SIGNAL(finished(QNetworkReply*)),this,
            SLOT(onReplyFinish(QNetworkReply*)));
    }
    ~TestNAM() { delete m_nam; }

    Q_INVOKABLE void get(const QString&url) {
        QNetworkRequest u;
        u.setUrl(url);
        m_nam->get(u);
    }
private slots:
    void onReplyFinish(QNetworkReply* reply) {
        Q_ASSERT(reply);
        ou<<reply->readAll()<<endl;
        reply->deleteLater();
    }
private:
    QNetworkAccessManager*m_nam {nullptr};
};

#include "main.moc"

//scriptValueFromQMetaObject
Q_SCRIPT_DECLARE_QMETAOBJECT(TestNAM, QObject*)


int main(int argc, char *argv[]) {
    QCoreApplication a(argc,argv);
    QTextStream in(stdin, QIODevice::ReadOnly);


    ou<<"======Request====="<<endl;
    TestNAM nam;
    QScriptEngine eng;
    QScriptValue testNAMCls = 
        eng.scriptValueFromQMetaObject<TestNAM>();
    eng.globalObject().setProperty("TestNAM", testNAMCls);
    eng.evaluate("var nam = new TestNAM();");

    QObject::connect(&eng, &QScriptEngine::signalHandlerException,[&](const QScriptValue& ex)->void{
                auto eng = ex.engine();
                ou<<"exceptions:"<<ex.toString()<<endl;
                //ou<<eng->uncaughtExceptionBacktrace()<<endl;
        });
    
    QSocketNotifier ns(STDIN_FILENO, QSocketNotifier::Read);
    QObject::connect(&ns,
            &QSocketNotifier::activated,[&]() ->void {
                auto line = in.readLine();
                auto r = eng.evaluate(line);
                ou<<r.toString()<<endl;
        });

    return a.exec();
}


