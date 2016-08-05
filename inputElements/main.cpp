#include "lineEdit.h"
#include <QApplication>
#include <QPrinter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineEdit l;
//    l.show();

    QTextEdit* text = new QTextEdit;
    text->setPlainText("Simple text2");
    QTextDocumentWriter writer;
    writer.setFileName("teeeext.txt");
    writer.write(text->document());

    QTextEdit* pdf = new QTextEdit("PDF text");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
    pdf->document()->print(&printer);

    return a.exec();
}
