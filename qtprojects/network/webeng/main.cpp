#include "mainwindow.h"
#include <QApplication>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineHistory>
#include <QWebEngineSettings>
#include <QtWebEngine/QtWebEngine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qDebug()<<"sizeof(long)="<<sizeof(long long);
    MainWindow w;
    w.show();

//    QtWebEngine::initialize();
    //const QString addr = "https://music.163.com/";
    //QWebEngineView view;
    //view.settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    //view.settings()->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    ////view.load(QUrl("https://www.baidu.com"));
    //view.load(QUrl(addr));
    //view.show();

    return a.exec();
}
