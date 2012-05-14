#include "Column.h"
#include "Console.h"
#include <boost/lexical_cast.hpp>
using namespace std;

Column::Column() {

}

Column::~Column() {

}

void Column::push_back(const string &var) {
	data.push_back(var);
}

void Column::push(int size, luabind::object const& lua_arr) {
	for(int i = 1; i <= size; i ++) {
		// TODO: MUST be a better way to cast objects!!
		try {
			const char* var = luabind::object_cast<const char*>(lua_arr[i]);
			data.push_back(string(var));
		} catch (std::exception&) {
			float var = luabind::object_cast<float>(lua_arr[i]);
			data.push_back(boost::lexical_cast<string>(var));
		}
	}
}

void Column::print() const {
	for(size_t i = 0; i < data.size(); i ++)
		Console::GetSingleton() << wxString(data[i].c_str(), wxConvUTF8) << wxT(" ");
	Console::GetSingleton() << wxT("\n");
}

string Column::at(const int index) const {
	return data[index];
}

unsigned Column::getSize() const {
	return data.size();
}
