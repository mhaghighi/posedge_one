`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:54:28 08/20/2017
// Design Name:   top
// Module Name:   D:/Projects/Posedge/DemoProjects/uart2fifo/uart-rx_to_tx_ise/top_tb.v
// Project Name:  rx_to_tx
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module top_tb;

	// Inputs
	reg clk_in;
	reg rst_n;
	reg rxd;

	// Outputs
	wire txd;
	reg [7:0] data = 8'hAB;
	reg [9:0] uart_frame;
	
	parameter bit_time = 104000; // nanoseconds @ 9600 bps

	// Instantiate the Unit Under Test (UUT)
	top uut (
		.clk_in(clk_in), 
		.rst_n(rst_n), 
		.txd(txd), 
		.rxd(rxd)
	);

	initial begin
		// Initialize Inputs
		clk_in = 0;
		rst_n = 0;
		rxd = 1'b1;
		#1000
		rst_n = 1;
		#100000
		repeat(5) begin					
			// construct the whole frame with start and stop bit
			//            STOP  data  START
			uart_frame = {1'b1, data, 1'b0};
			repeat (10)     // number of bit-symbols to send
			begin
				rxd = uart_frame[0];   // drive line to correct level
				uart_frame = uart_frame >> 1;  // prepare next bit
				#(bit_time);            // hold output for one bit time
			end
		end
	end	
	
	
	always #20 clk_in = ~clk_in;
	      
endmodule

