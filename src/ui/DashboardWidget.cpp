#include "DashboardWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include "AddBookDialog.h"

DashboardWidget::DashboardWidget(LibraryService *service, QWidget *parent)
    : QWidget(parent), m_service(service)
{
    auto mainLayout = new QVBoxLayout(this);

    // Header
    auto headerLayout = new QHBoxLayout();
    headerLayout->addWidget(new QLabel("<h3>Library Dashboard</h3>"));
    auto logoutBtn = new QPushButton("Logout");
    connect(logoutBtn, &QPushButton::clicked, this, &DashboardWidget::onLogout);
    headerLayout->addStretch();
    headerLayout->addWidget(logoutBtn);
    mainLayout->addLayout(headerLayout);

    // Search Bar
    auto searchLayout = new QHBoxLayout();
    m_searchEdit = new QLineEdit();
    m_searchEdit->setPlaceholderText("Search...");
    
    m_checkTitle = new QCheckBox("Title");
    m_checkAuthor = new QCheckBox("Author");
    m_checkCategory = new QCheckBox("Category");
    m_checkTitle->setChecked(true); // Default

    auto searchBtn = new QPushButton("Search");
    connect(searchBtn, &QPushButton::clicked, this, &DashboardWidget::onSearch);
    connect(m_searchEdit, &QLineEdit::returnPressed, this, &DashboardWidget::onSearch);

    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_checkTitle);
    searchLayout->addWidget(m_checkAuthor);
    searchLayout->addWidget(m_checkCategory);
    searchLayout->addWidget(searchBtn);
    mainLayout->addLayout(searchLayout);

    // Admin Controls (Add/Remove)
    auto adminLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add Book");
    m_removeButton = new QPushButton("Remove Selected");
    
    connect(m_addButton, &QPushButton::clicked, this, &DashboardWidget::onAddBook);
    connect(m_removeButton, &QPushButton::clicked, this, &DashboardWidget::onRemoveBook);

    adminLayout->addWidget(m_addButton);
    adminLayout->addWidget(m_removeButton);
    adminLayout->addStretch();
    mainLayout->addLayout(adminLayout);

    // Table
    m_model = new QStandardItemModel(0, 4, this);
    m_model->setHorizontalHeaderLabels({"Title", "Author", "Category", "Barcode"});
    
    m_bookTable = new QTableView();
    m_bookTable->setModel(m_model);
    m_bookTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_bookTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(m_bookTable);

    // Connections
    connect(m_service, &LibraryService::userLoggedIn, this, &DashboardWidget::refreshView);
    connect(m_service, &LibraryService::booksChanged, this, &DashboardWidget::onSearch); // Refresh list
}

void DashboardWidget::refreshView() {
    updatePermissions();
    onSearch(); // Load initial data
}

void DashboardWidget::updatePermissions() {
    bool isAdmin = m_service->isAdmin();
    m_addButton->setVisible(isAdmin);
    m_removeButton->setVisible(isAdmin);
}

void DashboardWidget::onSearch() {
    QString query = m_searchEdit->text();
    QStringList fields;
    if (m_checkTitle->isChecked()) fields << "Title";
    if (m_checkAuthor->isChecked()) fields << "Author";
    if (m_checkCategory->isChecked()) fields << "Category";

    loadBooks(m_service->searchBooks(query, fields));
}

void DashboardWidget::loadBooks(const QList<Book> &books) {
    m_model->removeRows(0, m_model->rowCount());
    for (const Book &book : books) {
        QList<QStandardItem*> row;
        row << new QStandardItem(book.title);
        row << new QStandardItem(book.author);
        row << new QStandardItem(book.category);
        row << new QStandardItem(book.barcode);
        // Make ready only
        for (auto item : row) item->setEditable(false);
        m_model->appendRow(row);
    }
}

void DashboardWidget::onAddBook() {
    AddBookDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_service->addBook(dialog.title(), dialog.author(), dialog.category(), dialog.barcode());
    }
}

void DashboardWidget::onRemoveBook() {
    auto selection = m_bookTable->selectionModel()->selectedRows();
    if (selection.isEmpty()) return;

    int row = selection.first().row();
    QString barcode = m_model->item(row, 3)->text(); // Barcode is column 3

    if (QMessageBox::question(this, "Confirm Delete", "Delete book with barcode " + barcode + "?") == QMessageBox::Yes) {
        m_service->removeBook(barcode);
    }
}

void DashboardWidget::onLogout() {
    m_service->logout();
    emit logoutRequested();
}
