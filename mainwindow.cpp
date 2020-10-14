#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery qry;
//............................................................................
    qry.prepare("select * from hero;");
    qry.exec();
    while (qry.next()){
       Hero * hero = new Hero(qry.value(1).toString(), qry.value(2).toString(),
                               (qry.value(3).toString().at(0) == NULL)? false:true, qry.value(4).toString());
       Heroes.push_back(std::shared_ptr<Hero>(hero));
    }
//............................................................................
    qry.prepare("select * from place;");
    qry.exec();
    while (qry.next()){
       Place *place = new Place(qry.value(1).toString(), qry.value(2).toString());
       Places.push_back(std::shared_ptr<Place>(place));
    }
//............................................................................
    QSqlQuery qryacts, qryplaces, qryheroes;
    qryacts.prepare("select * from act where bookid = :id order by number;");
    qryheroes.prepare("select hero.name, hero.kind, hero.positive, hero.description from hero inner join heroinact on hero.id = heroid inner join act on act.id = actid where act.id = :actid;");
    qryplaces.prepare("select place.name, place.description from place inner join actinplace on place.id = placeid inner join act on act.id = actid where act.id = :actid;");
    qry.prepare("select * from book;");
    qry.exec();

    while (qry.next()){
        Book somebook(qry.value(1).toString(), qry.value(0).toDouble(),
                      qry.value(2).toInt());
        qryacts.bindValue(":id",qry.value(0).toDouble());
        qryacts.exec();
        int actnumber = 1;
        while(qryacts.next()){
            //std::cout << "Act% " << actnumber << "  ";
            Act act(qryacts.value(1).toString(), qryacts.value(2).toString(),
                    qryacts.value(3).toString());
            int actid = qryacts.value(0).toInt();
            qryheroes.bindValue(":actid", actid);
            qryheroes.exec();
            qryplaces.bindValue(":actid", actid);
            qryplaces.exec();
            while (qryheroes.next()){
                Hero* hero = new Hero(qryheroes.value(0).toString(),
                                      qryheroes.value(1).toString(),
                                      (qryheroes.value(2).toString().at(0) == NULL)? false:true,
                                      qryheroes.value(3).toString());
                for (int i = 0; i < Heroes.size(); i++) {
                    if (*Heroes.at(i) == *hero){
                        std::shared_ptr<Hero> it(Heroes.at(i));
                        act.addHero(it);
                        break;
                    }
                }
            }
            while (qryplaces.next()){
                Place* place = new Place(qryplaces.value(0).toString(),
                                         qryplaces.value(1).toString());
                for (int i = 0; i < Places.size(); i++) {
                    if (*Places.at(i) == *place){
                        std::shared_ptr<Place> it(Places.at(i));
                        act.addPlace(it);
                        break;
                    }
                }

            }
            somebook.addAct(act, actnumber);
            actnumber++;
        }
        books.push_back(somebook);
    }
    placeWindow = new PlaceWindow(&Places);
    heroWindow = new HeroWindow(&Heroes);
    placeWindow->hide();
    heroWindow->hide();
    ui->comboBox_2->setModel(placeWindow->receiveModel());
    ui->comboBox->setModel(heroWindow->receiveModel());
    model = new ActModel(QVector<Act>());
    showBook();
}

