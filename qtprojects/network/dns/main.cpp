#include <QCoreApplication>
#include <QDnsLookup>
#include <QHostAddress>
#include <QDebug>
#include <QMetaObject>
#include <QMetaEnum>
#include <algorithm>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QMetaObject mo = QDnsLookup::staticMetaObject;
    int index = mo.indexOfEnumerator("Type");
    QMetaEnum me = mo.enumerator(index);

    int cnt=0;
    for(int k=0; k<me.keyCount(); ++k) {
    qDebug()<<"Lookup... "<<me.key(k)<<", "<<me.value(k);
    QDnsLookup *lookup = new QDnsLookup(static_cast<QDnsLookup::Type>(me.value(k)), "news.163.com");
    QObject::connect(lookup, &QDnsLookup::finished, [&cnt,lookup, me, &a]()->void {
                         //QDnsLookup *lookup = qobject_cast<QDnsLookup*>(sender());

                         {
                             auto r =lookup->hostAddressRecords();
                             std::for_each(r.begin(), r.end(), [](const QDnsHostAddressRecord &ar)->void{
                                 qDebug()<<ar.name()<<","<<ar.value()<<","<<ar.timeToLive();
                             }) ;
                         }
                         {
                             auto r =lookup->nameServerRecords();
                             std::for_each(r.begin(), r.end(), [](const QDnsDomainNameRecord &ar)->void{
                                 qDebug()<<ar.name()<<","<<ar.value()<<","<<ar.timeToLive();
                             }) ;
                         }
                         {
                             auto r =lookup->pointerRecords();
                             std::for_each(r.begin(), r.end(), [](const QDnsDomainNameRecord &ar)->void{
                                 qDebug()<<ar.name()<<", "<<ar.value()<<","<<ar.timeToLive();
                             }) ;
                         }
                         {
                             auto r =lookup->serviceRecords();
                             std::for_each(r.begin(), r.end(), [](const QDnsServiceRecord &ar)->void{
                                 qDebug()<<"name="<<ar.name()<<" port="<<ar.port()<<" target="<<ar.target()
                                 <<" weight="<<ar.weight();
                             }) ;
                         }
                         {
                             auto r =lookup->textRecords();
                             std::for_each(r.begin(), r.end(), [](const QDnsTextRecord &ar)->void{
                                 qDebug()<<ar.name()<<","<<ar.values();
                             }) ;
                         }

                         if(lookup->error() != QDnsLookup::NoError)
                             qDebug()<<"error:"<<lookup->errorString();
                         lookup->deleteLater();

                         if(++cnt == me.keyCount())
                             a.quit();
    });

    lookup->lookup();
    }

    return a.exec();
}
