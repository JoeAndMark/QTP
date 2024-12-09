#include "tetromino.h"

#include <QPoint>

#define GAME_WIDTH 20


Tetromino mino_j({
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint( 1,  1)},
    {QPoint( 0,  1), QPoint(0, -1), QPoint(0, 0), QPoint( 1, -1)},
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint(-1, -1)},
    {QPoint( 0, -1), QPoint(0,  0), QPoint(0, 1), QPoint(-1,  1)}
}, 3);

Tetromino mino_i({
    {QPoint( 1,  0), QPoint(0,  0), QPoint(-1, 0), QPoint( 2,  0)},
    {QPoint( 0,  1), QPoint(0, -1), QPoint( 0, 0), QPoint( 0, -2)},
    {QPoint(-1,  0), QPoint(1,  0), QPoint( 1, 0), QPoint(-2,  0)},
    {QPoint( 0, -1), QPoint(0,  0), QPoint( 0, 1), QPoint( 0,  2)}
}, 4);

Tetromino mino_l({
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint( 1, -1)},
    {QPoint(-1, -1), QPoint(0, -1), QPoint(0, 0), QPoint( 0,  1)},
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint(-1,  1)},
    {QPoint( 0, -1), QPoint(0,  0), QPoint(0, 1), QPoint( 1,  1)}
}, 1);

Tetromino mino_o({
    {QPoint(-1,  0), QPoint(0, 0), QPoint(-1, 1), QPoint( 0,  1)},
    {QPoint( 1,  1), QPoint(0, 1), QPoint( 0, 0), QPoint( 1,  0)},
    {QPoint( 1, -1), QPoint(0, 0), QPoint( 1, 0), QPoint( 0, -1)},
    {QPoint( 0, -1), QPoint(0, 0), QPoint(-1, 0), QPoint(-1, -1)}
}, 2);

Tetromino mino_s({
    {QPoint( 0, -1), QPoint(0,  0), QPoint(-1, -1), QPoint( 1,  0)},
    {QPoint(-1,  1), QPoint(0, -1), QPoint( 0,  0), QPoint(-1,  0)},
    {QPoint( 1,  1), QPoint(0,  0), QPoint(-1,  0), QPoint( 0,  1)},
    {QPoint( 0,  1), QPoint(0,  0), QPoint( 1,  0), QPoint( 1, -1)}
}, 6);

Tetromino mino_t({
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint( 0,  1)},
    {QPoint( 1,  0), QPoint(0, -1), QPoint(0, 0), QPoint( 0,  1)},
    {QPoint(-1,  0), QPoint(0,  0), QPoint(1, 0), QPoint( 0, -1)},
    {QPoint( 0, -1), QPoint(0,  0), QPoint(0, 1), QPoint(-1,  0)}
}, 5);

Tetromino::Tetromino(std::initializer_list<QVector<QPoint>> shape_list, Color color_value)
    : block_color_(color_value)
    , block_status_(0)
    , block_position_(QPoint(GAME_WIDTH /2 , 2))
    , block_shape_(shape_list) {

    }

Tetromino::~Tetromino() {

}

/*!
 * @brief 沿水平方向（x 轴方向）移动
 * @param x: 移动到的 x 轴坐标
 */
void Tetromino::moveX(int x) {
    block_position_.setX(x);
}

/*!
 * @brief 将俄罗斯方块向下移动
 */
void Tetromino::moveDown() {
    block_position_.setY(block_position_.y() + 1);
}

/*!
 * @brief 将俄罗斯方块向左移动
 */
void Tetromino::moveLeft() {
    block_position_.setX(block_position_.x() - 1);
}

/*!
 * @brief 将俄罗斯方块向右移动
 */
void Tetromino::moveRight() {
    block_position_.setY(block_position_.x() + 1);
}

/*!
 * @brief 切换到下一个状态
 */
void Tetromino::statusForward() {
    if (status() < 3) {
        block_status_++;
    } else {
        block_status_ = 0;
    }
}

/*!
 * @brief 切换回上一个状态
 */
void Tetromino::statusBackward() {
    if (status() > 0) {
        block_status_--;
    } else {
        block_status_ = 3;
    }
}

inline Tetromino::Status Tetromino::status() const {
    return block_status_;
}

/*!
 * @brief 获取俄罗斯方块的颜色
 * @return 返回方块的颜色
 */
inline Tetromino::Color Tetromino::color() const {
    return block_color_;
}

/*!
 * @brief 设置俄罗斯方块的颜色
 * @param color_value: 需要被设置的俄罗斯方块的值
 * @return 无返回值
 */
void Tetromino::setColor(Tetromino::Color color_value) {
    block_color_ = color_value;
}

/*!
 * @brief 获取当前状态下的俄罗斯方块的形状（坐标）
 * @return 返回当前状态下的俄罗斯方块的坐标
 */
const QVector<QPoint>& Tetromino::getAllBlocksPosition() const {
    return block_shape_[block_status_];
}
