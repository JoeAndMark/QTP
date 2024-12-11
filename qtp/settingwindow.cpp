#include "settingwindow.h"
#include "ui_settingwindow.h"

#include <QDesktopWidget>
#include <QFlags>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QInputDialog>

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui_ptr_(new Ui::SettingWindow) {
        ui_ptr_->setupUi(this);
        this->setWindowTitle("设置");
        this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
        this->setFixedSize(800, 1000);

        ui_ptr_->tabWidget->setCurrentIndex(0);
        ui_ptr_->currentUserLabel->setWordWrap(true);
        ui_ptr_->currentUserLabel->setText("当前用户：\n");

        // QDesktopWidget* desktop_ptr = QApplication::desktop();
        // move(desktop_ptr->width() - this->width(), desktop_ptr->width() - this->width());

        // 返回按钮
        connect(ui_ptr_->settingBackBtn, &QPushButton::clicked, this, [=]() {

            if (keyRepetition()) {
                QMessageBox::critical(parent, "错误", "键位设置重复");
                return;
            }

            saveSettingToDatabase();
            ui_ptr_->tryListeningBtn->setText("试听");
            // media_player_->stop();
            emit settingWindowBack();
        });

        // 重置选项按钮
        connect(ui_ptr_->resetBtn, &QPushButton::clicked, this, [=]() {
            setNumFromDefault();
        });

        // 创建新用户下拉框
        connect(ui_ptr_->selectUserComboBox, &QComboBox::currentTextChanged, [=]() {
            ui_ptr_->currentUserLabel->setText("当前用户：\n" + ui_ptr_->selectUserComboBox->currentText());
        });

        // 清除用户存档按钮
        connect(ui_ptr_->clearUserBtn, &QPushButton::clicked, this, [=]() {
            return;
        });

        connect(ui_ptr_->chooseMediaFileBtn, &QPushButton::clicked, [&]() {
            QString file_path =  QFileDialog::getOpenFileName(nullptr, "选择文件", "", "音频文件（*.mp3, *.wav）");

            if (!file_path.isEmpty()) {
                ui_ptr_->mediaLineEdit->setText(file_path);
                // media_player_->setMedia(QUrl::fromLocakFile(file_path);
            }

        });

        connect(ui_ptr_->tryListeningBtn, &QPushButton::clicked, [&]() {
            return;
        });

        connect(ui_ptr_->mediaOptionBlock, &OptionBlock::valueChanged, [=]() {
            return;
        });

        connect(ui_ptr_->newUserBtn, &QPushButton::clicked, [&]() {
            addNewProfile(false);
        });

        //

        init();
        setNumFromDefault();
    }

SettingWindow::~SettingWindow() {
    delete ui_ptr_;
}

void SettingWindow::init() {
    ui_ptr_->widthOptionBlock->setText("棋盘宽度");
    ui_ptr_->widthOptionBlock->setLimit(10, 5);
    ui_ptr_->widthOptionBlock->setStep(1);

    ui_ptr_->heightOptionBlock->setText("棋盘高度");
    ui_ptr_->heightOptionBlock->setLimit(20, 10);
    ui_ptr_->heightOptionBlock->setStep(1);

    ui_ptr_->fallingOptionBlock->setText("游戏速度");
    ui_ptr_->fallingOptionBlock->setLimit(160, 20);
    ui_ptr_->fallingOptionBlock->setStep(10);

    ui_ptr_->mediaOptionBlock->setText("游戏音乐");
    ui_ptr_->mediaOptionBlock->setLimit(100, 0);
    ui_ptr_->mediaOptionBlock->setStep(10);
    ui_ptr_->mediaLineEdit->setReadOnly(true);

    color_option_block_vector_.append(ui_ptr_->blockL_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockO_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockJ_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockI_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockT_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockS_ColorOptionBlock);
    color_option_block_vector_.append(ui_ptr_->blockZ_ColorOptionBlock);

    const QString block_name[7] = {"L", "O", "J", "I", "T", "S", "Z"};

    size_t count = 0;

    for (auto item : color_option_block_vector_) {
        item->setText(QString("方块%1").arg(block_name[count++]));
    }

    key_option_block_vector_.append(ui_ptr_->left_KeyOptionBlock);
    key_option_block_vector_.append(ui_ptr_->right_KeyOptionBlock);
    key_option_block_vector_.append(ui_ptr_->down_KeyOptionBlock);
    key_option_block_vector_.append(ui_ptr_->spin_KeyOptionBlock);
    key_option_block_vector_.append(ui_ptr_->pause_KeyOptionBlock);

    const QString key_name[5] = {"左移", "右移", "下降", "旋转", "暂停"};

    count = 0;

    for (auto item : key_option_block_vector_) {

        connect(item, &KeyOptionBlock::disableMouseControl, this, [=]() {
            disableMouseClick(this);
        });

        connect(item, &KeyOptionBlock::enableMouseControl, this, [=]() {
            enableMouseClick(this);
        });

        item->setLabel(QString(key_name[count++]));
    }
}

