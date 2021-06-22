#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "qfiledialog.h"
#include "qmessagebox.h"
#include <QInputDialog>
#include <QtGui>
#include <fstream>
#include <string>
#include <iostream>
#include "dialogaddedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Tuner");
    ui->tableWidget->setColumnCount(amount+1);

    loadSettings();

    qmPath = qApp->applicationDirPath();
    createLanguageMenu();


    if(active_lang.isEmpty()){
        QList<QAction*> langs = languageActionGroup->actions();
        if (langs.size()>0){
            active_lang = langs[0]->data().toString();
            //langs[0]->setCheckable(true);
        }else{
            //TODO: no lang warning
        }
    }

    setlang(active_lang);
    CreateHeader();
    ui->tableWidget->setColumnWidth(Interface,160);
    ui->tableWidget->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void msgSave()
{
    QMessageBox MSGBox;

    MSGBox.setWindowTitle("Сохраненеие");
    MSGBox.setText("Файл успешно сохранен!\nДля продолжения нажмите \"Ок\"");
    MSGBox.setStandardButtons(QMessageBox::Ok);
    MSGBox.setIcon(QMessageBox::Information);
    MSGBox.setDefaultButton(QMessageBox::Ok);
    int res = MSGBox.exec();
    if (res == QMessageBox::Ok)
        return;
}

void MainWindow::on_pushExit_clicked()
{
    saveSettings(active_lang, this->pos(), this->size());

    close();
}

void MainWindow::ReadFromFile(std::string str, MainWindow::PonSt New)
{
    std::string arr[amount];
    int index[amount+1];

    index[0]=-1;
    int j = 1;
    for(int i=0; i < (int)str.length();i++)
    {
        if(str[i] == ';')
        {
            index[j]=i;
            j++;
        }
    }

    for(int i=0;i<amount;i++)
    {
        arr[i] = str.substr(index[i]+1, index[i+1]-index[i]-1);
    }

    New->Element.setManufacturer(arr[0]);
    New->Element.setModel(arr[1]);
    switch (stoi(arr[2]))
    {
    case 1: New->Element.setType(TKeyboard::Membrane);
        break;
    case 2: New->Element.setType(TKeyboard::Mechanical);
        break;
    case 3: New->Element.setType(TKeyboard::SemiMechanical);
        break;
    }
    switch (stoi(arr[3]))
    {
    case 1: New->Element.setConstruction(TKeyboard::Classic);
        break;
    case 2: New->Element.setConstruction(TKeyboard::Ergonomic);
        break;
    case 3: New->Element.setConstruction(TKeyboard::Split);
        break;
    case 4: New->Element.setConstruction(TKeyboard::Rhombic);
        break;
    }
    switch (stoi(arr[4]))
    {
    case 1: New->Element.setInterface(TKeyboard::PS2);
        break;
    case 2: New->Element.setInterface(TKeyboard::USB);
        break;
    case 3: New->Element.setInterface(TKeyboard::Wireless);
        break;
    }

    New->Element.setKolVo(stoi(arr[5]));
    New->Element.setDopKl(stoi(arr[6]));
    New->Element.setBacklighting(stoi(arr[7]));
    New->Element.setPrice(stoi(arr[8]));
}

void MainWindow::NewRow(MainWindow::PonSt St, int i, bool New)
{
    const QString strType[] = {tr("Undef"),tr("Мембранная"), tr("Механическая"), tr("Мехомембранная")};
    const QString strConstuct[] = {tr("Default"), tr("Классическый"), tr("Эргономичный"), tr("Разделенный"), tr("Ромбический")};
    const QString strInterface[] = {tr("Undefined"), tr("PS2"), tr("USB"), tr("Wireless")};
    if(New)
         ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);

    QTableWidgetItem *TableEl[amount];

    TableEl[0] = new QTableWidgetItem(QString::fromStdString(St->Element.getManufacturer()));
    TableEl[1] = new QTableWidgetItem(QString::fromStdString(St->Element.getModel()));
    TableEl[2] = new QTableWidgetItem(strType[St->Element.getType()]);
    TableEl[3] = new QTableWidgetItem(strConstuct[St->Element.getConstruction()]);
    TableEl[4] = new QTableWidgetItem(strInterface[St->Element.getInterface()]);
