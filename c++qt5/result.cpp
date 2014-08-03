#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QSslError>
#include <QDebug>
#include <QUrl>
#include <QTimer>
#include <QStringList>
#include "conf.h"

class SMSClient: public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;

public:
    SMSClient();

public slots:
    void checkResult();
    void downloadFinished(QNetworkReply *reply);
    void provideAuthenication(QNetworkReply *reply, QAuthenticator *ator);
};

SMSClient::SMSClient()
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));

    connect(&manager,
            SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            SLOT(provideAuthenication(QNetworkReply*,QAuthenticator*)));
}

void SMSClient::provideAuthenication(QNetworkReply *, QAuthenticator *ator)
{
    ator->setUser(QString(APPID));
    ator->setPassword(QString(APIKEY));
}

void SMSClient::checkResult()
{
    QStringList args = QCoreApplication::instance()->arguments();
    QString program = args.takeFirst();
    if (args.isEmpty()) {
        qCritical() << "Usage";
        qCritical() << QString("  %1 delivery-id").arg(program);
        QCoreApplication::instance()->quit();
        return;
    }
    QString deliveryid = args.takeFirst();
    QUrl url(QString("https://api.bluehouselab.com/smscenter/v1.0/result/%1").arg(deliveryid));
    QNetworkRequest request(url);
    manager.get(request);
}

void SMSClient::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << reply->readAll();
    reply->deleteLater();
    QCoreApplication::instance()->quit();
}
 
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    SMSClient client;
    QTimer::singleShot(0, &client, SLOT(checkResult()));

    app.exec();
}
#include "result.moc"
