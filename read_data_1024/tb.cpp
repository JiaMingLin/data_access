#include"top.h"

data_t** generateData(int length, int width, bool initZero){
	data_t** arr = new data_t*[length];
	for(int i = 0; i < length; i++){
		arr[i] = new data_t[width];
	}

	for(int i = 0; i < length; i++){
		for(int j= 0; j < width; j++){
			if(initZero){
				arr[i][j] = 0;
			}else{
				arr[i][j] = i * width + j;
			}
		}
	}
	return arr;
}

int main(){

	int error = 0;
	// input buffer
	data_t **A = generateData(TEST_LENGTH, EXTERNAL_DATA_WIDTH/PREC, false);

	// output buffer
	data_t **B = generateData(TEST_LENGTH, EXTERNAL_DATA_WIDTH/PREC, true);

	data_bus *BufferA = new data_bus[TEST_LENGTH];
	data_bus *BufferB = new data_bus[TEST_LENGTH];

	// convert A to buffer
	for(int i = 0; i < TEST_LENGTH; i++){
		for(int j = 0; j < EXTERNAL_DATA_WIDTH/PREC; j++){
			BufferA[i].range((j+1)*PREC-1, j*PREC) = A[i][j];
		}
	}

	// to hardware
	DoCompute(BufferA, BufferB, TEST_LENGTH);

	// convert buffer to raw data
	for(int i = 0; i < TEST_LENGTH; i++){
		for(int j = 0; j < EXTERNAL_DATA_WIDTH/PREC; j++){
			B[i][j] = BufferB[i].range((j+1)*PREC-1, j*PREC);
		}
	}

	// compare results

	for(int i = 0; i < TEST_LENGTH; i++){
		for(int j = 0; j < EXTERNAL_DATA_WIDTH/PREC; j++){
			if(A[i][j] != B[i][j]) error++;

		}
	}

	return error;
}