//    TableEl[5] = new QTableWidgetItem(strColorComb[St->Element.getColorComb()]);
    TableEl[5] = new QTableWidgetItem(QString::number(St->Element.getKolVo()));
    if(St->Element.getDopKl())
        TableEl[6] = new QTableWidgetItem(tr("Есть"));
    else
        TableEl[6] = new QTableWidgetItem(tr("Нет"));
    if(St->Element.getBacklighting())
        TableEl[7] = new QTableWidgetItem(tr("Есть"));
    else
        TableEl[7] = new QTableWidgetItem(tr("Нет"));
    TableEl[8] = new QTableWidgetItem(QString::number(St->Element.getPrice()));


    ui->tableWidget->setItem(i, Man, TableEl[0]);
    ui->tableWidget->setItem(i, Mod, TableEl[1]);
    ui->tableWidget->setItem(i, Type, TableEl[2]);
    ui->tableWidget->setItem(i, Constr, TableEl[3]);
    ui->tableWidget->setItem(i, Interface, TableEl[4]);
    ui->tableWidget->setItem(i, Kol, TableEl[5]);
    ui->tableWidget->setItem(i, Dop, TableEl[6]);
    ui->tableWidget->setItem(i, BL, TableEl[7]);
    ui->tableWidget->setItem(i, Pr, TableEl[8]);
    ui->tableWidget->setItem(i, ID, new QTableWidgetItem(QString::number(St->ID)));
    //ui->tableWidget->setColumnHidden(ID, true);
}

void MainWindow::DeleteRow(int i)
{
    ui->tableWidget->removeRow(i);
}

void MainWindow::EnabledButtons(bool op)
{
    ui->menu_2->setEnabled(op);
    ui->actionAdd->setEnabled(op);
    ui->actionClose->setEnabled(op);
    ui->actionDelete->setEnabled(op);
    ui->actionEdit->setEnabled(op);
    ui->actionSave->setEnabled(op);
    ui->pushClose->setEnabled(op);
    ui->pushSave->setEnabled(op);
    ui->actionOpen->setEnabled(!op);
    ui->pushOpen->setEnabled(!op);
}

bool MainWindow::Check()
{
    QString  FileN = QString::fromStdString(FN);
    QFile in(FileN);
    FN = FileN.toStdString();

    in.open(QFile::ReadOnly);
    char a [1024];
    PonSt NewL = new KBd;

    while(!in.atEnd()){
        in.readLine(a, sizeof(a));
        std::string str(a);

        if(str.empty())continue;

        try{
            ReadFromFile(str,NewL);
        }
        catch(...){
            in.close();
            return (false);
        }
    }
    in.close();
    return (true);
}

void MainWindow::on_actionOpen_triggered()
{
    QFile in;
    do{
        QString FileN = QFileDialog::getOpenFileName(0, "Выберите файл", "", "*.db *.txt");
        if(FileN=="") return;
        in.setFileName(FileN);
        FN = FileN.toStdString();

        if(!Check()){
            QMessageBox MSGBox;
            MSGBox.setWindowTitle("Ошибка");
            MSGBox.setText("Выбранный вами файл не соответствует требуемому формату!");
            MSGBox.setInformativeText("Ок - открыть другой файл\nCancel - отменить открытие файла");
            MSGBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            MSGBox.setIcon(QMessageBox::Information);
            MSGBox.setDefaultButton(QMessageBox::Ok);
            int res = MSGBox.exec();
            if (res == QMessageBox::Cancel)
                return;
        }
    }while(!Check());

    Last = 0;
    KBdSt = 0;

    in.open(QFile::ReadOnly);
    char a [1024];

    while(!in.atEnd()){
        in.readLine(a, sizeof(a));
        std::string str(a);

        if(str.empty())continue;

        PonSt NewSt = new KBd;

        ReadFromFile(str,NewSt);

        if(!KBdSt){
            Last = NewSt;
            KBdSt = NewSt;
            NewSt->prev = 0;
            NewSt->next = 0;
            NewSt->ID =1;
        }else {
            Last->next = NewSt;
            NewSt->prev= Last;
            NewSt->next = 0;
            NewSt->ID = Last->ID+1;
            Last = NewSt;
        }
        ElemAm++;
    }
    in.close();
    PonSt St = KBdSt;
    int i=0;
    for(St=KBdSt; St!=0; St=St->next, i++){
       NewRow(St,i);
    }

    EnabledButtons(true);
}

