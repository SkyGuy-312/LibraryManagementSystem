#ifndef LIBRARYSERVICE_H
#define LIBRARYSERVICE_H

#include <QObject>
#include "DatabaseManager.h"
#include "User.h"

class LibraryService : public QObject {
    Q_OBJECT

public:
    explicit LibraryService(QObject *parent = nullptr);

    // Auth
    bool login(const QString &username, const QString &password);
    void logout();
    User* currentUser() const;
    bool isAdmin() const;

    // Proxy to DB
    QList<Book> getAllBooks() const;
    QList<Book> searchBooks(const QString &query, const QStringList &fields) const;
    void addBook(const QString &title, const QString &author, const QString &category, const QString &barcode);
    bool removeBook(const QString &barcode);

signals:
    void userLoggedIn(User *user);
    void userLoggedOut();
    void booksChanged();

private:
    DatabaseManager *m_db;
    User *m_currentUser = nullptr;
};

#endif // LIBRARYSERVICE_H
