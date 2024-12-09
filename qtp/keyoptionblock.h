#ifndef KEYOPTIONBLOCK_H
#define KEYOPTIONBLOCK_H

#include <QWidget>

namespace Ui {
class KeyOptionBlock;
}

class KeyOptionBlock : public QWidget
{
    Q_OBJECT

public:
    explicit KeyOptionBlock(QWidget *parent = nullptr);
    ~KeyOptionBlock();

private:
    Ui::KeyOptionBlock *ui;
};

#endif // KEYOPTIONBLOCK_H
