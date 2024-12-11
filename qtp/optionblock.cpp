#include "optionblock.h"
#include "ui_optionblock.h"

#include <QDebug>

OptionBlock::OptionBlock(QWidget *parent) :
    QWidget(parent),
    ui_ptr_(new Ui::OptionBlock) {
        ui_ptr_->setupUi(this);

        void (QSpinBox:: *spinbox_signal_fptr)(int) = &QSpinBox::valueChanged;
        connect(ui_ptr_->spinBox, spinbox_signal_fptr, ui_ptr_->horizontalSlider, &QSlider::setValue);
        connect(ui_ptr_->spinBox, spinbox_signal_fptr, [=]() {
            emit valueChanged();
        });

        connect(ui_ptr_->horizontalSlider, &QSlider::valueChanged, ui_ptr_->spinBox, &QSpinBox::setValue);
    }

OptionBlock::~OptionBlock() {
    delete ui_ptr_;
}


/*!
 * @brief 设置值
 * @param num: 需要设置的值
 */
void OptionBlock::setNum(int num) {
    ui_ptr_->spinBox->setValue(num);
}


/*!
 * @brief 获取设置值
 * @return 返回设置值
 */
inline int OptionBlock::num() const {
    return ui_ptr_->spinBox->value();
}


/*!
 * @brief 设置滑动条的步长
 * @param num: 步长值
 */
void OptionBlock::setStep(int step_value) {
    ui_ptr_->horizontalSlider->setSingleStep(step_value);
    ui_ptr_->horizontalSlider->setPageStep(step_value);
}


/*!
 * @brief 设置标签值
 * @param str: 需要设置成的值
 * @return 无返回值
 */
void OptionBlock::setText(QString str) {
    ui_ptr_->label->setText(str);
}


/*!
 * @brief 获取标签值
 * @return 标签值
 */
inline QString OptionBlock::text() const {
    return ui_ptr_->label->text();
}


/*!
 * @brief 设置控件的上下限
 *
 * 设置滑动条和微调框的上下限
 *
 * @param lower_bound: 下界，即最小值
 * @param upper_bound: 上界，即最大值
 */
void OptionBlock::setLimit(int lower_bound, int upper_bound) {

    if (lower_bound > upper_bound) {
        qCritical() << "设置错误";
        return;
    }

    ui_ptr_->spinBox->setMinimum(lower_bound);
    ui_ptr_->horizontalSlider->setMinimum(lower_bound);
    ui_ptr_->spinBox->setMaximum(upper_bound);
    ui_ptr_->horizontalSlider->setMaximum(upper_bound);
}