void SettingWindow::disableMouseClick(QWidget *widget_ptr) {
    widget_ptr->setMouseTracking(true);
    widget_ptr->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    QList<QWidget*> children = widget_ptr->findChildren<QWidget*>();

    for (auto child : children) {
        disableMouseClick(child);
    }
}

void SettingWindow::enableMouseClick(QWidget *widget_ptr) {
    widget_ptr->setMouseTracking(true);
    widget_ptr->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    QList<QWidget*> children = widget_ptr->findChildren<QWidget*>();

    for (auto child : children) {
        enableMouseClick(child);
    }
}

void SettingWindow::setNumFromDefault() {
    ui_ptr_->widthOptionBlock->setNum(0);
    ui_ptr_->heightOptionBlock->setNum(20);
    ui_ptr_->fallingOptionBlock->setNum(100);
    ui_ptr_->mediaOptionBlock->setNum(50);
    ui_ptr_->mediaLineEdit->setText("");

    QColor default_block_color[10] = {
        Qt::white,
        QColor("#3795D9"),//方块1颜色
        QColor("#F0CA2E"),//方块2颜色
        QColor("#88258B"),//方块3颜色
        QColor("#F56816"),//方块4颜色
        QColor("#2A51B6"),//方块5颜色
        QColor("#61B532"),//方块6颜色
        QColor("#BE1D23"),//方块7颜色
        Qt::white,
        Qt::gray//固定方块颜色
    };

    Qt::Key default_key_setting[5] = {
        Qt::Key_Left,
        Qt::Key_Right,
        Qt::Key_Down,
        Qt::Key_Up,
        Qt::Key_Escape
    };

    size_t count = 1;

    for (auto item : color_option_block_vector_) {
        item->setColor(default_block_color[count++]);
    }

    count = 0;

    for (auto item : key_option_block_vector_) {
        item->setKey(default_key_setting[count++]);
    }
}

bool SettingWindow::keyRepetition() {
    QSet<Qt::Key> temp_key_set;

    for (auto item : key_option_block_vector_) {
        temp_key_set.insert(item->key());
    }

    return temp_key_set.size() < 5;
}

void SettingWindow::addNewProfile(bool is_required) {
    QInputDialog input_dialog;
    bool ok;

    QString name;

    while (true) {
        name = input_dialog.getText(this, "新用户", "请输入新用户昵称", QLineEdit::Normal, "admin", &ok);

        if (!ok && !is_required) {
            return;
        }

        if (name.size() >= 10 || name.size() < 1) {
            QMessageBox::critical(this, "错误", "字数限制(<10)!");
            continue;
        }

        // 其余操作

        break;
    }

    // 等待实现用户管理者
}

void SettingWindow::saveSettingToDatabase() {
    return;
}
