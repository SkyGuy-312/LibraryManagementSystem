#include "DatabaseManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QDir>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
    loadData();
    if (m_users.isEmpty()) {
        createDefaultAdmin();
    }
}

DatabaseManager::~DatabaseManager() {
    saveData();
}

void DatabaseManager::loadData() {
    loadBooks();
    loadUsers();
}

void DatabaseManager::saveData() const {
    saveBooks();
    saveUsers();
}

void DatabaseManager::loadBooks() {
    QFile file(m_booksFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open books file for reading:" << m_booksFile;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray array = doc.array();

    m_books.clear();
    for (const QJsonValue &val : array) {
        m_books.append(Book::fromJson(val.toObject()));
    }
}

void DatabaseManager::saveBooks() const {
    QFile file(m_booksFile);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open books file for writing:" << m_booksFile;
        return;
    }

    QJsonArray array;
    for (const Book &book : m_books) {
        array.append(book.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
}

void DatabaseManager::loadUsers() {
    QFile file(m_usersFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open users file for reading:" << m_usersFile;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray array = doc.array();

    m_users.clear();
    for (const QJsonValue &val : array) {
        User user = User::fromJson(val.toObject());
        m_users.insert(user.username, user);
    }
}

void DatabaseManager::saveUsers() const {
    QFile file(m_usersFile);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open users file for writing:" << m_usersFile;
        return;
    }

    QJsonArray array;
    for (const User &user : m_users.values()) {
        array.append(user.toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
}

void DatabaseManager::createDefaultAdmin() {
    User admin;
    admin.username = "admin";
    admin.password = "admin"; // Weak default password
    admin.role = UserRole::Admin;
    addUser(admin);
    saveUsers();
}

User* DatabaseManager::getUser(const QString &username) {
    if (m_users.contains(username)) {
        return &m_users[username];
    }
    return nullptr;
}

void DatabaseManager::addUser(const User &user) {
    m_users.insert(user.username, user);
}

QList<Book> DatabaseManager::getAllBooks() const {
    return m_books;
}

void DatabaseManager::addBook(const Book &book) {
    m_books.append(book);
}

bool DatabaseManager::removeBook(const QString &barcode) {
    for (int i = 0; i < m_books.size(); ++i) {
        if (m_books[i].barcode == barcode) {
            m_books.removeAt(i);
            return true;
        }
    }
    return false;
}

QList<Book> DatabaseManager::searchBooks(const QString &query, const QStringList &fields) const {
    QList<Book> results;
    if (query.isEmpty()) return m_books;

    for (const Book &book : m_books) {
        bool match = false;
        // If no fields specified, search all
        if (fields.isEmpty() || fields.contains("Title")) {
            if (book.title.contains(query, Qt::CaseInsensitive)) match = true;
        }
        if (!match && (fields.isEmpty() || fields.contains("Author"))) {
            if (book.author.contains(query, Qt::CaseInsensitive)) match = true;
        }
        if (!match && (fields.isEmpty() || fields.contains("Category"))) {
            if (book.category.contains(query, Qt::CaseInsensitive)) match = true;
        }
        
        if (match) {
            results.append(book);
        }
    }
    return results;
}
