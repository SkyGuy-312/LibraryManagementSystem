#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include "Book.h"
#include "User.h"

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    // loads data from JSON files
    void loadData();
    // saves data to JSON files
    void saveData() const;

    // User management
    User* getUser(const QString &username);
    QList<User> getAllUsers() const;
    void addUser(const User &user);

    // Book management
    QList<Book> getAllBooks() const;
    void addBook(const Book &book);
    bool removeBook(const QString &barcode);
    QList<Book> searchBooks(const QString &query, const QStringList &fields) const;

private:
    QList<Book> m_books;
    QMap<QString, User> m_users; // key: username

    QString m_booksFile = "books.json";
    QString m_usersFile = "users.json";

    void loadBooks();
    void loadUsers();
    void saveBooks() const;
    void saveUsers() const;
    void createDefaultAdmin();
};

#endif // DATABASEMANAGER_H
