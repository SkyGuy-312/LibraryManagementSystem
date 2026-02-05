#include "LibraryService.h"
#include <QDebug>

LibraryService::LibraryService(QObject *parent) : QObject(parent) {
    m_db = new DatabaseManager(this);
}

bool LibraryService::login(const QString &username, const QString &password) {
    User *user = m_db->getUser(username);
    if (user && user->password == password) {
        m_currentUser = user;
        emit userLoggedIn(m_currentUser);
        return true;
    }
    return false;
}

void LibraryService::logout() {
    m_currentUser = nullptr;
    emit userLoggedOut();
}

User* LibraryService::currentUser() const {
    return m_currentUser;
}

bool LibraryService::isAdmin() const {
    return m_currentUser && m_currentUser->role == UserRole::Admin;
}

QList<Book> LibraryService::getAllBooks() const {
    return m_db->getAllBooks();
}

QList<Book> LibraryService::searchBooks(const QString &query, const QStringList &fields) const {
    return m_db->searchBooks(query, fields);
}

void LibraryService::addBook(const QString &title, const QString &author, const QString &category, const QString &barcode) {
    if (!isAdmin()) return; // Security check

    Book book{title, author, category, barcode};
    m_db->addBook(book);
    m_db->saveData();
    emit booksChanged();
}

bool LibraryService::removeBook(const QString &barcode) {
    if (!isAdmin()) return false;

    if (m_db->removeBook(barcode)) {
        m_db->saveData();
        emit booksChanged();
        return true;
    }
    return false;
}
