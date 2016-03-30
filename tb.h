#include "systemc.h"
SC_MODULE(tb){
	//clock, input and reset
	sc_in<bool> 		clk;
	sc_out<bool> 		rst;
	sc_out< sc_int<16> >	inp;
	//handshaked input validation and ready
	sc_out< bool >		inp_vld;
	sc_out< bool >		inp_rdy;
	
	//output port
	sc_in< sc_int<16> >     outp;
	//handshaked validation and ready
	sc_in< bool > 		outp_vld;
	sc_in< bool >		outp_rdy;

	void source();
	void sink();

	FILE *outfp; //points to the stream buffer the location in it.
	sc_time start_time[64], end_time[64], clk_period;	


	SC_CTOR(tb) {
		SC_CTHREAD ( source, clk.pos() );
		SC_CTHREAD ( sink, clk.pos() );
	}
	
}
