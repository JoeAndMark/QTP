#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QDebug>
#include <QGraphicsRectItem>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , ui_ptr_(new Ui::GameWindow)
    , game_view_ptr_(nullptr)
    , next_minos_view_ptr_(nullptr)
    , game_graphic_scene_ptr_(new QGraphicsScene(this))
    , next_minos_scene_ptr_(new QGraphicsScene(this))
    , board_width_(10)
    , board_height_(20)
    , down_speed_(1)
    , ui_mode_(Mode::DayMode) {

        qDebug() << "开始构造游戏界面，并进行配置";
        ui_ptr_->setupUi(this);
        setFixedSize(800, 1000);
        setWindowTitle("游戏界面");

        game_view_ptr_ = ui_ptr_->board_view;
        next_minos_view_ptr_ = ui_ptr_->preview_view;

//        game_graphic_scene_ptr_ = new QGraphicsScene(this);
        game_view_ptr_->setScene(game_graphic_scene_ptr_);
        qDebug() << "设置成功1";

//        next_minos_scene_ptr_ = new QGraphicsScene(this);
        next_minos_view_ptr_->setScene(next_minos_scene_ptr_);
        qDebug() << "设置成功2";

        connect(ui_ptr_->music_button, &QPushButton::clicked, this, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户点击播放音乐按钮";
        });

        connect(ui_ptr_->music_slider, &QSlider::valueChanged, [this]() {
            Q_UNUSED(this);
            qDebug() << "用户更改音乐声音大小";
        });

        connect(ui_ptr_->start_restart_button, &QPushButton::clicked, this, [this]() {
            Q_UNUSED(this);

            if (this->ui_ptr_->start_restart_button->text() == "开始") {
                qDebug() << "用户点击开始游戏";
                this->ui_ptr_->start_restart_button->setText("重新开始");
            } else {
                qDebug() << "用户点击重新开始游戏";
                this->ui_ptr_->start_restart_button->setText("开始");
            }

        });

        connect(ui_ptr_->back_button, &QPushButton::clicked, this, [this]() {
            Q_UNUSED(this);

            qDebug() << "用户点击返回按钮";
        });

        renderGameScene();
        qDebug() << game_graphic_scene_ptr_->items().count();
        renderNextMinosScene();
    }

GameWindow::~GameWindow() {
    delete ui_ptr_;
}

/*!
 * @brief 绘制棋盘网格区域
 *
 * 棋盘可以看多若干个空正方形组成，画棋盘网格线本质上就是画若干个透明的正方形。
 *
 */
void GameWindow::renderGameScene() {
    qDebug() << "开始渲染游戏棋盘区";

    game_graphic_scene_ptr_->clear();

    // 正方形的大小参数
    const short square_size = 30; // 单位像素
    const short spacing = 1; // 间隔

    // 绘制网格线
    qDebug() << "开始绘制游戏棋盘区网格线";
    for (size_t row = 0; row < board_height_; row++) {

        for (size_t column = 0; column < board_width_; column++) {
            QGraphicsRectItem* square_ptr = new QGraphicsRectItem;

            if (Mode::DayMode == ui_mode_) {
                square_ptr->setPen(QPen(Qt::black));
            } else {
                square_ptr->setPen(QPen(Qt::white));
            }

            /*!
             * 设置方块的位置和尺寸。
             * 由于 game_graphic_scene_ptr_ 对象已经挂载到了 GameWindow 的对象树上，所以可以直接使用相对坐标。
             */
            int x = column * (square_size + spacing);
            int y = row * (square_size + spacing);
            square_ptr->setRect(x, y, square_size, square_size);

            game_graphic_scene_ptr_->addItem(square_ptr);

        }

    }
    qDebug() << "游戏棋盘区网格线结束绘制";

    // 绘制警戒线
    qDebug() << "开始绘制警戒线";
    int warning_line_y = 1 * (square_size + spacing) + square_size; // 警戒线的 Y 坐标

    QGraphicsLineItem* warning_line_ptr = new QGraphicsLineItem(0, warning_line_y, board_width_ * (square_size + spacing), warning_line_y);

    QPen warning_line_pen(Qt::red);
    warning_line_pen.setWidth(3);

    warning_line_ptr->setPen(warning_line_pen);
    game_graphic_scene_ptr_->addItem(warning_line_ptr);
    qDebug() << "结束绘制警戒线";

    qDebug() << game_graphic_scene_ptr_->items().count();;

//    game_graphic_scene_ptr_->update();
//    game_view_ptr_->viewport()->update();
}

void GameWindow::renderNextMinosScene() {
    next_minos_scene_ptr_->clear();

    const short square_size = 30;
    const short spacing = 1;

    // 绘制网格线
    for (int row = 0; row < 5; row++) {

        for (int column = 0; column < 5; column++) {
            QGraphicsRectItem* square_ptr = new QGraphicsRectItem;

            QPen pen;

            if (Mode::DayMode == ui_mode_) {
                pen.setColor(Qt::black);
            } else {
                pen.setColor(Qt::white);
            }

            square_ptr->setPen(pen);

            int x = column * (square_size + spacing);
            int y = row * (square_size + spacing);
            square_ptr->setRect(x, y, square_size, square_size);

            next_minos_scene_ptr_->addItem(square_ptr);
        }

    }
}
