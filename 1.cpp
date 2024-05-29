// Клас-рядок, який містить методи, необхідні для роботи методів класу-контейнера. Клас-контейнер, який є абстракцією тексту та складається з об’єктів класу-рядка та методів додавання рядка до тексту, видалення рядка з тексту, очищення тексту, повернення найбільшого рядка, повернення відсотка символів-цифр у тексті, повернення загальної кількості символів
// Створити один чи декілька об’єктів текстів та продемонструвати їх функціональність, застосовуючи операції над текстом

#include <iostream>

class Line{
    private:
        char *line;
    public:
        Line *next;
        Line(const char *line){
            this->line = new char[strlen(line) + 1];
            strcpy(this->line, line);
            next = nullptr;
        }
        ~Line(){
            delete[] line;
        }
        int getLength(){
            return strlen(line);
        }
        char* getLine(){
            return line;
        }
        int getDigitsPercent(){
            int count = 0;
            for(int i = 0; i < strlen(line); i++){
                if(isdigit(line[i])){
                    count++;
                }
            }
            return count * 100 / strlen(line);
        }
        void print(){
            std::cout << line << std::endl;
        }
};

class Text {
    private:
        Line *head;
    public:
        Text(){
            head = nullptr;
        }
        void addLine(Line *line){
            if(head == nullptr){
                head = line;
            } else {
                Line *current = head;
                while(current->next != nullptr){
                    current = current->next;
                }
                current->next = line;
            }
        }
        void removeLine(int index){
            if(index == 0){
                Line *temp = head;
                head = head->next;
                delete temp;
            } else {
                Line *current = head;
                for(int i = 0; i < index - 1; i++){
                    current = current->next;
                }
                Line *temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
        void clear(){
            while(head != nullptr){
                Line *temp = head;
                head = head->next;
                delete temp;
            }
        }
        Line* getLongestLine(){
            Line *current = head;
            Line *longest = head;
            while(current != nullptr){
                if(current->getLength() > longest->getLength()){
                    longest = current;
                }
                current = current->next;
            }
            return longest;
        }
        int getDigitsPercent(){
            int count = 0;
            int total = 0;
            Line *current = head;
            while(current != nullptr){
                total += current->getDigitsPercent();
                count++;
                current = current->next;
            }
            return total / count;
        }
        void printText(){
            Line *current = head;
            while(current != nullptr){
                current->print();
                current = current->next;
            }
        }
        int getTotalChars(){
            int total = 0;
            Line *current = head;
            while(current != nullptr){
                total += current->getLength();
                current = current->next;
            }
            return total;
        }
};


int main()
{

    Text text;

    text.addLine(new Line("Hello"));
    text.addLine(new Line("World"));
    text.addLine(new Line("12345"));
    text.addLine(new Line("1234512345"));
    std::cout << "Digits percent: " << text.getDigitsPercent() << std::endl;
    std::cout << "Longest line:" << std::endl;
    text.getLongestLine()->print();
    std::cout << "Text:" << std::endl;
    text.printText();
    std::cout << "Total chars: " << text.getTotalChars() << std::endl;

    std::cout << "Removing line 2 (counting from 0)" << std::endl;
    text.removeLine(2);
    std::cout << "Digits percent: " << text.getDigitsPercent() << std::endl;
    std::cout << "Longest Line: ";
    text.getLongestLine()->print();
    std::cout << "Text:" << std::endl;
    text.printText();
    std::cout << "Total chars: " << text.getTotalChars() << std::endl;

    std::cout << "Clearing text" << std::endl;
    text.clear();
    std::cout << "Text:" << std::endl;
    text.printText();
    return 0;
}