#ifndef COLOROPTIONBLOCK_H
#define COLOROPTIONBLOCK_H

#include <QWidget>

namespace Ui {
    class ColorOptionBlock;
}

class ColorOptionBlock : public QWidget {
    Q_OBJECT

public:
    explicit ColorOptionBlock(QWidget *parent = nullptr);
    ~ColorOptionBlock();

    void setText(QString text);

    QString colorName() const;
    void setColorFromDialog();
    void setColor(QColor color);

    QColor color() const;

private:
    Ui::ColorOptionBlock *ui_ptr_;

    QColor color_;
};

#endif // COLOROPTIONBLOCK_H
