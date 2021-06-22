#include "keyboard.h"
#include<iostream>
#include <iostream>

using namespace std;

TModel::TModel():
    Manufacturer(""),
    Model("")
{

}

TModel::~TModel()
{

}

TModel::TModel(std::string lManufacturer, std::string lModel):
    Manufacturer(lManufacturer),
    Model(lModel)
{

}

void TModel::setManufacturer(const string lManufacturer)
{
    Manufacturer=lManufacturer;
}

string TModel::getManufacturer() const
{
    return Manufacturer;
}

void TModel::setModel(const string lModel)
{
    Model=lModel;
}

string TModel::getModel() const
{
    return Model;
}

void TModel::show()
{
    cout<<"Manufacturer: "<<Manufacturer<<"\n"
        <<"Model: "<<Model<<"\n";
}


TKeyboard::TKeyboard():
    TModel ({"",""}),
    Type(Undef),
    Construction(Default),
    Interface(Undefined),
    KolVo(0),
    DopKl(0),
    Backlighting(0)
{

}

TKeyboard::~TKeyboard()
{

}

TKeyboard::TKeyboard(TModel lModel
                     , TKeyboard::EType lType
                     , TKeyboard::EConstruction lConstruction
                     , TKeyboard::EInterface lInterface
//                     , TKeyboard::EColorComb lColorComb
                     , int lKolVo
                     , bool lDopKl
                     , bool lBacklighting
                     , int lPrice
                     ):
    TModel (lModel),
    Type(lType),
    Construction(lConstruction),
    Interface(lInterface),
//    ColorComb(lColorComb),
    KolVo(lKolVo),
    DopKl(lDopKl),
    Backlighting(lBacklighting),
    Price(lPrice)
{

}

void TKeyboard::setType(const TKeyboard::EType lType)
{
    Type=lType;
}

void TKeyboard::setConstruction(const TKeyboard::EConstruction lConstruction)
{
    Construction=lConstruction;
}

void TKeyboard::setInterface(const TKeyboard::EInterface lInterface)
{
    Interface=lInterface;
}

//void TKeyboard::setColorComb(const TKeyboard::EColorComb lColorComb)
//{
//    ColorComb = lColorComb;
//}

void TKeyboard::setKolVo(const int lKolVo)
{
    KolVo=lKolVo;
}

void TKeyboard::setDopKl(const bool lDopKl)
{
    DopKl=lDopKl;
}

void TKeyboard::setBacklighting(const bool lBacklighting)
{
    Backlighting=lBacklighting;
}

void TKeyboard::setPrice(const int lPrice)
{
    Price = lPrice;
}

TKeyboard::EType TKeyboard::getType()
{
    return Type;
}

TKeyboard::EConstruction TKeyboard::getConstruction()
{
    return Construction;
}

TKeyboard::EInterface TKeyboard::getInterface()
{
    return Interface;
}

//TKeyboard::EColorComb TKeyboard::getColorComb() const
//{
//    return ColorComb;
//}

int TKeyboard::getKolVo()
{
    return KolVo;
}

bool TKeyboard::getDopKl()
{
    return DopKl;
}

bool TKeyboard::getBacklighting()
{
    return Backlighting;
}

int TKeyboard::getPrice() const
{
    return Price;
}

void TKeyboard::show()
{
    const char *SType[]={"Undef", "Membrane", "Mechanical", "SemiMechanical"};
    const char *SConstruction[]={"Default", "Classic", "Ergonomic", "Split", "Rhombic"};
    const char *SInterface[]={"Undefined", "PS2", "USB", "Wireless"};
    const char *SBool[]={"No","Yes"};
    TModel::show();
    std::cout<<"Keyboard Type: "<< SType[Type] <<"\n"<<
               "Constructon Type: "<< SConstruction[Construction] <<"\n"<<
               "Connetcion Type: "<< SInterface[Interface] <<"\n"<<
               "Amount of Keys: "<< KolVo <<"\n"<<
               "Numpad Availability: "<< SBool[DopKl] <<"\n"<<
               "Availability of Backlighting: "<< SBool[Backlighting] <<"\n";
}
