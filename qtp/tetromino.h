#ifndef TETROMINO_H
#define TETROMINO_H

#include <QPoint>
#include <QColor>
#include <QVector>

/*!
 * @brief 俄罗斯方块类
 *
 * 俄罗斯方块就叫 tetromino，复数为 tetrominoes
 */
class Tetromino {
public:
    using Status = int;
    using Color = int;

public:
    Tetromino(std::initializer_list<QVector<QPoint>> shape_list, Color color_value);
    ~Tetromino();

    void moveX(int x);
    void moveDown();
    void moveLeft();
    void moveRight();

    void statusForward();
    void statusBackward();
    inline Status status() const;

    inline Color color() const;
    void setColor(Color color_value);

    const QVector<QPoint>& getAllBlocksPosition() const;

public:
    // enum class Color { };

private:
    Color block_color_;
    Status block_status_;
    QPoint block_position_;
    QVector<QVector<QPoint>> block_shape_;
};

extern Tetromino mino_j;
extern Tetromino mino_i;
extern Tetromino mino_l;
extern Tetromino mino_o;
extern Tetromino mino_s;
extern Tetromino mino_z;

#endif // TETROMINO_H
