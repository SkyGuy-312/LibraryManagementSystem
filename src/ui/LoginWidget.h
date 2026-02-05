#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../core/LibraryService.h"

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    explicit LoginWidget(LibraryService *service, QWidget *parent = nullptr);

private slots:
    void attemptLogin();

private:
    LibraryService *m_service;
    
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginButton;
    QLabel *m_errorLabel;
};

#endif // LOGINWIDGET_H
