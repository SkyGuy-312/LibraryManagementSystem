#include "LoginWidget.h"
#include <QVBoxLayout>
#include <QFormLayout>

LoginWidget::LoginWidget(LibraryService *service, QWidget *parent)
    : QWidget(parent), m_service(service)
{
    auto layout = new QVBoxLayout(this);
    
    // Title
    auto titleLabel = new QLabel("<h3>Library System Login</h3>");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Form
    auto formLayout = new QFormLayout();
    m_usernameEdit = new QLineEdit();
    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    
    formLayout->addRow("Username:", m_usernameEdit);
    formLayout->addRow("Password:", m_passwordEdit);
    layout->addLayout(formLayout);

    // Login Button
    m_loginButton = new QPushButton("Login");
    layout->addWidget(m_loginButton);

    // Error Label
    m_errorLabel = new QLabel();
    m_errorLabel->setStyleSheet("color: red;");
    layout->addWidget(m_errorLabel);

    // Default admin info
    auto hintLabel = new QLabel("<small>Default: admin / admin</small>");
    hintLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(hintLabel);

    layout->addStretch();

    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::attemptLogin);
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginWidget::attemptLogin);
}

void LoginWidget::attemptLogin() {
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        m_errorLabel->setText("Please enter both username and password.");
        return;
    }

    if (!m_service->login(username, password)) {
        m_errorLabel->setText("Invalid credentials.");
    } else {
        m_errorLabel->clear();
        m_usernameEdit->clear();
        m_passwordEdit->clear();
    }
}
