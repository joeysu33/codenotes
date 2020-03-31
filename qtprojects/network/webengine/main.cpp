#include <QCoreApplication>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineScriptCollection>

#include <QApplication>
#include <QSocketNotifier>
#include <QNetworkProxy>
#include <QNetworkProxyFactory>

#include <QTextEdit>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QNetworkAccessManager>


#include <unistd.h>
#include <cstdio>

static const quint32 wid = 3354;

QWebEngineScript makeCust() {
    return QWebEngineScript();

    //static const QString code= ""
    //        "@require https://code.jquery.com/jquery-3.4.1.min.js\n"
    //        "console.log('injected successuly');\n"
    //        "alert('hello qwebenginewidgets!');\n";
    //static const QString code = "alert('hello qwebenginewidgets!');";
    static const QString code = "";

    QWebEngineScript ws;
    ws.setName("custom");
    ws.setSourceCode(code);
    ws.setInjectionPoint(QWebEngineScript::Deferred);
//    ws.setWorldId(wid);
    return ws;
}

QWebEngineScript loadJQuery() {
    return QWebEngineScript();

    QFile file(":/jquery-3.4.1.min.js");
    if(!file.open(QFile::ReadOnly)) {
        qDebug()<<"open failed:"<<file.fileName() <<endl;
        return QWebEngineScript();
    }
    QString code =  file.readAll();
    file.close();

    QWebEngineScript ws;
    ws.setName("custom");
    ws.setSourceCode(code);
    ws.setInjectionPoint(QWebEngineScript::DocumentReady);
//    ws.setWorldId(wid);
    return ws;
}

QWebEngineScript loadJQuery2() {
    QString code = "var jq = document.createElement('script');\n"
            "jq.setAttribute('src','https://code.jquery.com/jquery-3.4.1.min.js');\n"
            "document.body.appendChild(jq);";
    QWebEngineScript ws;
    ws.setName("custom");
    ws.setSourceCode(code);
    ws.setInjectionPoint(QWebEngineScript::DocumentReady);
    return ws;
}

void setPageSettings(QWebEnginePage *p) {
    QWebEngineSettings *se = p->settings();
    se->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    se->setAttribute(QWebEngineSettings::PluginsEnabled,true);
}

void applyNetProxy() {
    QNetworkProxyFactory::setUseSystemConfiguration(true);
}

void appendLine(QTextEdit *txt, const QString &newLine) {
    QString old = txt->toPlainText();
    txt->setPlainText(QString("%1\n%2").arg(old).arg(newLine));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);
    QTextStream in(stdin, QFile::ReadOnly);
    applyNetProxy();

    QTextEdit out;
    QWebEngineView view;
    QWebEnginePage * page = view.page();
    QWebEngineProfile *pro = view.page()->profile();
    pro->scripts()->insert(makeCust());
    pro->scripts()->insert(loadJQuery());
    pro->scripts()->insert(loadJQuery2());

    qDebug()<<"Injection:"<<pro->scripts()->size()<<" scripts."<<endl;

    setPageSettings(page);

    //??
    //QObject::connect(&page, &QWebEnginePage::loadFinished, [&](){
    //    qDebug()<<"Load finished:"<<page->url();
    //});
    QObject::connect(page, &QWebEnginePage::loadFinished, [&](bool)->void{
        qDebug()<<"load finished:"<<page->url()<<endl;
    });
    QObject::connect(&view, &QWidget::destroyed, &out, &QWidget::close);

    QSocketNotifier sn(STDIN_FILENO, QSocketNotifier::Read);
    QObject::connect(&sn, &QSocketNotifier::activated, [&]()->void{
                         QString line = in.readLine();
                         if(line.toLower() == "q" ||
                         line.toLower() == "quit") { a.exit(0); }

                         page->runJavaScript(line, [&](const QVariant& v)->void{
                             QString res;
                             if(v.type() == QVariant::List) {
                                 for(auto a : v.toList())
                                    res += a.toString()+"\n";
                             } else
                                 res = v.toString();

                             qDebug()<<"after evalueted:"<<res<<endl;
                             appendLine(&out, res);
                         });
                         QApplication::processEvents();
                     });

    view.load(QUrl::fromUserInput("news.163.com"));
    view.show();
    if(!out.isVisible()) {
        out.resize(400, 250);
        out.show();
    }


    return a.exec();
}
