/*
 * A test n the filter module with single input to a single output
 * @param : this si a verification 
 * @param : date - 24, 03 2016
 * @param : Hierarchical structure testbenche
 * @Param : author - forturne_five you tube testbench example
 */

#include<systemc.h>		//systemc api libraries
#include "fir.h"   		//intance of FIR module
#include "tb.h"			//instance of testbench module

SC_MODULE( SYSTEM ) {
	tb	*tb0; //the test mudules
	fir	*fir0;
	
	sc_signal< sc_int<16> >	inp_sig;	//the input signal
	sc_signal< sc_int<16> > inp_sig_vld;	//ensure that the input signal is valid
	sc_signal< sc_int<16> >inp_sig_rdy;	//check and ensure the input is alway ready to send a signal 

	sc_signal< sc_int<16> > outp_sig;	//output singal
	sc_signal< sc_int<16> > outp_sig_vld; 	//validates output signal coming for inp_sig_vld
	sc_signal< sc_int<16> > out_sig_rdy;	//ensure the ports are ready for output at any time

	sc_signal< bool >       rst_sig;	
	sc_clock clk_sig;
	
	SC_CTOR( SYSTEM )
		:clk_sig ( "clk_sig", 10, SC_NS )
		
	//the testbench clocked signals
	tb0 = new tb("tb0");
	tb0->clk ( clk_sig );	
	tb0->rst ( rst_sig );
	
	
/* TESTBENCH module
 * This is the testbench module that runs the input and outputs with clocked signal.
 * This is also the test bench module that runs the input and output validation and
 * ready signals for validation
 *
 */ 
	//the input signal from testbench with clock
	tb0->inp ( inp_sig );
	//our input signals for handshaking (validation and readying)
	tb0->inp_vld ( inp_sig_vld );
	tb0->inp_rdy (inp_sig_ready );

	//the output signal from the testbech module with clock
	tb0->output (outp_sig );
	//the output signal from fir module for handshaking
	tb0->outp_sig ( outp_sig_vld );
	tb0-outp_sig ( outp_sig_rdy );

/* FIR module
 * This is the fir module that runs the input and outputs with clocked signal.
 * This is also the fir module that runs the input and output validation and
 * ready signals for validation    
 */ 
	
	//the fir module clock signals
	fir0 = new fir( "fir0" );
	fir0->clk ( clk_sig );
	fir0->rst ( rst_sig );
	
	//input signal with the clock	
	fir0->inp (inp_sig );
	//input fir module validation and ready signal
	fir0->inp_vld (inp_sig_vld );
	fir0->inp_rdy ( inp_sig_rdy );

	//output signal with the clock
	fir0->outp (outp_sig );
	//output fir module validation and ready signal
	fir0->outp_sig ( outp_sig_vld );
	fir0->outp_sig ( outp_sig_rdy );

	SC_CTOR( SYSTEM ){
		~SYSTEM() {
		delete tb0;
		delete fir0;	
	SYSTEM *top = NULL;

	int sc_main( int argc, char* argv[] ){
		
		top = new SYSTE ( "top");
		sc_start();
		return 0;
	}
	}
};
