#include "Database.h"
using namespace std;

DatabaseIO Database::io = DatabaseIO();

Database::Database() {

}

Database::~Database() {
	clear();
}

void Database::clear() {
	for(size_t i = 0; i < table.size(); i ++)
		delete table[i];
	table.clear();
}

Column* Database::newColumn(const char name[], Column::Type type) {
	table.push_back(new Column(name, type));
	return table.back();
}

void Database::addColumn(Column *column) {
	table.push_back(column);
}

Database* Database::random(int n) const {
	srand(time(0));
	vector<int> nums;
	for(int i = 0; i < n; i ++) {
		bool duplicate = false;
		int tmp = 0;
		do {
			duplicate = false;
			tmp = rand() % n;
			for(size_t j = 0; j < nums.size(); j ++)
				if(tmp == nums[j])
					duplicate = true;
		} while(duplicate);

		nums.push_back(tmp);
	}
	
	Database *result = new Database();
	for(size_t i = 0; i < table.size(); i ++) {
		Column *tmp = result->newColumn(table[i]->name, table[i]->type);
		for(int j = 0; j < n; j ++)
			tmp->data.push_back(table[i]->data[nums[j]]);
	}

	return result;
}

void Database::print() const {
	for(size_t i = 0; i < table.size(); i ++)
		table[i]->print();
}

void Database::save(const char filename[]) const {
	io.saveText(filename, this);
}

void Database::load(const char filename[]) {
	io.loadText(filename, this);
}
