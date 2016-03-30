#include "tb.h"

void tb::source() {
	
	sc_int<16> tmp;	

	//Reset
	inp.write( 0 ); 		//clocked signal
	inp_vld.write( 0 ); 		//handshake signal
	rst.write( 1 );
	wait();
	rst.write( 0 );
	wait(); 
	

	//send stimulus to DUT
	for( int i = 0; i < 64; i++) {

		if ( i > 23 && i < 29 )	
			tmp = 256;
		else
			tmp = 0;
		inp_vld.write( 1 )	//asserting the input valid signal
		inp.write( tmp );
		 	
		do{
		   wait();
			while( !inp_rdy.read() );
			inp_vld.write( 0 );
			start_time[i] = sc_time_stamp(); // use array index at i array all 64 start times
		}
		//Handing simulation guard condition
		wait(10000);
		printf( "Hanging simulation stopped by TB source thread. Please check DUT module. \n" );
	sc_stop();
}

void tb::sink() {
	sc_int<16> indata;

	//Extract clock period
	sc_clock *clk_p = DCAST<sc_clock*>(clk.get_interface());
	clock_period = clk_p->period();	

	//determine whether the simulation passed or failed.
	char out_put_file[256];
	sprintf( output_file,"./output.dat");
	outfp = fopen( output_file, "wb" );
	if( outfp == NULL ){
		printf("could not open output.dat for writing. \n");
		exit(0);
	}
	//initialize port
	outp_rdy.write(0);

	double total_cycles = 0;
	
	//Read output coming from  DUT
	for( int i = 0; i < 64; i++) {
	
	outp_rdy.write(1);
        do { //wait until we have valid output from the fir module
                wait();
        } while (!outp_vld.read());
                indata = outp.read();
		end_time[i] = sc_time_stamp();
		total_cycles += (end_time[i] - start_time[i]) / clock_period; //add latency calculation to the total_cycles
		outp_rdy.write( 0 );

		fprintf( outfp, "%d\n", (int)indata );
		cout<< i << " :\t" << indata.to_double() << endl;
	}
	//print throughput
	double total_throughput = ( start_time[63] - start_time[0] )/ clock_period;	
	printf ( "Average throughput is %g cycles per input. \n" (double)(total_throughput/63)) ; 
	//print latency
	printf ( "Average Latency is %g cycles.\n", (double)(total_cycles/64) );
}//End the simulation
fclose(outfp);
sc_stop();
