#include "menu_items.hpp"
#include  <cstddef>
#include "menu_functions.hpp"


const MVlad::MenuItem MVlad::TRAVEl_DV1 = {
	"1 - Владивосток",  MVlad::travel_dv1, &MVlad::TRAVEl_DV
};
const MVlad::MenuItem MVlad::TRAVEl_DV2 = {
	"2 - Сахалин",  MVlad::travel_dv2, &MVlad::TRAVEl_DV
};
const MVlad::MenuItem MVlad::TRAVEl_DV3 = {
	"3 - Хабаровск",  MVlad::travel_dv3, &MVlad::TRAVEl_DV
};
const MVlad::MenuItem MVlad::TRAVEl_DV_EXIT = {
	"0 - Выйти в предудыщее меню",  MVlad::travel_dv_exit, &MVlad::TRAVEl_DV
};

namespace {

		const MVlad::MenuItem* const travel_dv_children[] = {
			&MVlad::TRAVEl_DV_EXIT,
			&MVlad::TRAVEl_DV1,
			&MVlad::TRAVEl_DV2,
			&MVlad::TRAVEl_DV3
		};
		const int travel_dv_size = sizeof(travel_dv_children) / sizeof(travel_dv_children[0]);
	}



const MVlad::MenuItem MVlad::TRAVEl_DV = {
	"1 - Дальний Восток",  MVlad::show_menu, &MVlad::TRAVEl, travel_dv_children, travel_dv_size
};
const MVlad::MenuItem MVlad::TRAVEl_SIB = {
	"2 - Алтай",  MVlad::travel_sib, &MVlad::TRAVEl
};
const MVlad::MenuItem MVlad::TRAVEl_GOLDR= {
	"3 - Золотое Кольцо России",  MVlad::travel_goldr, &MVlad::TRAVEl
};
const MVlad::MenuItem MVlad::TRAVEl_GO_BACK = {
	"0 - Выйти в главвное меню",  MVlad::travel_go_back, &MVlad::TRAVEl
};

namespace {

	const MVlad::MenuItem* const travel_children[] = {
		&MVlad::TRAVEl_GO_BACK,
		&MVlad::TRAVEl_DV,
		&MVlad::TRAVEl_SIB,
		&MVlad::TRAVEl_GOLDR,
		
	};
	   const int travel_size = sizeof(travel_children) / sizeof(travel_children[0]);
}



	const MVlad::MenuItem MVlad::TRAVEl = {
		"1- Путешествовать по России", MVlad::show_menu, &MVlad::MAIN, travel_children, travel_size
	};

	const MVlad::MenuItem MVlad::EXIT = {
		"0 - Закончить путешествие", MVlad::exit, &MVlad::MAIN
	};

	namespace {
		const MVlad::MenuItem* const main_children[] = {
		&MVlad::EXIT,
		&MVlad::TRAVEl
		};
		const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	}



	const MVlad::MenuItem MVlad::MAIN = {
	 nullptr, MVlad::show_menu, nullptr, main_children, main_size
	};