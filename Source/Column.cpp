#include "Column.h"
#include "Console.h"
using namespace std;

Column::Column(const char name[], Type type) : type(type) {
	strcpy(this->name, name);
}

Column::~Column() {

}

void Column::push_back(const Variable &var) {
	data.push_back(var);
}

void Column::push(int size, luabind::object const& lua_arr) {
	for(int i = 1; i <= size; i ++)
		if(type == VAR_STRING) {
			const char* var = luabind::object_cast<const char*>(lua_arr[i]);
			data.push_back(Variable(var));
		} else if(type == VAR_INTEGER) {
			int var = luabind::object_cast<int>(lua_arr[i]);
			data.push_back(Variable(var));
		} else if(type == VAR_REAL) {
			float var = luabind::object_cast<float>(lua_arr[i]);
			data.push_back(Variable(var));
		}
}

bool Column::isString() const {
	return (type == VAR_STRING);
}

bool Column::isInteger() const {
	return (type == VAR_INTEGER);
}

bool Column::isReal() const {
	return (type == VAR_REAL);
}

void Column::print() const {
	Console::GetSingleton() << wxString(name, wxConvUTF8) << wxT(": ");
	for(size_t i = 0; i < data.size(); i ++)
		Console::GetSingleton() << wxString(data[i].toString(), wxConvUTF8) << wxT(" ");
	Console::GetSingleton() << wxT("\n");
}
