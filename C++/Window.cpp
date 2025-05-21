#include "Window.hpp"

#include <cstdlib>

/* ====================
        Window
==================== */
Window::Window(const std::string& title, const std::vector<std::string>& options) : title(title), options_vect(options) {}

void Window::showTitle() {
    std::cout << "================================================================\n\t"
              << this->title << std::endl
              << "================================================================" << std::endl;
}

/* ====================
        WindowInfo
==================== */
WindowInfo::WindowInfo(const std::string& title, const std::vector<std::string>& options) : Window(title, options) {}

void WindowInfo::show() {
    std::string c;
    this->showTitle();
    this->printOptions();
    std::cout << std::endl << "APPUYER SUR UNE TOUCHE + ENTER POUR QUITTER";
    std::cin >> c;

    std::system("clear");
}

void WindowInfo::printOptions() const {
    for (const auto& value : this->options_vect) {
        std::cout << value << std::endl << std::endl;
    }
}

/* ====================
        WindowMenu
==================== */
WindowMenu::WindowMenu(const std::string& title, const std::vector<std::string>& options) : Window(title, options), choice(0) {}

void WindowMenu::show() {

    this->showTitle();
    this->printOptions();

    do {
        std::cout << "Entrer votre choix : ";
        std::cin >> this->choice;

    } while (this->choice > this->options_vect.size() + 1 || this->choice < 1);
        
    std::system("clear");
}

void WindowMenu::printOptions() const {
    int i = 1;
    for (const auto& value : this->options_vect) {
        std::cout << i++ << ") " << value << std::endl;
    }
    std::cout << i << ") Quitter." << std::endl;
}

int WindowMenu::getChoice() const {
    return this->choice;
}

/* ====================
        WindowForm
==================== */
WindowForm::WindowForm(const std::string& title, const std::vector<std::string>& options) : Window(title, options) {}

void WindowForm::show() {
    this->showTitle();
    this->printOptions();

    std::system("clear");
}

void WindowForm::printOptions() {
    std::string line;

    std::cin.ignore(); // vider le buffer

    for (const auto& value : this->options_vect) {
        std::cout << value << " : ";
        std::getline(std::cin, line);
        this->answer_dict[value] = line;
    }
}

const std::unordered_map<std::string, std::string>& WindowForm::getAnswer() const {
    return this->answer_dict;
}
