#include "keyoptionblock.h"
#include "ui_keyoptionblock.h"

KeyOptionBlock::KeyOptionBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyOptionBlock)
{
    ui->setupUi(this);
}

KeyOptionBlock::~KeyOptionBlock()
{
    delete ui;
}
