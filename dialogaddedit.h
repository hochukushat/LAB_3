#ifndef DIALOGADDEDIT_H
#define DIALOGADDEDIT_H

#include <QDialog>
#include "Keyboard.h"

namespace Ui {
class DialogAddEdit;
}

class DialogAddEdit : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DialogAddEdit конструктор диалога
     * @param parent
     */
    explicit DialogAddEdit(QWidget *parent = nullptr);
    ~DialogAddEdit();
    /**
     * @brief setMan устанавливает производителя
     */
    void setMan(const std::string);
    std::string getMan() const;
    /**
     * @brief setModel устанавливает модель
     */
    void setModel(const std::string);
    std::string getModel() const;
    /**
     * @brief setType устанавливает тип
     */
    void setType(const TKeyboard::EType);
    TKeyboard::EType getType() const;
    /**
     * @brief setConstr устанавливает тип конструкции
     */
    void setConstr(const TKeyboard::EConstruction);
    TKeyboard::EConstruction getConstr() const;
    /**
     * @brief setInterface устанавливает интерфейс
     */
    void setInterface(const TKeyboard::EInterface);
    TKeyboard::EInterface getInterface() const;

    /**
     * @brief setKolVo устанавливает кол-во
     */
    void setKolVo(const int);
    int getKolVo() const;
    /**
     * @brief setDopKl устанавливает КП
     */
    void setDopKl(const bool);
    bool getDopKl() const;
    /**
     * @brief setBL устанавливает БЛ
     */
    void setBL(const bool);
    bool getBL() const;
    /**
     * @brief setPrice устанавливает цену
     */
    void setPrice(const int);
    int getPrice() const;

    void setLabel(bool);

private:
    Ui::DialogAddEdit *ui;



};

#endif // DIALOGADDEDIT_H
