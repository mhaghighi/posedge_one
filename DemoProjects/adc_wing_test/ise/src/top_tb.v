`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:14:56 11/05/2016
// Design Name:   top
// Module Name:   C:/Users/Mahdi/Desktop/adc-spi/rtl/top_tb.v
// Project Name:  adc-spi
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
	reg clk_i;
	reg rst_n_i;
	reg miso;

	// Outputs
	wire mosi;
	wire sck;
	wire ss;

	// Instantiate the Unit Under Test (UUT)
	top uut (
		.clk_i(clk_i), 
		.rst_n_i(rst_n_i), 
		.miso(miso), 
		.mosi(mosi), 
		.sck(sck), 
		.ss(ss)
	);
	
	always begin
		clk_i = 1'b0;
		#10 clk_i = 1'b1;
		#10;
	end

	initial begin
		// Initialize Inputs
		rst_n_i = 0;
		miso = 0;

		// Wait 100 ns for global reset to finish
		#100;
		rst_n_i = 1;
        
		// Add stimulus here

	end
      
endmodule

