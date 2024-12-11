#ifndef OPTIONBLOCK_H
#define OPTIONBLOCK_H

#include <QWidget>

namespace Ui {
    class OptionBlock;
}

class OptionBlock : public QWidget {
    Q_OBJECT

public:
    explicit OptionBlock(QWidget *parent = nullptr);
    ~OptionBlock();

    void setText(QString str);
    inline QString text() const;

    void setLimit(int lower_bound, int upper_bound);

    void setStep(int step_value);

    void setNum(int num);
    inline int num() const;

signals:
    void valueChanged();

private:
    Ui::OptionBlock *ui_ptr_;
};

#endif // OPTIONBLOCK_H