void MainWindow::on_actionAdd_triggered()
{
    DialogAddEdit Add;
    Add.setLabel(true);
    Add.exec();
    if(Add.result() == DialogAddEdit::Rejected)
        return;
    PonSt NewE = new KBd;
    NewE->Element.setManufacturer(Add.getMan());
    NewE->Element.setModel(Add.getModel());
    NewE->Element.setType(Add.getType());
    NewE->Element.setConstruction(Add.getConstr());
    NewE->Element.setInterface(Add.getInterface());
//    NewE->Element.setColorComb(Add.getColorComb());
    NewE->Element.setKolVo(Add.getKolVo());
    NewE->Element.setDopKl(Add.getDopKl());
    NewE->Element.setBacklighting(Add.getBL());
    NewE->Element.setPrice(Add.getPrice());

    if(!KBdSt)
    {
        Last = NewE;
        KBdSt = NewE;
        NewE->next = 0;
        NewE->prev = 0;
        NewE->ID = 1;
    }
    else
    {
        Last->next = NewE;
        NewE->prev = Last;
        NewE->next = 0;
        NewE->ID = Last->ID+1;
        Last = NewE;
    }
    ElemAm++;

    NewRow(NewE,ui->tableWidget->rowCount());
}


void MainWindow::EditElmAtLine(int numOfEl){


    int id = ui->tableWidget->item(numOfEl,ID)->text().toInt();


    PonSt NStrct = KBdSt;
    for(NStrct=KBdSt; NStrct; NStrct=NStrct->next){
        if (NStrct->ID == id) break;
    }

    DialogAddEdit Edit;
    Edit.setLabel(false);
    Edit.setMan(NStrct->Element.getManufacturer());
    Edit.setModel(NStrct->Element.getModel());
    Edit.setType(NStrct->Element.getType());
    Edit.setConstr(NStrct->Element.getConstruction());
    Edit.setInterface(NStrct->Element.getInterface());
//    Edit.setColorComb(NStrct->Element.getColorComb());
    Edit.setKolVo(NStrct->Element.getKolVo());
    Edit.setDopKl(NStrct->Element.getDopKl());
    Edit.setBL(NStrct->Element.getBacklighting());
    Edit.setPrice(NStrct->Element.getPrice());

    Edit.exec();

    if(Edit.result() == DialogAddEdit::Rejected)
        return;
    NStrct->Element.setManufacturer(Edit.getMan());
    NStrct->Element.setModel(Edit.getModel());
    NStrct->Element.setType(Edit.getType());
    NStrct->Element.setConstruction(Edit.getConstr());
    NStrct->Element.setInterface(Edit.getInterface());
//    NStrct->Element.setColorComb(Edit.getColorComb());
    NStrct->Element.setKolVo(Edit.getKolVo());
    NStrct->Element.setDopKl(Edit.getDopKl());
    NStrct->Element.setBacklighting(Edit.getBL());
    NStrct->Element.setPrice(Edit.getPrice());

    NewRow(NStrct, numOfEl, false);
}

void MainWindow::DelElmAtLine(int numOfEl){


    int id = ui->tableWidget->item(numOfEl,ID)->text().toInt();

    PonSt St = KBdSt;

    for(St=KBdSt; St; St=St->next){
        if (St->ID == id) break;
    }

    if(St->next)
    {
        St->next->prev = St->prev;
    }
    else
    {
        Last = St->prev;
    }

    if(St->prev)
    {
        St->prev->next = St->next;
    }
    else
    {
        KBdSt = St->next;
    }

    St->~KBd();
    ElemAm--;

    DeleteRow(numOfEl);
}

void MainWindow::on_actionEdit_triggered()
{
    bool check;
    int j;
    int a = QInputDialog::getInt(this, QString::fromUtf8("Редактирование"), QString::fromStdString("Номер редактируемой записи:"), 1, 1, ElemAm, 1, &check) - 1;

    if(!check)
        return;
    EditElmAtLine(a);

}

