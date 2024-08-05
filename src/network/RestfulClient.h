#ifndef RESTCALLTASK_H
#define RESTCALLTASK_H
#include <QObject>
#include <QThread>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QDebug>
#include <QHttpMultiPart>
#include <QSslConfiguration>
#include <QUrlQuery>

#include "../utils/Globals.h"
#include "../Logger/Logger.h"

/**
 * @brief Very basic Restful Clientutility  class, This is NOT a thread safe class.
 * This abstracts the asynchromous calls needed by the Qt api, into a simple synchcronous calls.
 */
class RestfulClient  final : public QObject
{
    Q_OBJECT
public:

    //only get, post and put are implemented
    enum  HttpVerbType
    {
        HTTP_GET,    // The GET method requests a representation of the specified resource.
        // Requests using GET should only retrieve data.
        HTTP_HEAD,   // The HEAD method asks for a response identical to that of a GET request, but without the response body.
        HTTP_POST,   // The POST method is used to submit an entity to the specified resource, often causing a
        // change in state or side effects on the server.
        HTTP_PUT,    // The PUT method replaces all current representations of the target resource with the request payload.
        HTTP_DELETE, // The DELETE method deletes the specified resource.
        HTTP_CONNECT,// The CONNECT method establishes a tunnel to the server identified by the target resource.
        HTTP_OPTIONS,// The OPTIONS method is used to describe the communication options for the target resource.
        HTTP_TRACE,  // The TRACE method performs a message loop-back test along the path to the target resource.
        HTTP_PATCH   // The PATCH method is used to apply partial modifications to a resource.
    };

    enum RestfulCallPostDataType
    {
        Binary,
        Json,
        String
    };

    enum RestfulCallTextEncoding
    {
        UTF8,
        Latin1,//ISO 8859-1, use it for ascii
        Local8Bits // convert to 8 bits according to the os local
    };

private:

    /**
     * @brief The HttpSendDataDecorator class
     */
    class HttpSendDataDecorator
    {
    public:

        /**
         * @brief HttpSendDataDecorator constructor for HttpSendDataDecorator
         * @param manager
         * @param request
         */
        HttpSendDataDecorator(QNetworkAccessManager* manager, QNetworkRequest* request)
        {
            Q_ASSERT(manager != nullptr && request != nullptr);
            m_request = request;
            m_nam = manager;
        }

        /**
         * @brief sendBinaryData
         * @param contentType
         * @param buffer
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendBinaryData(const QString& contentType, const QByteArray& buffer,bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            return sendRawData(contentType, buffer,useHttpPutVerb);
        }

        /**
         * @brief sendBinaryData
         * @param contentType
         * @param data
         * @param size
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendBinaryData(const QString& contentType, const char* data, int size,bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            return sendRawData(contentType, QByteArray(data, size),useHttpPutVerb);
        }

        /**
         * @brief sendJsonData
         * @param contentType
         * @param jsonDocString
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendJsonData(const QString& contentType, const QJsonDocument& jsonDocString,bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            return postGenericStringData(contentType,
                                         QString(jsonDocString.toJson(QJsonDocument::Compact)),
                                         UTF8,useHttpPutVerb);
        }

        /**
         * @brief sendFormData
         * @param contentType
         * @param multiPart
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendFormData(const QString& contentType, QHttpMultiPart *multiPart,bool useHttpPutVerb=false)
        {
            LOG_INFO("");
            Q_UNUSED(contentType)

            m_request->setHeader(QNetworkRequest::ContentLengthHeader, multiPart->boundary());
            if (m_nam->networkAccessible() == QNetworkAccessManager::Accessible)
            {
                qDebug() <<  m_request->url().toDisplayString();
                LOG_INFO( "Post : " + m_request->url().toDisplayString());
                return useHttpPutVerb ?
                            m_nam->put(*m_request, multiPart):
                            m_nam->post(*m_request, multiPart);
            }
            else
            {
                LOG_DEBUG("No network connection !");
                return nullptr;
            }
        }

        /**
         * @brief sendStringData
         * @param contentType
         * @param str
         * @param encoding
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendStringData(const QString& contentType,
                                      const QString& str,
                                      RestfulCallTextEncoding encoding,
                                      bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            return postGenericStringData(contentType,str, encoding,useHttpPutVerb);
        }

    private:
        QNetworkRequest* m_request;
        QNetworkAccessManager* m_nam;

        /**
         * @brief sendRawData
         * @param contentType
         * @param postData
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* sendRawData(const QString& contentType,const QByteArray& postData,bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            m_request->setHeader(QNetworkRequest::ContentTypeHeader, contentType);
            m_request->setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
            if (m_nam->networkAccessible() == QNetworkAccessManager::Accessible)
            {
                LOG_INFO( "Post : " + m_request->url().toDisplayString());
                return useHttpPutVerb ? m_nam->put(*m_request, postData): m_nam->post(*m_request, postData);
            }
            else
            {
                LOG_DEBUG("No network connection !");
                return nullptr;
            }

        }

        /**
         * @brief postGenericStringData
         * @param contentType
         * @param theString
         * @param encoding
         * @param useHttpPutVerb
         * @return
         */
        QNetworkReply* postGenericStringData(const QString& contentType,const QString& theString,
                                             RestfulCallTextEncoding encoding,bool useHttpPutVerb=false)
        {
            LOG_INFO("");

            QByteArray buffer;
            switch (encoding)
            {
                case RestfulCallTextEncoding::UTF8:  buffer = theString.toUtf8(); break;
                case RestfulCallTextEncoding::Latin1: buffer = theString.toLatin1(); break;
                case RestfulCallTextEncoding::Local8Bits: buffer = theString.toLocal8Bit(); break;
                default:
                    break;
            }
            return sendRawData(contentType,buffer,useHttpPutVerb);
        }
    };

public:

