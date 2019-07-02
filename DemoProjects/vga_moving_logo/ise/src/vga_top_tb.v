`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:30:45 08/15/2015
// Design Name:   vga_top
// Module Name:   D:/Desktop/005-94.05.23-vga-not-tested/hw/rtl/vga_top_tb.v
// Project Name:  vga
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: vga_top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module vga_top_tb;

	// Inputs
	reg clk_i;
	reg reset_i;

	// Outputs
	wire hsync;
	wire vsync;
	wire [5:0] rgb;

	// Instantiate the Unit Under Test (UUT)
	vga_top uut (
		.clk_i(clk_i), 
		.reset_i(reset_i), 
		.hsync(hsync), 
		.vsync(vsync), 
		.rgb(rgb)
	);
	
   parameter PERIOD = 42; //41.66ns -> 24 Mhz
   initial begin
      clk_i = 1'b0;
      #(PERIOD/2);
      forever
         #(PERIOD/2) clk_i = ~clk_i;
   end

	initial begin
		// Initialize Inputs
		reset_i = 0;

		// Wait 100 ns for global reset to finish
		#100;
		reset_i = 1;
        
		// Add stimulus here

	end
      
endmodule

