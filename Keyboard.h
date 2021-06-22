#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<iostream>

class TModel
{
private:
    std::string Manufacturer;
    std::string Model;
public:
    TModel();
    ~TModel();
    TModel(
            std::string lManufacturer,
            std::string lModel
            );
    /**
     * @brief setMan устанавливает производителя
     */
    void setManufacturer(const std::string lManufacturer);
    std::string getManufacturer() const;
    /**
     * @brief setModel устанавливает модель
     */
    void setModel(const std::string lModel);
    std::string getModel() const;

    void show();
};

class TKeyboard: public TModel
{
public:
    enum EType{Undef = 0,Membrane, Mechanical, SemiMechanical};
    enum EConstruction{Default = 0, Classic, Ergonomic, Split, Rhombic};
    enum EInterface{Undefined = 0, PS2, USB, Wireless};
//    enum EColorComb{def = 0, White, Black, WB, BR, Custom};
private:
    EType Type;
    EConstruction Construction;
    EInterface Interface;
//    EColorComb ColorComb;
    int KolVo;
    bool DopKl;
    bool Backlighting;
    int Price;
public:
    TKeyboard();
    ~TKeyboard();
    TKeyboard(  TModel lModel,
                EType lType,
                EConstruction lConstruction,
                EInterface lInterface,
//                EColorComb lColorComb,
                int lKolVo,
                bool lDopKl,
                bool lBacklighting,
                int lPrice
                );
    /**
     * @brief setType устанавливает тип
     */
    void setType (const EType lType);
    /**
     * @brief setConstr устанавливает тип конструкции
     */
    void setConstruction (const EConstruction lConstruction);
    /**
     * @brief setInterface устанавливает интерфейс
     */
    void setInterface (const EInterface lInterface);
//    void setColorComb (const EColorComb lColorComb);
    void setKolVo (const int lKolVo);
    void setDopKl (const bool lDopKl);
    /**
     * @brief setBL устанавливает есть ли задняя подсветка
     */
    void setBacklighting (const bool lBacklighting);
    /**
     * @brief setPrice устанавливает цену
     */
    void setPrice (const int lPrice);

    EType getType ();
    EConstruction getConstruction ();
    EInterface getInterface ();
//    EColorComb getColorComb () const;
    /**
     * @brief setKolVo устанавливает кол-во
     */
    int getKolVo ();
    /**
     * @brief setDopKl устанавливает КП
     */
    bool getDopKl ();

    bool getBacklighting ();
    int getPrice() const;


    void show();
};

#endif // KEYBOARD_H
