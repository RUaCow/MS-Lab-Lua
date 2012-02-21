#include "Variable.h"

Variable::Variable() {
	clean();
}

Variable::Variable(const char value[]) {
	clean();
	strcpy(ptr, value);
}

Variable::Variable(int value) {
	clean();
	sprintf(ptr, "%d", value);
}

Variable::Variable(float value) {
	clean();
	sprintf(ptr, "%f", value);
}

Variable::~Variable() {

}

void Variable::clean() {
	for(int i = 0; i < MAX_STR_LEN; i ++)
		ptr[i] = 0;
}

const char* Variable::toString() const {
	return ptr;
}

int Variable::toInteger() const {
	return strtol(ptr, NULL, 10);
}

float Variable::toReal() const {
	return (float)strtod(ptr, NULL);
}
