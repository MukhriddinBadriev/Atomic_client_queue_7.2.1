#include <iostream>

#include <thread>
#include <atomic>

#include <chrono>
#include <Windows.h>

class consol_color
{
public:
    static void SetColor(int text, int background)
    {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }
};

std::atomic<int> n = 1;

void Client(int count) {
    
    while (n != count) {
        n.operator++();
        consol_color::SetColor(12, 0);
        std::cout << n.load() << " ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    }
}

void Teller() {

    while (n != 0) {
        n.operator--();
        consol_color::SetColor(10, 0);
        std::cout << n.load() << " ";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
    }
}


int main()
{
    int count = 0;
    std::cout << "Enter max number client: ";
    std::cin >> count;
    std::thread t1(Client,count);

    std::thread t2(Teller);

    t1.join();
    t2.join();

    return 0;
}