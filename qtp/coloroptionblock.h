#ifndef COLOROPTIONBLOCK_H
#define COLOROPTIONBLOCK_H

#include <QWidget>

namespace Ui {
class ColorOptionBlock;
}

class ColorOptionBlock : public QWidget
{
    Q_OBJECT

public:
    explicit ColorOptionBlock(QWidget *parent = nullptr);
    ~ColorOptionBlock();

private:
    Ui::ColorOptionBlock *ui;
};

#endif // COLOROPTIONBLOCK_H
