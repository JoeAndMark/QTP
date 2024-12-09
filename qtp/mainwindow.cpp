#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

#include <QMessageBox>
#include <QDebug>


/*!
 * @brief 主界面的构造函数
 *
 * 对必要属性进行初始化，设置标题、图标等信息，连接按键的信号与槽。
 *
 * @param parent: 父控件的指针，用于构建对象树
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_ptr_(new Ui::MainWindow)
    , ui_mode_(Mode::DayMode)
    , game_window_ptr_(nullptr) {
        ui_ptr_->setupUi(this);

        setWindowTitle("QTP");
        setFixedSize(800, 1000);

        ui_ptr_->introduce_button->setIcon(QIcon(":/resources/introduce_icon.png"));
        ui_ptr_->introduce_button->setIconSize(QSize(60, 60));

        ui_ptr_->rank_button->setIcon(QIcon(":/resources/rank_icon.png"));
        ui_ptr_->rank_button->setIconSize(QSize(60, 60));

        ui_ptr_->switch_mode_button->setIcon(QIcon(":/resources/moon_icon.png"));
        ui_ptr_->switch_mode_button->setIconSize(QSize(60, 60));

        game_window_ptr_ = new GameWindow(nullptr); // 创建游戏界面，但不将其绑定到当前界面的对象树上

        connect(ui_ptr_->introduce_button, &QPushButton::clicked, [=]() {
            qDebug() << "用户点击简介按键";
            QMessageBox message_box;
            message_box.setWindowTitle("简介");
            message_box.setText("这是俄罗斯方块");
            message_box.setFont(QFont("楷体", 16));
            message_box.setStandardButtons(QMessageBox::Ok);
            message_box.exec();
        });

        connect(ui_ptr_->switch_mode_button, &QPushButton::clicked, [this]() {
            qDebug() << "用户点击切换模式按键";
            // ui_mode_ = (ui_mode_ == Mode::DayMode) ? Mode::NigthMode : Mode::DayMode;

            if (Mode::DayMode == ui_mode_) {
                qDebug() << "用户从日间模式切换到夜间模式";
                ui_mode_ = Mode::NightMode;
            } else {
                qDebug() << "用户从夜间模式切换到日间模式";
                ui_mode_ = Mode::DayMode;
            }

            QPalette palette = this->palette();
            QColor window_color, text_color;

            if (Mode::NightMode == ui_mode_) {
                window_color = QColor("#2E2E30");
                text_color = Qt::white;
            } else {
                window_color = QColor("#FFFFFF");
                text_color = Qt::black;
            }

            palette.setColor(QPalette::Window, window_color);
            palette.setColor(QPalette::WindowText, text_color);

            updatePaletteColor(this, palette);
        });

        connect(ui_ptr_->start_button, &QPushButton::clicked, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击开始游戏按钮";

            game_window_ptr_->move(pos());
            game_window_ptr_->show();
            hide();

        });

        connect(ui_ptr_->continue_button, &QPushButton::clicked, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击继续游戏按钮";
        });

        connect(ui_ptr_->setting_button, &QPushButton::clicked, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击设置按钮";
        });

        connect(ui_ptr_->rank_button, &QPushButton::clicked, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击排名按钮";
        });

        connect(ui_ptr_->exit_button, &QPushButton::clicked, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击退出按钮";
        });
    }


/*!
 * @brief 主界面的析构函数
 *
 * 释放构造的主界面 UI，手动释放堆上的对象内存。
 *
 */
MainWindow::~MainWindow() {
    delete ui_ptr_;
}


/*!
 * @brief 更新界面的颜色，用于切换日间和夜晚模式时
 *
 * 用递归的方式遍历整颗对象树，将每个空间的颜色都进行设置。
 * 递归的效率不高，下一步优化将采用迭代的方式进行遍历。
 *
 * @param widget_ptr: 父控件
 * @param palette: 将要设置的调色盘配置
 * @return 无返回值
 */
void MainWindow::updatePaletteColor(QWidget* widget_ptr, const QPalette& palette) {
    widget_ptr->setPalette(palette);

    const QObjectList& child_widget_list = widget_ptr->children();

    for (auto* object: child_widget_list) {
        QWidget* child_widget = qobject_cast<QWidget*>(object);

        if (child_widget) {
            updatePaletteColor(child_widget, palette);
        }
    }
}
