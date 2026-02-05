#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QJsonObject>

struct Book {
    QString title;
    QString author;
    QString category;
    QString barcode; // Unique identifier

    // Serialization helper
    QJsonObject toJson() const {
        return QJsonObject{
            {"title", title},
            {"author", author},
            {"category", category},
            {"barcode", barcode}
        };
    }

    // Deserialization helper
    static Book fromJson(const QJsonObject &json) {
        return Book{
            json["title"].toString(),
            json["author"].toString(),
            json["category"].toString(),
            json["barcode"].toString()
        };
    }
};

#endif // BOOK_H
