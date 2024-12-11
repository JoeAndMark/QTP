#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewindow.h"
#include "settingwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updatePaletteColor(QWidget* widget, const QPalette& palette);

public:
    /*!
     * @brief UI 界面的显示模式，日间模式或夜间模式
     */
    enum class Mode {
        DayMode,
        NightMode,
    };

private:
    Ui::MainWindow *ui_ptr_;

    Mode ui_mode_;

    GameWindow* game_window_ptr_;
    SettingWindow* setting_window_ptr_;
};
#endif // MAINWINDOW_H
