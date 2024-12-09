#include "coloroptionblock.h"
#include "ui_coloroptionblock.h"

ColorOptionBlock::ColorOptionBlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorOptionBlock)
{
    ui->setupUi(this);
}

ColorOptionBlock::~ColorOptionBlock()
{
    delete ui;
}