    ~ RestfulClient(){}

    /**
     * @brief RestfulClient constructor.
     * @param argBaseUrl : base Url for the api calls that are going to performed by this instance
     * @param ownerThread : indicate the thread where the rest call will be performed.
     */
    explicit RestfulClient(const QUrl& argBaseUrl,QThread* ownerThread = QThread::currentThread())
    {
        LOG_INFO("RestfulClient Constructed for url : " + argBaseUrl.toString());

        //make sure we move the network access manager and the event loop
        // the the thread we're going to operate within.
        m_networkManager.setParent(this);
        m_eventLoop.setParent(this);
        if (ownerThread != QThread::currentThread())
            this->moveToThread(ownerThread);

        m_baseUrl = argBaseUrl;
        m_currentNetworkReply.reset(nullptr);

        //init waiting signals connection
        //when the network manager is finished recieving a net reply read it all
        connect(&m_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));

        //when done reading quit the waiting loop if it's on exec state.
        connect(this, SIGNAL(doneReading()), &m_eventLoop, SLOT(quit()));

        //when ssl errors, report them.
        connect(&m_networkManager, SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
                this, SLOT(sslErrorsSlot(QNetworkReply*, QList<QSslError>)));

        //when disconnected exit a probable current waiting loop
        connect(&m_networkManager, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
                this, SLOT(networkAccessibleChangedSlot(QNetworkAccessManager::NetworkAccessibility)));
    }

    /**
     * @brief addNetworkRequestHeader : adds a custom http request header
     * @param headerName: name of the header
     * @param data: value of the header
     */
    void addNetworkRequestHeader(const QString& headerName,const QByteArray& data)
    {
        LOG_INFO("Adding headers to RestfulClient");
        LOG_INFO("Header Name  : " + headerName);
        LOG_INFO("Header Value : " + data);
        m_requestHeaders[headerName] = data;
    }

    /**
     * @brief addURLQuery
     * @param urlQuery
     */
    void addURLQuery(QUrlQuery urlQuery)
    {
        LOG_INFO("Adding urlQuery to RestfulClient");
        QList<QPair<QString, QString>> queryItems = urlQuery.queryItems();
        for (int i = 0 ; i < queryItems.size() ; i++)
        {
            QPair<QString, QString> queryItem = queryItems.at(i);
            LOG_INFO("queryItem key  : " + queryItem.first);
            LOG_INFO("queryItem key  : " + queryItem.second);
        }
        m_urlQueryList.append(urlQuery);
    }

    /**
     * @brief clearNetworkRequestHeader: clears all http request headers added previously to this isntance
     */
    void clearNetworkRequestHeader()
    {
        m_requestHeaders.clear();
    }

    /**
     * @brief removeNetworkRequestHeader: Remove any header with the name @param headerName from
     * the http request headers.
     * @param headerName : the name of the header to be removed.
     */
    void removeNetworkRequestHeader(const QString& headerName)
    {
        m_requestHeaders.remove(headerName);
    }

    /**
     * @brief getNetworkRequest
     * @param route
     * @return
     */
    QNetworkRequest getNetworkRequest(const QString& route)
    {
        LOG_INFO("");
        LOG_INFO("route : " + route);

        QNetworkRequest request;

        QSslConfiguration config = request.sslConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1_2);
        request.setSslConfiguration(config);

        setRequestHeader(request);
        LOG_INFO("url : " + m_baseUrl.toString() + "/" + route);
        request.setUrl(addQueryItemsToURL(QString(m_baseUrl.toString() + "/" + route)));

        return request;
    }

    /**
     * @brief sendRawData : Perform a post or put call of raw data @arg postData of the type @arg contentType, using the
     * route @arg route. This method is the methdo used by all post/put convinience methods listed below.
     * @param route
     * @param contentType
     * @param postData
     * @param useHttpPutVerb : if truie the call will be http put , otherwise it will be a http post.
     * @return
     */
    bool sendRawData(const QString& route, const QString& contentType, const QByteArray& postData,bool useHttpPutVerb=false)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request = getNetworkRequest(route);
        HttpSendDataDecorator decorator(&m_networkManager, &request);
        m_currentNetworkReply.reset(decorator.sendBinaryData(contentType, postData,useHttpPutVerb));
        if (m_currentNetworkReply == nullptr)
        {
            LOG_ERROR(0,"Network Reply is NULL");
            return false;
        }
        waitForReply();
        LOG_DEBUG("Server Replied SuccessFully");
        return true;
    }

    /**
     * @brief sendRawData : Same as @see sendRawData , the raw data is passed by using a pointer to a buffer.
     * @param route
     * @param contentType
     * @param data
     * @param size
     * @param useHttpPutVerb
     * @return
     */
    bool sendRawData(const QString& route, const QString& contentType, const char* data, int size,bool useHttpPutVerb=false)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request = getNetworkRequest(route);
        HttpSendDataDecorator decorator(&m_networkManager, &request);
        m_currentNetworkReply.reset(decorator.sendBinaryData(contentType, data, size,useHttpPutVerb));
        if (m_currentNetworkReply == nullptr)
        {
            LOG_ERROR(0,"Network Reply is NULL");
            return false;
        }
        waitForReply();
        LOG_DEBUG("Server Replied SuccessFully");
        return true;
    }

    /**
     * @brief sendJsonData : uses @see sendRawData to send A QJsonDocument as post or put data.
     * */
    bool sendJsonData(const QString& route, const QString& contentType, const QJsonDocument& jsonDoc,bool useHttpPutVerb=false)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request = getNetworkRequest(route);
        HttpSendDataDecorator decorator(&m_networkManager, &request);

        m_currentNetworkReply.reset(decorator.sendJsonData(contentType, jsonDoc,useHttpPutVerb));
        if (m_currentNetworkReply == nullptr)
        {
            LOG_ERROR(0,"Network Reply is NULL");
            return false;
        }
        LOG_DEBUG("Waiting for Reply");
        waitForReply();
        LOG_DEBUG("Server Replied SuccessFully");
        return true;
    }

    /**
     * @brief sendStringData : uses @see sendRawData to send A string as post or put data.
     * */
    bool sendStringData(const QString& route, const QString& contentType, const QString& text,
                        RestfulCallTextEncoding encoding,bool useHttpPutVerb=false)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request = getNetworkRequest(route);
        HttpSendDataDecorator decorator(&m_networkManager, &request);
        m_currentNetworkReply.reset(decorator.sendStringData(contentType, text, encoding,useHttpPutVerb));
        if (m_currentNetworkReply == nullptr)
        {
            LOG_ERROR(0,"Network Reply is NULL");
            return false;
        }
        LOG_DEBUG("Waiting for Reply");
        waitForReply();
        LOG_DEBUG("Server Replied SuccessFully");
        return true;
    }

    /**
     * @brief sendFormData : uses @see sendRawData to send A formdata(file) as post or put data.
     * */
    bool sendFormData(const QString& route, const QString& contentType,QHttpMultiPart *multiPart,
                      bool useHttpPutVerb=false)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request = getNetworkRequest(route);
        HttpSendDataDecorator decorator(&m_networkManager, &request);

        m_currentNetworkReply.reset(decorator.sendFormData(contentType, multiPart,useHttpPutVerb));
        if (m_currentNetworkReply == nullptr)
        {
            LOG_ERROR(0,"Network Reply is NULL");
            return false;
        }
        LOG_DEBUG("Waiting for Reply");
        waitForReply();
        LOG_DEBUG("Server Replied SuccessFully");
        return true;
    }

    /**
     * @brief addQueryItemsToURL
     * @param urlStr
     */
    QUrl addQueryItemsToURL(QString urlStr)
    {
        QUrl url(urlStr);
        foreach (QUrlQuery urlQuery, m_urlQueryList)
        {
            url.setQuery(urlQuery);
        }
        return url;
    }

    /**
     * @brief getData : performs a http get call.
     * @param route : the nroute of the call
     * @param parameters : a map representif the parameters of the get show in the url as
     * the substring  "key?value"
     * @param headersMap : the http request header/value map.
     * @return true if success, false otherwise.
     */
    bool getData(const QString& route,const QMap<QString, QVariant>& parameters,const QMap<QString, QString>& headersMap)
    {
        LOG_INFO("");

        restNetworkStatus();
        QNetworkRequest request; setRequestHeader(request);

        QSslConfiguration config = request.sslConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1_2);
        request.setSslConfiguration(config);

        //construct url with parameters
        QString urlStr = m_baseUrl.toString() + "/" + route;
        if (parameters.count() > 1) urlStr += "/";

        foreach(QString paramName, parameters.keys())
        {
            urlStr += QString("%1?%2").arg(paramName).arg(parameters.value(paramName).toString());
        }

        request.setUrl(addQueryItemsToURL(urlStr));

        //add headers
        foreach(QString headerKey, headersMap.keys())
        {
            request.setRawHeader(headerKey.toUtf8(), headersMap.value(headerKey).toUtf8());
        }

        LOG_DEBUG("Get : " + request.url().toDisplayString());
        if (m_networkManager.networkAccessible() == QNetworkAccessManager::Accessible)
        {
            m_currentNetworkReply.reset(m_networkManager.get(request));
            waitForReply();
            return true;
        }
        LOG_DEBUG("No network connection !");
        return false;
    }

    /**
     * @brief getData : A convinience method, uses @see getData
     * @param route
     * @return
     */
    bool getData(const QString& route)
    {
        LOG_INFO("");

        const QMap<QString, QString>  headers;
        const QMap<QString, QVariant> params;
        return getData(route, params, headers);
    }

    /**
     * @brief getData : A convinience method, uses @see getData
     * @param route
     * @return
     */
    bool getData(const QString& route, const QMap<QString, QVariant> parameters)
    {
        LOG_INFO("");

        QMap<QString, QString>  headers;
        return getData(route, parameters, headers);
    }

    /**
     * @brief getData : A convinience method, uses @see getData
     * @param route
     * @return
     */
    bool getData(const QString& route, const QMap<QString, QString> headersMap)
    {
        LOG_INFO("");

        const QMap<QString, QVariant> parameters;
        return getData(route, parameters, headersMap);
    }

    /**
     * @brief lastStatus : returns the last http status recieved upon a call
     * using this instance.
     * @return  the variant value of the @see QNetworkRequest::HttpStatusCodeAttribute
     */
    QVariant lastStatus() const
    {
        LOG_INFO("");

        if (m_currentNetworkReply==nullptr)
            return QVariant();
        return m_currentNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    }

    /**
     * @brief lastReply: returns the last response data received upon a call
     * using this instance.
     * @return
     */
    QByteArray lastReply() const
    {
        LOG_INFO("");
        LOG_INFO("m_lastRepliedData.size : " + QString::number(m_lastRepliedData.size()));
        LOG_INFO("m_lastRepliedData : " + QString::fromStdString(m_lastRepliedData.toStdString()));

        if (m_lastRepliedData.size() > 100)
            LOG_DEBUG("Last reply data size : " + QString::number(m_lastRepliedData.size()));
        else
            LOG_DEBUG("Last reply data size : " + QString::number(m_lastRepliedData.size()));

        return m_lastRepliedData;
    }

