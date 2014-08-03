#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QSslError>
#include <QDebug>
#include <QUrl>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    void sendSMS();
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

void SMSClient::sendSMS()
{
    QUrl url("https://api.bluehouselab.com/smscenter/v1.0/sendsms");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                        QVariant("application/json; charset=utf-8"));

    QJsonDocument json;
    QJsonObject obj;
    obj["sender"] = QString(SENDER);
    QJsonArray receivers;
    receivers.push_back(QString(RECEIVER));
    obj["receivers"] = receivers;
    obj["content"] = QString(CONTENT);
    json.setObject(obj);
    manager.post(request, json.toJson());
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
    QTimer::singleShot(0, &client, SLOT(sendSMS()));

    app.exec();
}
#include "sendsms.moc"
