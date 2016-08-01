#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class QLabel;

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

    QLabel *getLabel();

private slots:
    void on_Form_destroyed(QObject *arg1);

private:
    Ui::Form *ui;
};

#endif // FORM_H
