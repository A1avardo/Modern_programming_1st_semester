#pragma once
#include "menu.hpp"
#include <string>
namespace MVlad {
	const MenuItem* exit(const MenuItem* current);
	const MenuItem* show_menu(const MenuItem* current);


	const MenuItem* travel_dv(const MenuItem* current);
	const MenuItem* travel_sib(const MenuItem* current);
	const MenuItem* travel_goldr(const MenuItem* current);
	const MenuItem* travel_go_back(const MenuItem* current);

	const MenuItem* travel_dv1(const MenuItem* currentt);
	const MenuItem* travel_dv2(const MenuItem* currentt);
	const MenuItem* travel_dv3(const MenuItem* currentt);
	const MenuItem* travel_dv_exit(const MenuItem* currentt);


	int get_level(const MVlad::MenuItem* current);



}