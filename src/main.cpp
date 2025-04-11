#include <iostream>
#include <string>
#include <iomanip>
#include <csv_reader.h>

class Workplace
{
private:
    std::string cashier;
    int cash;
    int totalAmount;

public:
    Workplace(const std::string &cashier_name)
    {
        cashier = cashier_name;
        cash = 50000;
        totalAmount = 0;

        std::cout << "Открытие смены..." << std::endl
                  << std::endl;
    }

    void info()
    {
        std::cout << "Кассир - " << cashier << std::endl;
        std::cout << "Наличных в кассе - " << cash << " руб." << std::endl;
        std::cout << "Выручка - " << totalAmount << " руб." << std::endl
                  << std::endl;
    }

    void menu()
    {
        int width = 18;

        std::cout << std::left
                  << std::setw(width) << "№"
                  << std::setw(width) << "Опция" << std::endl;

        std::cout << std::string(width * 2, '-') << std::endl;

        std::cout << std::setw(width) << "1" << std::setw(width) << "Чек" << std::endl;
        std::cout << std::setw(width) << "2" << std::setw(width) << "Статистика по смене" << std::endl;
        std::cout << std::setw(width) << "3" << std::setw(width) << "Закрытие смены" << std::endl;

        std::cout << std::string(width * 2, '-') << std::endl;
    }

    void sell()
    {
        std::cout << "Список товаров: " << std::endl;
        std::vector<Product> products = readCSV("../data/test.csv");
        std::vector<Cell> purchase;
        std::vector<int> codes;

        std::cout << std::string(45, '-') << std::endl;
        for (const auto &product : products)
        {
            std::cout << product.id 
                      << ". " << product.name 
                      << ", Код: " << product.barcode
                      << ", Цена: " << product.price << " руб."
                      << std::endl;
            
            codes.push_back(product.barcode);
        }
        std::cout << std::string(45, '-') << std::endl;
        std::cout << std::endl;

        std::cout << "Заполнение чека..." << std::endl;
        std::cout << "* для закрытия чека введите \"0\" как номер товара" << std::endl << std::endl;
        int totalPurchaseAmount = 0;
        while (true) {
            int code, count, amount;
            Cell cell;

            std::cout << "Введите штрихкод товара: ";
            std::cin >> code;

            if (code == 0) break;
            if (std::find(codes.begin(), codes.end(), code) == codes.end()) {
                std::cout << "Товара с данным кодом не существует" << std::endl << std::endl;
                continue;
            }

            std::cout << "Введите количество: ";
            std::cin >> count;
            std::cout << std::endl;


            Product product = get_product(products, code);
            cell.name = product.name;
            cell.count = count;
            cell.price = product.price * count;

            purchase.push_back(cell);
            totalPurchaseAmount += product.price * count;
        }

        std::cout << std::endl << "Чек: " << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        for (const auto &cell : purchase) {
            std::cout << cell.name << ", "
                      << cell.count << " шт. Сумма: " 
                      << cell.price 
                      << std::endl;
        }
        std::cout << std::string(40, '-') << std::endl;
        std::cout << "Итого: " << totalPurchaseAmount << " руб." << std::endl << std::endl << std::endl;

        int pay;
        std::cout << "Оплата" << std::endl;
        std::cout << "1) Картой" << std::endl;
        std::cout << "2) Наличными" << std::endl << std::endl;
        std::cout << "Выберите способ оплаты: ";
        std::cin >> pay;
        std::cout << std::endl;

        switch (pay)
        {
        case 1:
            totalAmount += totalPurchaseAmount;
            std::cout << "Чек закрыт" << std::endl << std::endl << std::endl;
            break;
        case 2:
            if (totalPurchaseAmount > cash) {
                std::cout << "Недостаточно денег в кассе для сдачи, покупка отменена" << std::endl << std::endl;
                break;
            } 
            cash -= totalPurchaseAmount;
            totalAmount += totalPurchaseAmount;
            break;
        default:
            break;
        }
    }

    Product get_product(const std::vector<Product>& products, int& code) {
        Product product;
        product.id = 0;

        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].barcode == code) return products[i];
        }

        return product;
    }
};

int main()
{
    std::cout << "Запуск..." << std::endl
              << std::endl;

    std::string cashier;
    std::cout << "Введите ваше имя: ";
    std::cin >> cashier;
    std::cout << std::endl;

    Workplace workplace(cashier);
    workplace.info();

    int command;

    while (true)
    {
        workplace.menu();
        std::cout << std::endl
                  << "Выберите опцию - ";
        std::cin >> command;
        std::cout << std::endl;

        switch (command)
        {
        case 1:
            workplace.sell();
            break;
        case 2:
            workplace.info();
            break;
        case 3:
            std::cout << "Смена закрыта" << std::endl;
            return 0;
        default:
            break;
        }
    }

    return 0;
}