signals:
    void doneReading();

private slots:

    /**
     * @brief finishedSlot
     * @param reply
     */
    void finishedSlot(QNetworkReply* reply)
    {
        LOG_DEBUG("finishedSlot");
        if (reply != nullptr) {
            m_lastRepliedData = reply->readAll();
            reply->deleteLater();
        }
        else
            LOG_DEBUG("Reply is NULL");
        emit doneReading();
    }

    /**
     * @brief sslErrorsSlot
     * @param reply
     * @param errors
     */
    void sslErrorsSlot(QNetworkReply* reply, const QList<QSslError>& errors)
    {
        LOG_DEBUG("sslErrorsSlot");

        if (reply != nullptr)
            m_curentSSLErrors.clear();
        if (errors.count() > 1)
            LOG_DEBUG("ssl error for: ");
        m_curentSSLErrors.append(errors);
    }

    /**
     * @brief networkErrorSlot
     * @param error
     */
    void networkErrorSlot(QNetworkReply::NetworkError error)
    {
        LOG_DEBUG("networkErrorSlot");

        if (m_currentNetworkReply != nullptr)
        {
            const auto redirection = m_currentNetworkReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

            if (redirection.isValid()) //no action is taken we're always allowing redirection
                LOG_DEBUG("server redirection : " + redirection.toString());
            else
            {
                LOG_DEBUG("net error : " + m_currentNetworkReply->errorString());
                //the finished signal will follow
                qDebug() << m_currentNetworkReply->error();
            }
        }
        m_currentNetworkError = error;
    }

    /**
     * @brief networkAccessibleChangedSlot
     * @param accessible
     */
    void networkAccessibleChangedSlot(QNetworkAccessManager::NetworkAccessibility accessible)
    {
        if (accessible != QNetworkAccessManager::Accessible)
            if (m_eventLoop.isRunning()) m_eventLoop.quit();
    }   

