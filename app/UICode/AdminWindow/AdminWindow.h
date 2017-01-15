#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "VirtualController.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

    bool setController(VirtualController* vc);
    void setup_view();

private:
    Ui::AdminWindow *ui;
    VirtualController* vc = nullptr;
    
};

#endif // ADMINWINDOW_H