void MainWindow::on_actionDelete_triggered()
{
    bool ok;
    int i = QInputDialog::getInt(this, QString::fromUtf8("Удаление"),QString::fromUtf8("Номер удаляемой записи:"), 1, 1, 1+ElemAm, 1, &ok) - 1;

    if (!ok) return;
    DelElmAtLine(i);
}

void MainWindow::on_actionClose_triggered()
{
    PonSt St;
    for(St=KBdSt; St!=0; St=St->next){
        St->~KBd();
    }

    KBdSt=0;
    Last=0;
    ElemAm=0;

    for(int i=ui->tableWidget->rowCount(); i >=0; i--)
        DeleteRow(i);

    EnabledButtons(false);
}



void MainWindow::on_actionSave_triggered()
{
    std::fstream out(FN, std::ios_base::out);
    PonSt PS;
    for(PS = KBdSt; PS != 0; PS = PS->next)
    {
        out << PS->Element.getManufacturer() << ";"
            << PS->Element.getModel() << ";"
            << PS->Element.getType() << ";"
            << PS->Element.getConstruction() << ";"
            << PS->Element.getInterface() << ";"
//            << PS->Element.getColorComb() << ";"
            << PS->Element.getKolVo() << ";"
            << PS->Element.getDopKl() << ";"
            << PS->Element.getBacklighting() << ";"
            << PS->Element.getPrice() << ";"
            << std::endl;
    }
    out.close();

    msgSave();
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox MSGBox;

    MSGBox.setWindowTitle("О программе");
    MSGBox.setText("Перед началом работы нажмите \"Файл\"->\"Открыть\" или \"Ctrl+O\"\n\nДмитрий Пастухов ЭУИС-2-4");
    MSGBox.setStandardButtons(QMessageBox::Ok);
    MSGBox.setIcon(QMessageBox::Information);
    MSGBox.setDefaultButton(QMessageBox::Ok);
    int res = MSGBox.exec();
    if (res == QMessageBox::Ok)
        return;
}

void MainWindow::on_pushSave_clicked()
{
    on_actionSave_triggered();
}

void MainWindow::on_pushClose_clicked()
{
    on_actionClose_triggered();
}


void MainWindow::setlang(QString locale){
    if (locale.isEmpty()) return;
    if (!qtLanguageTranslator.load("DimaP_" + locale, qmPath)){
        //TODO:alert lang load error
        return;
    }
    active_lang = locale;
    qApp->installTranslator(&qtLanguageTranslator);
    ui->retranslateUi(this);
    CreateHeader();

}

void MainWindow::switchLanguage(/*QAction *action*/){


    setlang(languageActionGroup->checkedAction()->data().toString());

    for(int i=ui->tableWidget->rowCount();i>=0;i--){
        DeleteRow(i);
    }

    CreateHeader();
    int i=0;
     PonSt St = KBdSt;
    for(St=KBdSt; St; St=St->next,i++){
        NewRow(St,i);
    }


}

//! Программа должна быть на русском языке, но при этом язык программы должен быть оформлен как перевод из файла qm. В исходных файлах всё должно быть на английском через функцию tr().
void MainWindow::createLanguageMenu()
{
    languageActionGroup = new QActionGroup(this);

    connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);

    QDir dir(qmPath);

    QStringList fileNames = dir.entryList(QStringList("DimaP_*.qm")); // получили список файлов с языками

    //QString active_lang = getLang();
    for(int i=0; i<fileNames.size(); ++i){
        QString locale = fileNames[i];
        locale.remove(0,locale.indexOf('.') - 5); //ищем символ "_", удаляем начало
        locale.truncate(locale.lastIndexOf(('.'))); //удаляем последний символ, после .         //в locale остается ru_RU / en_US

        QTranslator translator;

        if (translator.load(fileNames[i], qmPath)){

            QString language = translator.translate("Mainwindow", "English");

            QAction *action = new QAction(language,this); //tr - метод переводчик разыскивает
            //- нажимаемая кнопка.
            action->setData(locale);
            ui->menu_lang->addAction(action);
            languageActionGroup->addAction(action);
            action->setCheckable(true);
            if (locale == active_lang){
                //action->setCheckable(true);
                action->setChecked(true);
            }
            //languageActionGroup->findChild()
        }

        //if(language == "English")
            //action->setCheckable(true); //включаем кнопку, если язык английский
    }
}

