#include "Session.h"
#include "Console.h"
using namespace std;

void echo(const char str[]) {
	Console::GetSingleton() << wxString(str, wxConvUTF8) << wxT("\n");
}

Session::Session() {
	start();
}

Session::~Session() {
	close();
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

void Session::start() {
	state = lua_open();
	luabind::open(state);

	// Bind functions and classes to Lua
	luabind::module(state) [
		luabind::def("echo", &echo),
		
		luabind::class_<Column>("Column")
			.def(luabind::constructor<>())
			.def("push", &Column::push)
			.def("print", &Column::print),

		luabind::class_<Database>("Database")
			.def(luabind::constructor<>())
			.def("new", &Database::newColumn)
			.def("print", &Database::print)
			.def("rand", &Database::random)
			.def("save", &Database::save)
			.def("load", &Database::load)
			.def("pie", &Database::drawPie)
	];
}

void Session::close() {
	lua_close(state);
}