MainWindow::~MainWindow()
{
    QSqlQuery qry;
    qry.prepare("delete from hero;");
    qry.exec();
    qry.prepare("delete from place;");
    qry.exec();
    qry.prepare("delete from book;");
    qry.exec();
    qry.prepare("insert into hero values (:id, :name, :kind, :positive, :description)");
    for (int i = 0; i < Heroes.length(); i++)
    {
        qry.bindValue(":id", i + 1);
        qry.bindValue(":name", Heroes[i]->name());
        qry.bindValue(":kind", Heroes[i]->kind());
        qry.bindValue(":positive", Heroes[i]->isPositive());
        qry.bindValue(":description", Heroes[i]->description());
        qry.exec();
    }
    qry.prepare("insert into place values (:id, :name, :description)");
    for (int i = 0; i < Places.length(); i++)
    {
        qry.bindValue(":id", i + 1);
        qry.bindValue(":name", Places[i]->name());
        qry.bindValue(":description", Places[i]->description());
        qry.exec();
    }
    qry.prepare("insert into book values (:id, :name, :year);");
    QSqlQuery qryacts, qryheros, qryplaces, findhero, findplace;
    qryacts.prepare("insert into act values (:id, :name, :description, :result, :bookid, :number);");
    qryheros.prepare("insert into heroinact values (:heroid, :actid);");
    qryplaces.prepare("insert into actinplace values (:placeid, :actid);");
    findhero.prepare("select id from hero where name = :name;");
    findplace.prepare("select id from place where name = :name;");
    int actid = 1;
    for (int i = 0; i < books.length(); i++)
    {
        qry.bindValue(":id", books[i].number());
        qry.bindValue(":name", books[i].name());
        qry.bindValue(":year", books[i].year());
        qry.exec();
        for (int j = 0; j < books[i].acts().length(); j++){

            qryacts.bindValue(":id", actid);
            qryacts.bindValue(":name", books[i].acts()[j].name());
            qryacts.bindValue(":description", books[i].acts()[j].description());
            qryacts.bindValue(":result", books[i].acts()[j].result());
            qryacts.bindValue(":bookid", books[i].number());
            qryacts.bindValue(":number", j + 1);
            qryacts.exec();

            for (int s = 0; s < books[i].acts()[j].heroesQuantity(); s++){
                findhero.bindValue(":name", books[i].acts()[j].hero(s + 1).name());
                findhero.exec();
                findhero.next();
                int id = findhero.value(0).toInt();
                qryheros.bindValue(":heroid", id);
                qryheros.bindValue(":actid", actid);
                qryheros.exec();
            }

            for (int s = 0; s < books[i].acts()[j].placesQuantity(); s++){
                findplace.bindValue(":name", books[i].acts()[j].place(s + 1).name());
                findplace.exec();
                findplace.next();
                int id = findplace.value(0).toInt();
                qryplaces.bindValue(":placeid", id);
                qryplaces.bindValue(":actid", actid);
                qryplaces.exec();
            }

            actid++;
        }
    }
    delete ui;
    delete placeWindow;
    delete heroWindow;
    delete model;
}

void MainWindow::on_forward_clicked()
{
    if (++currentBook >= books.length())
        currentBook = 0;
    showBook();
}

void MainWindow::on_action_triggered()
{
    heroWindow->show();
}

void MainWindow::on_action_2_triggered()
{
    placeWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString nameOfNewHero = ui->comboBox->currentText();

    QStringList listOfHeroes = ui->textEdit_3->toPlainText().split(",", QString::SkipEmptyParts);
    listOfHeroes << nameOfNewHero;
    listOfHeroes.removeDuplicates();
    QString str = listOfHeroes.join(",");
    ui->textEdit_3->setText(str);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString nameOfNewPlace = ui->comboBox_2->currentText();
    QStringList listOfPlaces = ui->textEdit_4->toPlainText().split(",", QString::SkipEmptyParts);
    listOfPlaces << nameOfNewPlace;
    listOfPlaces.removeDuplicates();
    QString str = listOfPlaces.join(",");
    ui->textEdit_4->setText(str);
}

void MainWindow::on_pushButton_clicked()
{
    QString nameOfRemovingHero = ui->comboBox->currentText();

    QStringList listOfHeroes = ui->textEdit_3->toPlainText().split(",", QString::SkipEmptyParts);
    int i = listOfHeroes.indexOf(nameOfRemovingHero);
    listOfHeroes.removeAt(i);
    listOfHeroes.removeDuplicates();
    QString str = listOfHeroes.join(",");
    ui->textEdit_3->setText(str);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString nameOfRemovingPlace = ui->comboBox_2->currentText();

    QStringList listOfPlaces = ui->textEdit_4->toPlainText().split(",", QString::SkipEmptyParts);
    int i = listOfPlaces.indexOf(nameOfRemovingPlace);
    listOfPlaces.removeAt(i);
    listOfPlaces.removeDuplicates();
    QString str = listOfPlaces.join(",");
    ui->textEdit_4->setText(str);
}

