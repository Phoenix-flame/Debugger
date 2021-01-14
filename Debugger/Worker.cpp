#include "Worker.h"

Ref<FIFO<std::vector<Variables>>> Worker::s_Fifo;
std::map<std::string, float> Worker::s_FloatVars;