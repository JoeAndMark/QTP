#include "optionblock.h"
#include "ui_optionblock.h"

OptionBlock::OptionBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionBlock)
{
    ui->setupUi(this);
}

OptionBlock::~OptionBlock()
{
    delete ui;
}
