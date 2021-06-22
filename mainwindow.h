#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>
#include <QMainWindow>
#include <QTranslator>
#include "Keyboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow констуктор окна
     * @param parent виджет родитель
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int ElemAm = 0;

    /**
     * @brief setlang устанавливает активный язык
     * @param locale язык
     */
    void setlang(QString locale);
    /**
     * @brief switchLanguage переключает язык при выборе из меню
     */
    void switchLanguage();
    /**
     * @brief createLanguageMenu создает менб языков
     */
    void createLanguageMenu();
    /**
     * @brief saveSettings сохраняет настройки интерфйса
     * @param locale язык
     * @param pos позиция окна
     * @param dim размеры окна
     */
    void saveSettings(QString locale, QPoint pos, QSize dim);
    /**
     * @brief loadSettings загржает настройки
     */
    void loadSettings();
    /**
     * @brief CreateHeader
     */
    void CreateHeader();
    /**
     * @brief DelElmAtLine
     * @param numOfEl
     */
    void DelElmAtLine(int numOfEl);
    /**
     * @brief EditElmAtLine
     * @param numOfEl
     */
    void EditElmAtLine(int numOfEl);
public slots:
    /**
     * @brief contextMenuEvent обработчик вызова контекстного меню
     * @param event контекстное меню
     */
    void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void on_pushExit_clicked();
    /**
     * @brief on_actionOpen_triggered действие "Открыть"
     */
    void on_actionOpen_triggered();
    /**
     * @brief on_actionAdd_triggered действие "Добавить"
     */
    void on_actionAdd_triggered();
    /**
     * @brief on_actionEdit_triggered действие "Редактровать"
     */
    void on_actionEdit_triggered();
    /**
     * @brief on_actionDelete_triggered действие "Удалить"
     */
    void on_actionDelete_triggered();
    /**
     * @brief on_actionClose_triggered действие "Закрыть"
     */
    void on_actionClose_triggered();
    /**
     * @brief on_actionSave_triggered действие "Сохранить"
     */
    void on_actionSave_triggered();
    /**
     * @brief on_actionInfo_triggered действие "Инфо"
     */
    void on_actionInfo_triggered();
    /**
     * @brief on_pushSave_clicked действие "Сохранить"
     */
    void on_pushSave_clicked();
    /**
     * @brief on_pushClose_clicked действие "Закрыть"
     */
    void on_pushClose_clicked();
    /**
     * @brief on_lineEdit_editingFinished действие "Редактировать"
     */
    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;

    enum Colomn
    {
        Man = 0,
        Mod,
        Type,
        Constr,
        Interface,
//        ColComb,
        Kol,
        Dop,
        BL,
        Pr,
        ID
    };

    QString File;
    std::string FN;

    bool Op;

    const int amount = 9;

    struct KBd;

    typedef struct KBd *PonSt;

    PonSt KBdSt, Last;

    struct KBd
    {
        TKeyboard Element;
        PonSt next, prev;
        int ID;
    };

    void ReadFromFile(std::string, PonSt);
    void NewRow(PonSt, int, bool New = true);
    void DeleteRow(int);

    void EnabledButtons(bool);
    bool Check();

    /**
     * @brief qtLanguageTranslator
     */
    QTranslator qtLanguageTranslator;
    /**
     * @brief qmPath
     */
    QString qmPath;
    /**
     * @brief languageActionGroup
     */
    QActionGroup *languageActionGroup; //объединение в группы
    /**
     * @brief active_lang - текйщая локаль
     */
    QString active_lang;
};
#endif // MAINWINDOW_H
