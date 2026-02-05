#include "AddBookDialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>

AddBookDialog::AddBookDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add New Book");
    
    auto layout = new QVBoxLayout(this);
    auto form = new QFormLayout();

    m_titleEdit = new QLineEdit();
    m_authorEdit = new QLineEdit();
    m_categoryEdit = new QLineEdit();
    m_barcodeEdit = new QLineEdit();

    form->addRow("Title:", m_titleEdit);
    form->addRow("Author:", m_authorEdit);
    form->addRow("Category:", m_categoryEdit);
    form->addRow("Barcode:", m_barcodeEdit);
    layout->addLayout(form);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
}

QString AddBookDialog::title() const { return m_titleEdit->text(); }
QString AddBookDialog::author() const { return m_authorEdit->text(); }
QString AddBookDialog::category() const { return m_categoryEdit->text(); }
QString AddBookDialog::barcode() const { return m_barcodeEdit->text(); }
