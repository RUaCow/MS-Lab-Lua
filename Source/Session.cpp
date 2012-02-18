#include "Session.h"
using namespace std;

void echo(const char str[]) {
	printf("%s%s", str, "\n");
}

void quit() {
	exit(0);
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
			.def("load", &Database::load),
		luabind::def("exit", &quit),
		luabind::def("quit", &quit)
	];
}

Session::~Session() {
	lua_close(state);
}

void Session::doString(const char str[]) {
	if(luaL_dostring(state, str)) {
		cout << "Error: ";
		cout << lua_tostring(state, -1) << endl;
		lua_pop(state, 1);
	}
}

void Session::doFile(const char filename[]) {
	if(luaL_dofile(state, filename)) {
		cout << "Error: ";
		cout << lua_tostring(state, -1) << endl;
		lua_pop(state, 1);
	}
}
