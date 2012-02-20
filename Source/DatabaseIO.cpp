#include "DatabaseIO.h"
#include "Database.h"

DatabaseIO::DatabaseIO() {

}

DatabaseIO::~DatabaseIO() {

}

void DatabaseIO::saveText(const char filename[], const Database *db) const {
	/*FILE *output = fopen(filename, "wb");
	if(!output)
		return;

	for(size_t i = 0; i < db->table.size(); i ++) {
		fprintf(output, "%s%s%d%s", db->table[i].name, " ", db->table[i].data.size(), " ");
		for(size_t j = 0; j < db->table[i].data.size(); j ++)
			fprintf(output, "%s%s", db->table[i].data[j].toString(), " ");
	}

	fclose(output);*/
}

void DatabaseIO::loadText(const char filename[], Database *db) const {
	/*db->clear();

	FILE *input = fopen(filename, "rb");

	fseek(input, 0, SEEK_END);
	int size = ftell(input);
	fseek(input, 0, SEEK_SET);

	while(ftell(input) < size) {
		char name[MAX_STR_LEN] = {0};
		int length = 0;
		fscanf(input, "%s%d", name, &length);

		Column &column = db->newColumn(name, Column::VAR_STRING);

		for(int i = 0; i < length; i ++) {
			char var[MAX_STR_LEN] = {0};
			fscanf(input, "%s", var);
			column.push_back(Variable(var));
		}
	}

	fclose(input);*/
}

void DatabaseIO::saveEncrypted(const char filename[], const Database *db) const {
	/*FILE* tfile = fopen(filename , "w");
	for(size_t i = 0; i < db->table.size(); i ++) {
		fprintf(tfile , "%s" , db->table[i]->name);
		fprintf(tfile , "%s%d" , " " , !db->table[i]->isString());
		for(size_t j = 0 ; j < db->table[i]->data.size() ; j ++){
			if(!db->table[i]->isString())
				fprintf(tfile , "%s%s" , " " , /*strf2str(it->second.getNode(i)).c_str() "");
			else
				fprintf(tfile , "%s%s" , " " , db->table[i]->data[j].toString());
		}
		fputc('\n' , tfile);
	}
	fclose(tfile);*/
}
