#ifndef KEYOPTIONBLOCK_H
#define KEYOPTIONBLOCK_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
    class KeyOptionBlock;
}

class KeyOptionBlock : public QWidget {
    Q_OBJECT

public:
    explicit KeyOptionBlock(QWidget *parent = nullptr);
    ~KeyOptionBlock();

    void setLabel(QString label);
    void setButtonString(QString str);

    void setKey(Qt::Key key);
    Qt::Key key() const;

signals:
    void disableMouseControl();
    void enableMouseControl();

private:
    void onButtonClicked();
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::KeyOptionBlock *ui_ptr_;

    bool is_listening_enabled_;
    Qt::Key key_;
};

#endif // KEYOPTIONBLOCK_H
