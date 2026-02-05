#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QLineEdit>

class AddBookDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);

    QString title() const;
    QString author() const;
    QString category() const;
    QString barcode() const;

private:
    QLineEdit *m_titleEdit;
    QLineEdit *m_authorEdit;
    QLineEdit *m_categoryEdit;
    QLineEdit *m_barcodeEdit;
};

#endif // ADDBOOKDIALOG_H
