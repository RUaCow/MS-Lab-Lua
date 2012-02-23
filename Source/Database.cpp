#include "Database.h"
#include "Console.h"
using namespace std;

DatabaseIO Database::io = DatabaseIO();

Database::Database() {

}

Database::~Database() {
	clear();
}

Database::Database(const Database &db) {
	for(size_t i = 0; i < db.table.size(); i ++) {
		Column *column = newColumn(db.table[i].first.c_str(), db.table[i].second->type);
		for(size_t j = 0; j < db.table[i].second->data.size(); j ++)
			column->data.push_back(db.table[i].second->data[j]);
	}
}

void Database::operator= (const Database &db) {
	for(size_t i = 0; i < db.table.size(); i ++) {
		Column *column = newColumn(db.table[i].first.c_str(), db.table[i].second->type);
		for(size_t j = 0; j < db.table[i].second->data.size(); j ++)
			column->data.push_back(db.table[i].second->data[j]);
	}
}

void Database::clear() {
	for(size_t i = 0; i < table.size(); i ++)
		delete table[i].second;
	table.clear();
}

Column* Database::newColumn(const char name[], Column::Type type) {
	table.push_back(make_pair(name, new Column(type)));
	return table.back().second;
}

void Database::addColumn(const char name[], Column *column) {
	table.push_back(make_pair(name, column));
}

Database Database::random(int n) const {
	int minC = table[0].second->data.size();
	for(size_t i = 0; i < table.size(); i ++)
		if(table[i].second->data.size() < minC)
			minC = table[i].second->data.size();

	srand(time(0));
	vector<int> nums;
	for(int i = 0; i < n; i ++) {
		bool duplicate = false;
		int tmp = 0;
		do {
			duplicate = false;
			tmp = rand() % minC;
			for(size_t j = 0; j < nums.size(); j ++)
				if(tmp == nums[j])
					duplicate = true;
		} while(duplicate);

		nums.push_back(tmp);
	}
	
	Database result;
	for(size_t i = 0; i < table.size(); i ++) {
		Column *tmp = result.newColumn(table[i].first.c_str(), table[i].second->type);
		for(int j = 0; j < nums.size(); j ++)
			tmp->data.push_back(table[i].second->data[nums[j]]);
	}
	return result;
}

void Database::print() const {
	for(size_t i = 0; i < table.size(); i ++) {
		Console::GetSingleton() << wxString(table[i].first.c_str(), wxConvUTF8) << wxT(": ");
		table[i].second->print();
	}
}

void Database::save(const char filename[]) const {
	io.saveText(filename, this);
}

void Database::load(const char filename[]) {
	io.loadText(filename, this);
}