void MainWindow::on_back_clicked()
{
    if (--currentBook < 0)
        currentBook = books.length() - 1;
    showBook();
}

void MainWindow::showBook()
{
    if (model != nullptr)
        delete model;
    if (books.size()!=0){
        model = new ActModel(books[currentBook].acts());
        ui->tableView->setModel(model);
        ui->bookname->setText("Название: " + books[currentBook].name());
        ui->number->setText("Номер в серии: " + QString::number(books[currentBook].number()));
        ui->year->setText("Год: " + QString::number(books[currentBook].year()));
    }
    else {
        model = new ActModel(QVector<Act>());
        ui->tableView->setModel(model);
        ui->bookname->setText("Название: " );
        ui->number->setText("Номер в серии: " );
        ui->year->setText("Год: ");
    }
}

void MainWindow::on_actionAddBook_triggered()
{
    BookDialog dialog;
    if (dialog.exec() == QDialog::Accepted){
        books.insert(currentBook+1,Book(dialog.name(), dialog.number(), dialog.year()));
        on_forward_clicked();
    }
}

void MainWindow::on_actionDeleteBook_triggered()
{
    if (books.length() > 0 ){
        books.remove(currentBook);
        on_back_clicked();
    }
}

void MainWindow::on_actionEditBook_triggered()
{
    if (books.length() != 0 ){
        BookDialog dialog(books[currentBook].name(), books[currentBook].number(), books[currentBook].year());
        if (dialog.exec() == QDialog::Accepted){
            books[currentBook].setName(dialog.name());
            books[currentBook].setNumber(dialog.number());
            books[currentBook].setYear(dialog.year());
            showBook();
        }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if (books.length() != 0){
        if (ui->tableView->currentIndex().isValid())
            model->removeRows(ui->tableView->currentIndex().row(),1);
        books[currentBook].setActs(model->acts());
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if (books.length() != 0){
        QModelIndex in,in1, in4;
        if (ui->tableView->currentIndex().isValid())
        {
            model->insertRows(ui->tableView->currentIndex().row() + 1,1);
            in = model->index(ui->tableView->currentIndex().row() + 1,
                                          0,
                                          ui->tableView->currentIndex().parent());
            in1 = model->index(ui->tableView->currentIndex().row() + 1,
                                           1,
                                           ui->tableView->currentIndex().parent());
            in4 = model->index(ui->tableView->currentIndex().row() + 1,
                               4,
                               ui->tableView->currentIndex().parent());
        } else {
            model->insertRows(model->rowCount(), 1);
            in = model->index(model->rowCount() - 1,
                                          0,
                                          ui->tableView->currentIndex().parent());
            in1 = model->index(model->rowCount() - 1,
                                           1,
                                           ui->tableView->currentIndex().parent());
            in4 = model->index(model->rowCount() - 1,
                                           4,
                                           ui->tableView->currentIndex().parent());
        }
         model->setData(in,ui->lineEdit->text(),Qt::EditRole);
         model->setData(in1,ui->textEdit->toPlainText(),Qt::EditRole);
         model->setData(in4,ui->textEdit_2->toPlainText(),Qt::EditRole);
         //Act act;
         QStringList listofheroes = ui->textEdit_3->toPlainText().split(",", QString::SkipEmptyParts);
         listofheroes.removeDuplicates();
         QStringList listofplaces = ui->textEdit_4->toPlainText().split(",", QString::SkipEmptyParts);
         listofplaces.removeDuplicates();
         for (int i = 0; i < listofheroes.length(); i++)
         {
             for (int j = 0; j < Heroes.length(); j++)
             {
                 if (Heroes.at(j)->name() == listofheroes.at(i))
                     {
                         model->addHero(in,Heroes.at(j));
                         break;
                     }
             }
         }
         for (int i = 0; i < listofplaces.length(); i++)
         {
             for (int j = 0; j < Places.length(); j++)
             {
                 if (Places.at(j)->name() == listofplaces.at(i))
                     {
                         model->addPlace(in,Places.at(j));
                         break;
                     }
             }
         }
         books[currentBook].setActs(model->acts());
    }
}
