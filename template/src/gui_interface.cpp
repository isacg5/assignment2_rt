#include "gui_interface.h"
#include "ui_gui_interface.h"

GuiInterface::GuiInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiInterface)
{
    ui->setupUi(this);
}

GuiInterface::~GuiInterface()
{
    delete ui;
}
