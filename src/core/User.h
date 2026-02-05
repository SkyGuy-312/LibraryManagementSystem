#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

enum class UserRole {
    Admin,
    User
};

struct User {
    QString username;
    QString password; // In a real app, this should be hashed
    UserRole role;

    // Serialization helper
    QJsonObject toJson() const {
        return QJsonObject{
            {"username", username},
            {"password", password},
            {"role", role == UserRole::Admin ? "admin" : "user"}
        };
    }

    // Deserialization helper
    static User fromJson(const QJsonObject &json) {
        QString roleStr = json["role"].toString();
        UserRole r = (roleStr == "admin") ? UserRole::Admin : UserRole::User;
        
        return User{
            json["username"].toString(),
            json["password"].toString(),
            r
        };
    }
};

#endif // USER_H
