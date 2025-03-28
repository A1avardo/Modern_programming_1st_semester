#include "menu_functions.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

 const MVlad::MenuItem* MVlad::exit(const MenuItem* current) {
	std::exit(0);
}


const MVlad:: MenuItem* MVlad::show_menu(const MenuItem* current) {
    int level = get_level(current);

    switch (level) {
    case 0:
        std::cout << "Главное меню\n";
        break;
    case 1:
        std::cout << "Второй уровень меню\n";
        break;
    case 2:
        std::cout << "Третий уровень Дальний Восток\n";
        break;
    default:
        break;
    }


    for (int i = 1; i < current->children_count; ++i) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "> ";

    int user_input;
    std::cin >> user_input;
    return current->children[user_input];
}


 const MVlad:: MenuItem* MVlad::travel_dv(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current ->parent;

}
 const MVlad:: MenuItem* MVlad::travel_sib(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current -> parent;
}
 const MVlad:: MenuItem* MVlad::travel_goldr(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current -> parent;

}
 const MVlad::MenuItem*  MVlad::travel_go_back(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current->parent->parent;

}



 const MVlad::MenuItem* MVlad::travel_dv1(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current->parent;

 }
 const MVlad::MenuItem* MVlad::travel_dv2(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current->parent;
 }
 const MVlad::MenuItem* MVlad::travel_dv3(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current->parent;
 }

 const MVlad::MenuItem* MVlad::travel_dv_exit(const MenuItem* current) {
     std::cout << current->title << std::endl;
     return current->parent->parent;
 }

 int MVlad::get_level(const MVlad::MenuItem* current) {
         int level = 0;
         while (current->parent != nullptr) {
             ++level;
             current = current->parent;
         }
         return level;
 }
