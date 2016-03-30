#include <systemc.h>

SC_MODULE ( fir ){	//start at the module with inputs and clock ports
  sc_in< bool >			clk;		//input, clock and reset
  sc_in< bool >			rst;	
  sc_in< sc_int<16> >		inp;
	//handshakers
	sc_in< bool >		inp_vld;
	sc_in< bool > 		inp_rdy;
	sc_in< bool >		outp_rdy

//output port
  sc_out< sc_int<16> >		outp;
	//handshakers
 	sc_out< bool >		outp_vld;
	sc_out< bool >		outp_rdy;
	

	void fir_main(){ 
	
	f.write( a.read() & b.read() );

	SC_CTOR( fir ){
		SC_METHOD( func ) // sc method thread to clock the void function
	}
}
