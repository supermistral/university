#include "shannon_fano.h"
#include "huffman.h"
#include <Windows.h>


void shannonFanoTest() {
    ShannonFano shannonFano;
    std::string text = "Прибавь к ослиной голове Еще одну, получишь две. Но сколько б ни было ослов, Они и двух не свяжут слов.";
    std::string file = "D:\\temp\\siaod\\text.txt";

    shannonFano.encode(text);
    shannonFano.printEncodedString();
    shannonFano.writeFile(file);
    shannonFano.readEncodedFile(file);
    std::cout << "\n" << shannonFano.decode();
}

void huffmanTest() {
    Huffman huffman;
    std::string text = "иванов иван иванович";
    std::cout << text << "\n";
    std::string file = "D:\\temp\\siaod\\text.txt";

    huffman.encode(text);
    huffman.printEncodedString();
    huffman.printDOT();
    huffman.writeFile(file);
    huffman.readEncodedFile(file);
    std::cout << "\n" << huffman.decode();
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    shannonFanoTest();
    huffmanTest();

    return 0;
}
