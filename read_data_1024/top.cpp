#include"top.h"

/*
 * input: size = (length, width(bits))
 * output: size = (length, width(bits))
 */
void DoCompute(data_bus *input, data_bus *output, int length){
#pragma HLS INTERFACE s_axilite port=length
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE m_axi depth=2048 port=output offset=slave bundle=OUTPUT
#pragma HLS INTERFACE m_axi depth=2048 port=input offset=slave bundle=INPUT

	data_t buffer[MAX_LENGTH*(EXTERNAL_DATA_WIDTH/INTERNAL_DATA_WIDTH)][INTERNAL_DATA_WIDTH/PREC];
#pragma HLS ARRAY_PARTITION variable=buffer complete dim=2

	int ptr = 0;
	data_bus temp;
	for(int i = 0; i < length; i++){
#pragma HLS LOOP_TRIPCOUNT min=100 max=100 avg=100

#pragma HLS PIPELINE

		temp = input[i];
		for(int j = 0; j < EXTERNAL_DATA_WIDTH/INTERNAL_DATA_WIDTH; j++){

			for(int k = 0; k < INTERNAL_DATA_WIDTH/PREC; k++){
#pragma HLS UNROLL
				buffer[ptr+j][k] = temp.range((k+1)*PREC-1, k*PREC);
			}

			temp = temp >> INTERNAL_DATA_WIDTH;
		}
		ptr+=EXTERNAL_DATA_WIDTH/INTERNAL_DATA_WIDTH;

	}

	ptr = 0;
	for(int i = 0; i < length; i++){
#pragma HLS LOOP_TRIPCOUNT min=100 max=100 avg=100
#pragma HLS PIPELINE
		for(int j = EXTERNAL_DATA_WIDTH/INTERNAL_DATA_WIDTH-1; j >=0 ; j--){

			temp = temp << INTERNAL_DATA_WIDTH;

			for(int k = 0; k < INTERNAL_DATA_WIDTH/PREC; k++){
#pragma HLS UNROLL
				temp.range((k+1)*PREC-1, k*PREC) = buffer[ptr+j][k];
			}
		}
		ptr+=EXTERNAL_DATA_WIDTH/INTERNAL_DATA_WIDTH;
		output[i] = temp;
	}
	return;
}
