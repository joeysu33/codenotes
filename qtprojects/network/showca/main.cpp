#include "certificateinfo.h"
#include "mainwindow.h"
#include <QApplication>
#include <QSslCertificate>
#include <QString>
#include <QDebug>

static const QString DIRBASE="/home/ds/github.com/QSslSocket-example/certificates/";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    for(int i=1; i<argc; ++i) {
        CertificateInfo  *cer = new CertificateInfo();
        cer->setAttribute(Qt::WA_DeleteOnClose,true);
        CertificateInfo  &ca = *cer;
        cer->setWindowTitle(argv[i]);
        auto certs = QSslCertificate::fromPath(DIRBASE + argv[1]);
        qDebug()<<"Certs count["<<i<<"]="<<certs.size();
        ca.setCertificateChain(certs);
        ca.show();
    }

    return a.exec();
}
