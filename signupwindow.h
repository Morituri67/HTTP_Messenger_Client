#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
    QString GetLogin();
    QString GetPassword();
    QString GetPasswordAgain();
    void close_window();

signals:
    void LoginButton_signal();
    void SignupButton_signal();

private slots:
    void on_SignupButton_clicked();
    void on_LoginButton_clicked();

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H