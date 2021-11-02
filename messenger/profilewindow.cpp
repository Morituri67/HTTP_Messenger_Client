#include "profilewindow.h"
#include "ui_profilewindow.h"


ProfileWindow::ProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Profile");
    ui->label_Username->setText(CurrentUser::getInstance()->getLogin());

    setPlaceholderTextToLabels();
    hideInfoFields();
    hideLoginFields();
    hidePasswordFields();

    QPropertyAnimation *HideEditAnimation = new QPropertyAnimation(ui->Widget_SaveLogin, "maximumHeight");
    HideEditAnimation->setEasingCurve(QEasingCurve::OutBounce);
    HideEditAnimation->setDuration(1000);
//    HideEditAnimation->setStartValue(40);
//    HideEditAnimation->setEndValue(0);
    QPropertyAnimation *ShowEditAnimation = new QPropertyAnimation(ui->Widget_SaveLogin, "maximumHeight");
    HideEditAnimation->setEasingCurve(QEasingCurve::OutBounce);
    HideEditAnimation->setDuration(1000);
//    HideEditAnimation->setStartValue(0);
//    HideEditAnimation->setEndValue(40);

    QStateMachine *UserNameMachine = new QStateMachine(this);
    UserNameMachine->setGlobalRestorePolicy(QStateMachine::RestoreProperties);

    QState *UserNameHidedState= new QState();
    UserNameHidedState->assignProperty(ui->Widget_SaveLogin,"maximumHeight",0);
    QState *UserNameShowedState= new QState();
    UserNameShowedState->assignProperty(ui->Widget_SaveLogin,"maximumHeight",84);

    QEventTransition *ShowUserNameTransition = new QEventTransition(ui->pushButton_ChangeUsername,QEvent::MouseButtonPress);
    ShowUserNameTransition->setTargetState(UserNameShowedState);
    ShowUserNameTransition->addAnimation(ShowEditAnimation);
    UserNameHidedState->addTransition(ShowUserNameTransition);

    QEventTransition *HideUserNameTransition = new QEventTransition(ui->pushButton_ChangeUsername,QEvent::MouseButtonPress);
    HideUserNameTransition->setTargetState(UserNameHidedState);
    HideUserNameTransition->addAnimation(HideEditAnimation);
    UserNameShowedState->addTransition(HideUserNameTransition);

    UserNameMachine->addState(UserNameHidedState);
    UserNameMachine->addState(UserNameShowedState);
    UserNameMachine->setInitialState(UserNameHidedState);
    UserNameMachine->start();

    QPropertyAnimation *ShowPasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_Password, "maximumHeight");
    ShowPasswordEditAnimation->setDuration(1000);
    ShowPasswordEditAnimation->setStartValue(0);
    ShowPasswordEditAnimation->setEndValue(40);
    QPropertyAnimation *ShowNewPasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_NewPassword, "maximumHeight");
    ShowNewPasswordEditAnimation->setDuration(1000);
    ShowNewPasswordEditAnimation->setStartValue(0);
    ShowNewPasswordEditAnimation->setEndValue(40);
    QPropertyAnimation *ShowConfirmPasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_ConfNewPassword, "maximumHeight");
    ShowConfirmPasswordEditAnimation->setDuration(1000);
    ShowConfirmPasswordEditAnimation->setStartValue(0);
    ShowConfirmPasswordEditAnimation->setEndValue(40);

    QSequentialAnimationGroup *ShowPassGroup = new QSequentialAnimationGroup();
    ShowPassGroup->addAnimation(ShowPasswordEditAnimation);
    ShowPassGroup->addAnimation(ShowNewPasswordEditAnimation);
    ShowPassGroup->addAnimation(ShowConfirmPasswordEditAnimation);

    QPropertyAnimation *HidePasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_Password, "maximumHeight");
    HidePasswordEditAnimation->setDuration(1000);
    HidePasswordEditAnimation->setStartValue(40);
    HidePasswordEditAnimation->setEndValue(0);
    QPropertyAnimation *HideNewPasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_NewPassword, "maximumHeight");
    HideNewPasswordEditAnimation->setDuration(1000);
    HideNewPasswordEditAnimation->setStartValue(40);
    HideNewPasswordEditAnimation->setEndValue(0);
    QPropertyAnimation *HideConfirmPasswordEditAnimation = new QPropertyAnimation(ui->lineEdit_ConfNewPassword, "maximumHeight");
    HideConfirmPasswordEditAnimation->setDuration(1000);
    HideConfirmPasswordEditAnimation->setStartValue(40);
    HideConfirmPasswordEditAnimation->setEndValue(0);

    QSequentialAnimationGroup *HidePassGroup = new QSequentialAnimationGroup();
    HidePassGroup->addAnimation(HidePasswordEditAnimation);
    HidePassGroup->addAnimation(HideNewPasswordEditAnimation);
    HidePassGroup->addAnimation(HideConfirmPasswordEditAnimation);

    QState *PasswordHidedState = new QState();
    QState *PasswordShowedState = new QState();

    QEventTransition *ShowPasswordTransition = new QEventTransition(ui->pushButton_ChangePassword,QEvent::MouseButtonPress);
    ShowPasswordTransition->setTargetState(PasswordShowedState);
    ShowPasswordTransition->addAnimation(ShowPassGroup);
    PasswordHidedState->addTransition(ShowPasswordTransition);

    QEventTransition *HidePasswordTransition = new QEventTransition(ui->pushButton_ChangePassword,QEvent::MouseButtonPress);
    HidePasswordTransition->setTargetState(PasswordHidedState);
    HidePasswordTransition->addAnimation(HidePassGroup);
    PasswordShowedState->addTransition(HidePasswordTransition);


    QStateMachine *PasswordMachine = new QStateMachine(this);
