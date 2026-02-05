#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include "../core/LibraryService.h"

class DashboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit DashboardWidget(LibraryService *service, QWidget *parent = nullptr);
    void refreshView();

private slots:
    void onSearch();
    void onAddBook();
    void onRemoveBook();
    void onLogout();

signals:
    void logoutRequested();

private:
    LibraryService *m_service;
    
    // Search
    QLineEdit *m_searchEdit;
    QCheckBox *m_checkTitle;
    QCheckBox *m_checkAuthor;
    QCheckBox *m_checkCategory;
    
    // Table
    QTableView *m_bookTable;
    QStandardItemModel *m_model;

    // Admin Controls
    QPushButton *m_addButton;
    QPushButton *m_removeButton;

    void updatePermissions();
    void loadBooks(const QList<Book> &books);
};

#endif // DASHBOARDWIDGET_H
