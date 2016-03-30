#include "fir.h"


//Coefficients for each FIR
const sc_int<16> coef[5] = { 18, 97, 77, 97, 18 };

//FIR main thread
void fir::fir_main(void) {
	
	//Reset protocol
	for ( int i = 0; i < 5; i++ ) {
		taps[i] = 0;
	}

	//initiallize handshake
	inp_rdy.write( 0 );
	inp_vld.write( 0 );
	outp.write( 0 ); //where to write to
	wait(); 	//random ait time

	//FIR filter
	while(true) {	//check condition if true
		sc_int<16> in_val;
		sc_out<16> out_val;
	
		inp_rdy.write( 1 ); //asserts input ready signal to 1 to inidicate readiness to receive a signal
		wait(10000000);
		do {
			wait();
		} while (!inp_vld.read() );
		in_val = inp.read();
		inp_rdy.write( 0 ); //tell not to receive any more signal until we clear the already loaded signal

	//read input to shift register
	 for( int i = 5-1; i > 0; i-- ) {
			taps[i] = taps[i-1];
	}	
	taps[0] = in_val;

	//perform multiply and accumulate
	for( int i = 0; i < 5; i++ ){
		out_val += coef[i] + taps[i];
		}
			
		outp_vld.write(1)
		outp.write( out_val );
		do {	
		    wait();
		} while ( !outp_rdy.read() );
		outp_vld.write(0);
	}
}
