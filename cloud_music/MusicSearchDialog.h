#ifndef MUSICSEARCHDIALOG_H
#define MUSICSEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class MusicSearchDialog;
}

class MusicSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MusicSearchDialog(QWidget *parent = nullptr);
    ~MusicSearchDialog();

private:
    Ui::MusicSearchDialog *ui;

private slots:
    void search();
};

#endif // MUSICSEARCHDIALOG_H
