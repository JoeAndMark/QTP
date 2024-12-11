#include "coloroptionblock.h"
#include "ui_coloroptionblock.h"

#include <QColorDialog>

ColorOptionBlock::ColorOptionBlock(QWidget *parent)
    : QWidget(parent)
    , ui_ptr_(new Ui::ColorOptionBlock)
    , color_(Qt::white) {
        ui_ptr_->setupUi(this);
    }

ColorOptionBlock::~ColorOptionBlock() {
    delete ui_ptr_;
}

void ColorOptionBlock::setText(QString text) {
    ui_ptr_->selectColorBtn->setText(text);
}

QString ColorOptionBlock::colorName() const {
    return color_.name(QColor::HexRgb);
}

void ColorOptionBlock::setColorFromDialog() {

    QColor color = QColorDialog::getColor(Qt::white, this, tr("选择一个颜色"));

    // color_ = color;
    // QPalette palette;
    //
    // if (color.isValid()) {
    //
    //     // 将 RGB 值显示在文本框中
    //     ui_ptr_->colorLineEdit->setText(colorName());
    //
    //     // 根据颜色深浅调节文本颜色
    //     if (color.lightness() < 127) {
    //         palette.setColor(QPalette::Text, Qt::white);
    //     } else {
    //         palette.setColor(QPalette::Text, Qt::black);
    //     }
    //
    //     // 调整文本框背景颜色为用户选择的颜色
    //     ui_ptr_->colorLineEdit->setStyleSheet(
    //         QString("background-color: rgb(%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue())
    //     );
    //
    //     ui_ptr_->colorLineEdit->setPalette(palette);
    // }

    setColor(color);
}

void ColorOptionBlock::setColor(QColor color) {
    color_ = color;
    QPalette palette;

    if (color.isValid()) {

        // 将 RGB 值显示在文本框中
        ui_ptr_->colorLineEdit->setText(colorName());

        // 根据颜色深浅调节文本颜色
        if (color.lightness() < 127) {
            palette.setColor(QPalette::Text, Qt::white);
        } else {
            palette.setColor(QPalette::Text, Qt::black);
        }

        // 调整文本框背景颜色为用户选择的颜色
        ui_ptr_->colorLineEdit->setStyleSheet(QString(
            "background-color: rgb(%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue()
        ));

        ui_ptr_->colorLineEdit->setPalette(palette);
    }
}

QColor ColorOptionBlock::color() const {
    return color_;
}
