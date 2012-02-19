#include "Session.h"
#include "Console.h"
using namespace std;

void echo(const char str[]) {
	Console::GetSingleton() << wxString(str, wxConvUTF8) << wxT("\n");
}

Session::Session() {
	state = lua_open();
	luabind::open(state);

	// Bind functions and classes to Lua
	luabind::module(state) [
		luabind::def("echo", &echo),
		
		luabind::class_<Variable>("Variable")
		.enum_("Type") [
			luabind::value("string", 0),
			luabind::value("integer", 1),
			luabind::value("real", 2)
		],
		luabind::class_<Column>("Column")
			.def(luabind::constructor<const char*, Column::Type>())
			.def("set", &Column::setByArray)
			.def("print", &Column::print),

		luabind::class_<Database>("Database")
			.def(luabind::constructor<>())
			.def("new", &Database::newColumn)
			.def("rand", &Database::random)
			.def("print", &Database::print)
			.def("save", &Database::save)
			.def("load", &Database::load)
	];
}

Session::~Session() {
	lua_close(state);
}

void Session::doString(const char str[]) {
	if(luaL_dostring(state, str)) {
		Console::GetSingleton() << wxT("Error: ");
		Console::GetSingleton() << wxString(lua_tostring(state, -1), wxConvUTF8) << wxT("\n");
		lua_pop(state, 1);
	}
}

void Session::doFile(const char filename[]) {
	if(luaL_dofile(state, filename)) {
		Console::GetSingleton() << wxT("Error: ");
		Console::GetSingleton() << wxString(lua_tostring(state, -1), wxConvUTF8) << wxT("\n");
		lua_pop(state, 1);
	}
}
