#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Library Management System");
    resize(800, 600);

    m_service = new LibraryService(this);

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    m_loginWidget = new LoginWidget(m_service, this);
    m_dashboardWidget = new DashboardWidget(m_service, this);

    m_stack->addWidget(m_loginWidget);
    m_stack->addWidget(m_dashboardWidget);

    m_stack->setCurrentWidget(m_loginWidget);

    // Navigation connections
    connect(m_service, &LibraryService::userLoggedIn, this, &MainWindow::showDashboard);
    connect(m_dashboardWidget, &DashboardWidget::logoutRequested, this, &MainWindow::showLogin);
}

void MainWindow::showDashboard(User *user) {
    qDebug() << "Logged in as:" << user->username << "Role:" << (int)user->role;
    m_stack->setCurrentWidget(m_dashboardWidget);
}

void MainWindow::showLogin() {
    m_stack->setCurrentWidget(m_loginWidget);
}
