#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsView>


namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void renderGameScene();
    void renderNextMinosScene();
    void singleSetopHandle();
    void setRestartGameRecordId(int id);

public:
    /*!
     * @brief 界面的显示模式，选择日间模式还是夜间模式
     * 
     * 本来定义在 MainWindow 类中，但是在包含 mainwindow.h 的时候提示不能递归包含，
     * 所以便只能在这个类中再定义一次。
     * 
     * 后序优化时，计划将这个类提取到 Utility 通用组件模块中。
     */
    enum class Mode {
        DayMode,
        NightMode,
    };
    
private:
    Ui::GameWindow *ui_ptr_;

    QGraphicsView* game_view_ptr_;
    QGraphicsView* next_minos_view_ptr_;

    QGraphicsScene* game_graphic_scene_ptr_;
    QGraphicsScene* next_minos_scene_ptr_;

    size_t board_width_; // 游戏棋盘的宽度
    size_t board_height_; // 游戏棋盘的高度
    size_t down_speed_; // 方块下落的速度
    
    Mode ui_mode_; // 界面显示模式
};

#endif // GAMEWINDOW_H
