#include <iostream>
#include <ap_int.h>

using namespace std;

#define TEST_LENGTH 2048

#define MAX_LENGTH 5120
#define EXTERNAL_DATA_WIDTH 512
#define	INTERNAL_DATA_WIDTH 512
#define PREC 8

typedef ap_uint<PREC> data_t;
typedef ap_uint<EXTERNAL_DATA_WIDTH> data_bus;

void DoCompute(data_bus *input, data_bus *output, int length);