void MainWindow::CreateHeader()
{QStringList titles;
    titles << tr("Производитель") << tr("Модель") << tr("Тип") << tr("Конструкция") << tr("Интерфейсы подключения") << tr("Кол-во клавиш") << tr("Нумпад") << tr("Подсветка") << tr("Цена") ;
        ui->tableWidget->setHorizontalHeaderLabels(titles);
}


//! 15.	+ Программа должна запоминать настройки интерфейса.
void MainWindow::saveSettings(QString locale, QPoint pos,QSize dim)
{

        QSettings settings("settings.ini",QSettings::IniFormat);
        settings.beginGroup("Settings");
        settings.setValue("language",locale);
        settings.endGroup();
        settings.beginGroup("WindowGeometry");
        settings.setValue("pos",pos);
        settings.setValue("dim",dim);
}
//! 15.1	+ Программа должна запоминать настройки интерфейса.
void MainWindow::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("WindowGeometry");
    resize(settings.value("dim", QSize(1000,1000)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    settings.beginGroup("Settings");
    active_lang = settings.value("language").toString();
    settings.endGroup();

}

void MainWindow::on_lineEdit_editingFinished()
{
    const QString strType[] = {tr("Undef"),tr("Мембранная"), tr("Механическая"), tr("Мехомембранная")};
    const QString strConstuct[] = {tr("Default"), tr("Классическый"), tr("Эргономичный"), tr("Разделенный"), tr("Ромбический")};
    const QString strInterface[] = {tr("Undefined"), tr("PS2"), tr("USB"), tr("Wireless")};

    PonSt St = KBdSt;
    for(int i=ui->tableWidget->rowCount();i>=0;i--){
        DeleteRow(i);
    }

    if (ui->lineEdit->text().isEmpty()){
        for(St=KBdSt; St!=0; St=St->next){
            NewRow(St,ui->tableWidget->rowCount());
        }

    }else{
    for(St=KBdSt; St!=0; St=St->next){


        QTableWidgetItem *TableEl[amount];

        TableEl[0] = new QTableWidgetItem(QString::fromStdString(St->Element.getManufacturer()));
        TableEl[1] = new QTableWidgetItem(QString::fromStdString(St->Element.getModel()));
        TableEl[2] = new QTableWidgetItem(strType[St->Element.getType()]);
        TableEl[3] = new QTableWidgetItem(strConstuct[St->Element.getConstruction()]);
        TableEl[4] = new QTableWidgetItem(strInterface[St->Element.getInterface()]);
    //    TableEl[5] = new QTableWidgetItem(strColorComb[St->Element.getColorComb()]);
        TableEl[5] = new QTableWidgetItem(QString::number(St->Element.getKolVo()));
        if(St->Element.getDopKl())
            TableEl[6] = new QTableWidgetItem(tr("Есть"));
        else
            TableEl[6] = new QTableWidgetItem(tr("Нет"));
        if(St->Element.getBacklighting())
            TableEl[7] = new QTableWidgetItem(tr("Есть"));
        else
            TableEl[7] = new QTableWidgetItem(tr("Нет"));
        TableEl[8] = new QTableWidgetItem(QString::number(St->Element.getPrice()));


    for (int i=0; i<9 ;i++){
        if (TableEl[i]->text().contains(ui->lineEdit->text())){
             NewRow(St,ui->tableWidget->rowCount());
             break;
        }
    }
    }

    }
}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{


    QModelIndex ind = ui->tableWidget->indexAt((ui->tableWidget->viewport()->mapFromGlobal(event->globalPos())));
    int a = ind.row();
     //int b = ind.column();
    if (a>=0){
         QMenu * menu = new QMenu(this);
         QAction * edit = new QAction(tr("Edit"), menu);
         edit->setData("edit");
         menu->addAction(edit);
         QAction * del = new QAction(tr("Del"), menu);
         del->setData("del");
         menu->addAction(del);

         QAction *s = menu->exec(event->globalPos());//ui->tableWidget->mapFromGlobal(event->globalPos()));//event->globalPos());
         if (s){
            if (s->data().toString() == "edit"){
                EditElmAtLine(a);
            }else if (s->data().toString() == "del"){
                DelElmAtLine(a);
            }
         }


    }


}
