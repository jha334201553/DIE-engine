// Copyright (c) 2012-2019 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "dialogelfmachine.h"
#include "ui_dialogelfmachine.h"

DialogELFMachine::DialogELFMachine(QWidget *parent) :
    DialogELFGeneric(parent),
    ui(new Ui::DialogELFMachine)
{
    ui->setupUi(this);

    //    ui->comboBoxValue->addItem("");
    //    ui->comboBoxValue->addItem("NONE");
    //    ui->comboBoxValue->addItem("M32");
    //    ui->comboBoxValue->addItem("SPARC");
    //    ui->comboBoxValue->addItem("386");
    //    ui->comboBoxValue->addItem("68K");
    //    ui->comboBoxValue->addItem("88K");
    //    ui->comboBoxValue->addItem("860");
    //    ui->comboBoxValue->addItem("MIPS");
    //    ui->comboBoxValue->addItem("AMD64");

    ui->lineEditValue->setInputMask("HHHH");

    ui->checkBoxReadOnly->setChecked(true);

    ui->pushButtonCancel->setShortcut(QKeySequence(__KeySequence_quit));
    ui->pushButtonApply->setShortcut(QKeySequence(__KeySequence_save));
    ui->pushButtonOK->setShortcut(QKeySequence(__KeySequence_saveandquit));
}

DialogELFMachine::~DialogELFMachine()
{
    delete ui;
}

void DialogELFMachine::on_pushButtonOK_clicked()
{
    if(ui->pushButtonApply->isEnabled())
    {
        on_pushButtonApply_clicked();
    }

    on_pushButtonCancel_clicked();
}

bool DialogELFMachine::reload()
{
    if(pOptions->bShowTooltips)
    {
        ui->pushButtonOK->setToolTip(tr("Quit and apply changes"));
        ui->pushButtonCancel->setToolTip(tr("Quit without changes"));
        ui->pushButtonApply->setToolTip(tr("Apply changes"));
        ui->checkBoxReadOnly->setToolTip(tr("Set/unset read-only mode"));
        ui->lineEditValue->setToolTip(tr("Machine"));
        ui->comboBoxValue->setToolTip(tr("Set machine"));
    }

    ui->comboBoxValue->clear();
    ui->comboBoxValue->addItem("","");

    QList<ELFFile::MACHINE> list=ELFFile::getMachineList();

    for(int i=0; i<list.count(); i++)
    {
        ui->comboBoxValue->addItem(list.at(i).sName.section("_",1,1),QString("%1").arg(list.at(i).nMachine,4,16,QChar('0')));
    }

    unsigned short sValue=elffile->getElfHeader_machine();
    ui->lineEditValue->setText(QString("%1").arg(sValue,4,16,QChar('0')));

    ui->checkBoxReadOnly->setEnabled(!elffile->isReadOnly());

    ui->pushButtonApply->setEnabled(false);

    return true;
}


void DialogELFMachine::on_checkBoxReadOnly_stateChanged(int arg1)
{
    ui->lineEditValue->setReadOnly(ui->checkBoxReadOnly->checkState());
    ui->comboBoxValue->setEnabled(!ui->checkBoxReadOnly->checkState());
}

void DialogELFMachine::on_pushButtonCancel_clicked()
{
    this->close();
}

void DialogELFMachine::on_pushButtonApply_clicked()
{
    bool bTemp;
    ui->pushButtonApply->setEnabled(false);

    elffile->setElfHeader_machine(ui->lineEditValue->text().toUInt(&bTemp,16));

    ui->checkBoxReadOnly->setCheckState(Qt::Unchecked);

    emit reloadSignal();
}

void DialogELFMachine::on_lineEditValue_textChanged(const QString &arg1)
{
    //    ui->comboBoxValue->setCurrentIndex(0);
    //    bool bTemp;
    for(int i=0; i<ui->comboBoxValue->count(); i++)
    {
        if(arg1==ui->comboBoxValue->itemData(i).toString())
        {
            ui->comboBoxValue->setCurrentIndex(i);
            return;
        }
    }

    ui->comboBoxValue->setCurrentIndex(0);

    //    switch(arg1.toUInt(&bTemp,16))
    //    {
    //    case(0):
    //        ui->comboBoxValue->setCurrentIndex(1);
    //        break;
    //    case(1):
    //        ui->comboBoxValue->setCurrentIndex(2);
    //        break;
    //    case(2):
    //        ui->comboBoxValue->setCurrentIndex(3);
    //        break;
    //	case(3):
    //        ui->comboBoxValue->setCurrentIndex(4);
    //        break;
    //	case(4):
    //        ui->comboBoxValue->setCurrentIndex(5);
    //        break;
    //    case(5):
    //        ui->comboBoxValue->setCurrentIndex(6);
    //        break;
    //    case(7):
    //        ui->comboBoxValue->setCurrentIndex(7);
    //        break;
    //    case(8):
    //        ui->comboBoxValue->setCurrentIndex(8);
    //        break;
    //    case(62):
    //        ui->comboBoxValue->setCurrentIndex(9);
    //        break;


    //    default:
    //        ui->comboBoxValue->setCurrentIndex(0);
    //    }

    ui->pushButtonApply->setEnabled(true);
}

void DialogELFMachine::on_comboBoxValue_currentIndexChanged(int index)
{
    if(ui->comboBoxValue->itemData(index).toString()!="")
    {
        ui->lineEditValue->setText(ui->comboBoxValue->itemData(index).toString());
    }
    //    switch(index)
    //    {
    //    case(1):
    //        ui->lineEditValue->setText("0000");
    //        break;
    //    case(2):
    //        ui->lineEditValue->setText("0001");
    //        break;
    //    case(3):
    //        ui->lineEditValue->setText("0002");
    //        break;
    //    case(4):
    //        ui->lineEditValue->setText("0003");
    //        break;
    //    case(5):
    //        ui->lineEditValue->setText("0004");
    //        break;
    //    case(6):
    //        ui->lineEditValue->setText("0005");
    //        break;
    //    case(7):
    //        ui->lineEditValue->setText("0007");
    //        break;
    //    case(8):
    //        ui->lineEditValue->setText("0008");
    //        break;
    //    case(9):
    //        ui->lineEditValue->setText("003e");
    //        break;
    //    }
}
