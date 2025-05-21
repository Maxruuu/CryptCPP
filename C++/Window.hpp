#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

/* ====================
    Class abstract
==================== */
class Window {
protected:
    std::string title;
    std::vector<std::string> options_vect;

public:
    Window(const std::string& title, const std::vector<std::string>& options);

    virtual void show() = 0;
    virtual void showTitle();
};

/* ====================
        Class
==================== */
class WindowInfo : public Window {
public:
    WindowInfo(const std::string& title, const std::vector<std::string>& options);

    void show() override;
    void printOptions() const;
};

class WindowMenu : public Window {
private:
    int choice;

public:
    WindowMenu(const std::string& title, const std::vector<std::string>& options);

    void show() override;
    void printOptions() const;
    int getChoice() const;
};

class WindowForm : public Window {
private:
    std::unordered_map<std::string, std::string> answer_dict;

public:
    WindowForm(const std::string& title, const std::vector<std::string>& options);

    void show() override;
    void printOptions();
    const std::unordered_map<std::string, std::string>& getAnswer() const;
};

#endif