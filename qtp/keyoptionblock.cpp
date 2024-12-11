#include "keyoptionblock.h"
#include "ui_keyoptionblock.h"

#include <QKeyEvent>

KeyOptionBlock::KeyOptionBlock(QWidget *parent)
    : QWidget(parent)
    , ui_ptr_(new Ui::KeyOptionBlock)
    , is_listening_enabled_(false)
    , key_(Qt::Key::Key_Space) {
        ui_ptr_->setupUi(this);
        ui_ptr_->keyLineEdit->setReadOnly(true);
    }

KeyOptionBlock::~KeyOptionBlock() {
    delete ui_ptr_;
}

void KeyOptionBlock::setLabel(QString label) {
    ui_ptr_->keyLabel->setText(label);
}

void KeyOptionBlock::setButtonString(QString str) {
    ui_ptr_->resetBtn->setText(str);
}

void KeyOptionBlock::setKey(Qt::Key key) {
    key_ = key;
    ui_ptr_->keyLineEdit->setText(QKeySequence(key).toString());
}

Qt::Key KeyOptionBlock::key() const {
    return key_;
}

void KeyOptionBlock::onButtonClicked() {

    // 设置为正在监听键盘事件
    is_listening_enabled_ = true;
    this->grabKeyboard();

    // 设置文本框获得焦点，以便监听键盘事件
    ui_ptr_->keyLineEdit->setFocus();
    ui_ptr_->resetBtn->setText("等待按下");

    // 禁用按钮，防止重复按下
    ui_ptr_->resetBtn->setEnabled(false);
    emit disableMouseControl();
}

void KeyOptionBlock::keyPressEvent(QKeyEvent* event) {

    if (is_listening_enabled_) {
        QString key_name = QKeySequence(event->key()).toString();
        ui_ptr_->keyLineEdit->setText(key_name);
    } else {
        QWidget::keyPressEvent(event);
    }

}
