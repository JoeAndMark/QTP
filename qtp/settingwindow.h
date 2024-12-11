#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QVector>
#include "coloroptionblock.h"
#include "keyoptionblock.h"

namespace Ui {
    class SettingWindow;
}

class SettingWindow : public QWidget {
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

signals:
    void settingWindowBack();

private:
    void init();
    void setNumFromDatabase();
    void setNumFromDefault();
    void saveSettingToDatabase();

    bool keyRepetition();

    void disableMouseClick(QWidget* widget_ptr);
    void enableMouseClick(QWidget* widget_ptr);

    void addNewProfile(bool is_required);

private:
    Ui::SettingWindow *ui_ptr_;

    QVector<ColorOptionBlock*> color_option_block_vector_;
    QVector<KeyOptionBlock*> key_option_block_vector_;

};

#endif // SETTINGWINDOW_H
