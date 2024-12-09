#ifndef OPTIONBLOCK_H
#define OPTIONBLOCK_H

#include <QWidget>

namespace Ui {
class OptionBlock;
}

class OptionBlock : public QWidget
{
    Q_OBJECT

public:
    explicit OptionBlock(QWidget *parent = nullptr);
    ~OptionBlock();

private:
    Ui::OptionBlock *ui;
};

#endif // OPTIONBLOCK_H
