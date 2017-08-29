`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:30:17 09/06/2015
// Design Name:   clk_rst_gen
// Module Name:   D:/Desktop/clk_rst_gen/hw/rtl/clk_rst_gen_tb.v
// Project Name:  clk_rst_gen
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: clk_rst_gen
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module clk_rst_gen_tb;

	// Inputs
	reg clk_i;
	reg rst_n_i;

	// Outputs
	wire clk;
	wire rst;

	// Instantiate the Unit Under Test (UUT)
	clk_rst_gen uut (
		.clk_i(clk_i), 
		.rst_n_i(rst_n_i), 
		.clk(clk), 
		.rst(rst)
	);
	

	always begin
		clk_i = 0;
		#40;
		clk_i = 1;
		#40;	
	end

	initial begin
		// Initialize Inputs
		rst_n_i = 0;

		// Wait 100 ns for global reset to finish
		#100;
		rst_n_i = 1;
        
		// Add stimulus here

	end
      
endmodule

