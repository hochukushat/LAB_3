#include "dialogaddedit.h"
#include "ui_dialogaddedit.h"

DialogAddEdit::DialogAddEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEdit)
{
    ui->setupUi(this);
}

DialogAddEdit::~DialogAddEdit()
{
    delete ui;
}

void DialogAddEdit::setMan(const std::string lMan)
{
    ui->lineEditMan->setText(QString::fromStdString(lMan));
}

std::string DialogAddEdit::getMan() const
{
    return ui->lineEditMan->text().toStdString();
}

void DialogAddEdit::setModel(const std::string lModel)
{
    ui->lineEditModel->setText(QString::fromStdString(lModel));
}

std::string DialogAddEdit::getModel() const
{
    return ui->lineEditModel->text().toStdString();
}

void DialogAddEdit::setType(const TKeyboard::EType lType)
{
    ui->comboType->currentData(lType);
}

TKeyboard::EType DialogAddEdit::getType() const
{
    switch (ui->comboType->currentIndex())
    {
    case 1: return TKeyboard::EType::Mechanical;
        break;
    case 2: return TKeyboard::EType::Membrane;
        break;
    case 3: return TKeyboard::EType::SemiMechanical;
        break;
    }
}

void DialogAddEdit::setConstr(const TKeyboard::EConstruction lConstr)
{
    ui->comboConstr->currentData(lConstr);
}

TKeyboard::EConstruction DialogAddEdit::getConstr() const
{
    switch (ui->comboConstr->currentIndex())
    {
    case 1: return TKeyboard::Classic;
        break;
    case 2: return TKeyboard::Ergonomic;
        break;
    case 3: return TKeyboard::Split;
        break;
    case 4: return TKeyboard::Rhombic;
        break;
    }
}

void DialogAddEdit::setInterface(const TKeyboard::EInterface lInterface)
{
    ui->comboInterface->currentData(lInterface);
}

TKeyboard::EInterface DialogAddEdit::getInterface() const
{
    switch (ui->comboInterface->currentIndex())
    {
    case 1: return TKeyboard::PS2;
    case 2: return TKeyboard::USB;
    case 3: return TKeyboard::Wireless;
    }
}

//void DialogAddEdit::setColorComb(const TKeyboard::EColorComb lColor)
//{
//    ui->comboColor->currentData(lColor);
//}

//TKeyboard::EColorComb DialogAddEdit::getColorComb() const
//{

//    switch (ui->comboColor->currentIndex())
//    {
//    case 1: return TKeyboard::EColorComb::White;
//    case 2: return TKeyboard::EColorComb::Black;
//    case 3: return TKeyboard::EColorComb::WB;
//    case 4: return TKeyboard::EColorComb::BR;
//    case 5: return TKeyboard::EColorComb::Custom;
//    }

//}

void DialogAddEdit::setKolVo(const int lKolVo)
{
    ui->lineEditKolVo->setText(QString::number(lKolVo));
}

int DialogAddEdit::getKolVo() const
{
    return ui->lineEditKolVo->text().toInt();
}

void DialogAddEdit::setDopKl(const bool lDop)
{
    if(lDop)
    {
        ui->radioYes->setChecked(true);
        ui->radioNo->setChecked(false);
    }
    else
    {
        ui->radioNo->setChecked(true);
        ui->radioYes->setChecked(false);
    }
}

bool DialogAddEdit::getDopKl() const
{
    if(ui->radioYes->isChecked())
        return 1;
    else if(ui->radioNo->isChecked())
        return 0;;
}

void DialogAddEdit::setBL(const bool lBL)
{
    if(lBL)
    {
        ui->radioYes_2->setChecked(true);
        ui->radioNo_2->setChecked(false);
    }
    else
    {
        ui->radioNo_2->setChecked(true);
        ui->radioYes_2->setChecked(false);
    }
}

bool DialogAddEdit::getBL() const
{
    if(ui->radioYes_2->isChecked())
        return 1;
    else if(ui->radioNo_2->isChecked())
        return 0;
}

void DialogAddEdit::setPrice(const int lPrice)
{
    ui->lineEditPrice->setText(QString::number(lPrice));
}

int DialogAddEdit::getPrice() const
{
    return ui->lineEditPrice->text().toInt();
}

void DialogAddEdit::setLabel(bool type)
{
    if(type)
    {
        ui->labelHead->setText("Добавление нового элемента");
        setWindowTitle("Удаление");
    }
    else
    {
        ui->labelHead->setText("Редактирование элемента");
        setWindowTitle("Редактирование");
    }
}

