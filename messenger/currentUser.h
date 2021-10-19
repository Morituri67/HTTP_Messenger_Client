#ifndef CURRENTUSER_H
#define CURRENTUSER_H
#include <QMainWindow>
#include <map>
#include <mutex>

class CurrentUser
{
public:
    CurrentUser(CurrentUser& other) = delete;
    void operator=(const CurrentUser& other) = delete;

    void setLogin(const QString& userLogin);
    void setId(const QString& userId);
    void setChats(const QMap<int,QString> chats);
    void setToken(const QString& token);
    void setChats(const std::map<unsigned long, QString> chats);

    const QString& getLogin();
    const QString& getId();
    const QString& getToken();
    const std::map<unsigned long, QString>& getChats();
    static CurrentUser* getInstance();

private:
    CurrentUser(){};
    CurrentUser(const QString& userLogin, const QString& userId)
        : login(userLogin), id(userId){}

    QString login;
    QString id;
    QString accessToken;
    std::map<unsigned long, QString> chats;

    static CurrentUser* instance;
    static std::mutex mtx;
};

#endif // CURRENTUSER_H