//    PasswordMachine->setGlobalRestorePolicy(QStateMachine::RestoreProperties);
    PasswordMachine->addState(PasswordHidedState);
    PasswordMachine->addState(PasswordShowedState);
    PasswordMachine->setInitialState(PasswordHidedState);
    PasswordMachine->start();

}

ProfileWindow::~ProfileWindow()
{
    delete ui;
}

void ProfileWindow::setPlaceholderTextToLabels()
{
    CurrentUser *user = CurrentUser::getInstance();
    ui->lineEdit_Username->setPlaceholderText(user->getLogin());
    ui->lineEdit_Password->setPlaceholderText(" Enter your password:");
    ui->lineEdit_NewPassword->setPlaceholderText(" Enter new password:");
    ui->lineEdit_ConfNewPassword->setPlaceholderText(" Confirm new password:");
}

void ProfileWindow::hideInfoFields()
{
    ui->label_LoginInfo->hide();
    ui->label_ConfPassInfo->hide();
}

void ProfileWindow::hideLoginFields()
{
    ui->lineEdit_Username->hide();
    ui->pushButton_SaveLogin->hide();
}

void ProfileWindow::hidePasswordFields()
{
    ui->lineEdit_Password->hide();
    ui->lineEdit_NewPassword->hide();
    ui->lineEdit_ConfNewPassword->hide();
    ui->pushButton_SavePassword->hide();
}

void ProfileWindow::on_pushButton_ChangeUsername_clicked()
{
    if(ui->pushButton_ChangeUsername->isChecked())
    {
        hideInfoFields();
        showLoginFields();
    }
    else
    {
        hideLoginFields();
    }
}

void ProfileWindow::showLoginFields()
{
    ui->lineEdit_Username->show();
    ui->pushButton_SaveLogin->show();
}

void ProfileWindow::on_pushButton_ChangePassword_clicked()
{
    if(ui->pushButton_ChangePassword->isChecked())
    {
        hideInfoFields();
        showPasswordFields();
    }
    else
    {
        hidePasswordFields();
    }
}

void ProfileWindow::showPasswordFields()
{
    ui->lineEdit_Password->show();
    ui->lineEdit_NewPassword->show();
    ui->lineEdit_ConfNewPassword->show();
    ui->pushButton_SavePassword->show();
}

void ProfileWindow::on_pushButton_SaveLogin_clicked()
{
    QString newLogin = ui->lineEdit_Username->text();

    hideInfoFields();
    checkUsernameSame(newLogin);

    RequestManager::GetInstance()->updateLogin(CurrentUser::getInstance()->getToken(),newLogin,this);
}

void ProfileWindow::on_pushButton_SavePassword_clicked()
{
    QString password = ui->lineEdit_Password->text();
    QString newPassword = ui->lineEdit_NewPassword->text();
    QString newPassConf = ui->lineEdit_ConfNewPassword->text();

    hideInfoFields();
    checkPasswordEqual(newPassword,newPassConf);
    checkOldNewPasswordsEqual(password,newPassword);

    RequestManager::GetInstance()->updatePassword(CurrentUser::getInstance()->getToken(),password,newPassword,this);
}

void ProfileWindow::checkUsernameSame(const QString& username)
{
   CurrentUser *user = CurrentUser::getInstance();
   if(username == user->getLogin())
   {
       setErrorLabelColor(ui->label_LoginInfo);
       ui->label_LoginInfo->show();
       ui->label_LoginInfo->setText("Your new username is the same as your previous");
   }
}

void ProfileWindow::checkPasswordEqual(const QString& pass1, const QString& pass2)
{
    if(pass1 != pass2)
    {
       setErrorLabelColor(ui->label_ConfPassInfo);
       ui->label_ConfPassInfo->show();
       ui->label_ConfPassInfo->setText("Your password inputs are not equal. Try again.");
    }
}

void ProfileWindow::checkOldNewPasswordsEqual(const QString& pass, const QString& newPass)
{
    if(pass == newPass)
    {
       setErrorLabelColor(ui->label_ConfPassInfo);
       ui->label_ConfPassInfo->show();
       ui->label_ConfPassInfo->setText("Your new password is the same as your previous.");
    }
}

void ProfileWindow::setErrorLabelColor(QLabel *label)
{
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::white);
    palette.setColor(label->foregroundRole(), Qt::red);
    label->setPalette(palette);
}

void ProfileWindow::onRequestFinished(QNetworkReply *reply, RequestType type)
{
    if (reply->error())
    {
        JsonDeserializer extractor;
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QString resReply = extractor.extractErrorMsg(document);
        QMessageBox::critical(nullptr, "ERROR", resReply);
    }
    else
    {
        if(type == RequestType::UPDATE_LOGIN)
        {
            CurrentUser *user = CurrentUser::getInstance();
            user->setLogin(ui->lineEdit_Username->text());
            ui->label_Username->setText(user->getLogin());
            ui->lineEdit_Username->clear();
            ui->lineEdit_Username->setPlaceholderText(user->getLogin());
            QMessageBox::information(nullptr, "Profile", "Login was updated!");
            Cache::DeleteCacheFile();
            Cache::CreateIfNotExists(CurrentUser::getInstance()->getLogin());
        }
        if(type == RequestType::UPDATE_PASSWORD)
        {
            QMessageBox::information(nullptr, "Profile", "Password was updated!");
        }
    }
}

void ProfileWindow::closeEvent(QCloseEvent * e )
{
    emit closing();
}
