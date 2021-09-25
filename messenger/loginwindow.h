#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QRegularExpressionValidator>
#include <requestmanager.h>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget, virtual public RequestManager
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool CheckInput();
    void ClearInfoFields();

signals:
    void LoginSuccess(QString);
    void OpenSignupWindow();

private slots:
    void on_LoginButton_clicked();
    void on_SignupButton_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