private:

    /**
     * @brief setRequestHeader
     * @param request
     */
    void setRequestHeader(QNetworkRequest& request)
    {
        for(const auto headerName:m_requestHeaders.keys())
            request.setRawHeader(headerName.toUtf8().data(),m_requestHeaders[headerName]);
    }

    /**
     * @brief restNetworkStatus : reset network errors and status.
     */
    void restNetworkStatus()
    {
        m_curentSSLErrors.clear();
        m_currentNetworkError = QNetworkReply::NoError;
        if (m_currentNetworkReply != nullptr)
        {
            m_currentNetworkReply->deleteLater();
            m_currentNetworkReply.reset(nullptr);
        }
    }

    /**
    * @brief waitForReply : loop while waiting for asynchronous network reply to be available.
    * or a network error to happen.
    */
    void waitForReply()
    {
        m_lastRepliedData.clear();
        //when network error, report it and exit wait loop.
        if (m_currentNetworkReply != nullptr)
        {
            connect(m_currentNetworkReply.data(), SIGNAL(error(QNetworkReply::NetworkError)),
                    this, SLOT(networkErrorSlot(QNetworkReply::NetworkError)));
            m_eventLoop.exec();
        }
    }

    /**
     * @brief m_networkManager : network manager to get and post the data to the server
     */
    QNetworkAccessManager  m_networkManager;

    /**
     * @brief m_CurrentNetworkReply : current network reply getting processed
     */
    QScopedPointer<QNetworkReply> m_currentNetworkReply;

    /**
     * @brief m_LastRepliedData : last network captured reply.
     */
    QByteArray m_lastRepliedData;

    /**
     * @brief m_CurrentNetworkError : last network error
     */
    QNetworkReply::NetworkError  m_currentNetworkError;

    /**
     * @brief m_CurentSSLErrors : last ssl error
     */
    QList<QSslError> m_curentSSLErrors;

    /**
     * @brief m_BaseUrl : base url
     */
    QUrl m_baseUrl;

    /**
     * @brief m_EventLoop : waiting loop.
     */
    QEventLoop m_eventLoop;

    /**
     * @brief m_requestHeaders : will hold the headers to insert into
     * the next network request
     */
    QMap<QString,QByteArray> m_requestHeaders;

    /**
     * @brief m_urlQueryList
     */
    QList<QUrlQuery> m_urlQueryList;
};
#endif // RESTCALLTASK_H
