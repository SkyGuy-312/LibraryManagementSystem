#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../core/LibraryService.h"
#include "LoginWidget.h"
#include "DashboardWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showDashboard(User *user);
    void showLogin();

private:
    LibraryService *m_service;
    
    QStackedWidget *m_stack;
    LoginWidget *m_loginWidget;
    DashboardWidget *m_dashboardWidget;
};

#endif // MAINWINDOW_H
