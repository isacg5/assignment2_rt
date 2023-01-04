#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include <QWidget>

namespace Ui {
class GuiInterface;
}

class GuiInterface : public QWidget
{
    Q_OBJECT

public:
    explicit GuiInterface(QWidget *parent = nullptr);
    ~GuiInterface();

private:
    Ui::GuiInterface *ui;
};

#endif // GUI_INTERFACE_H
