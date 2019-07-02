`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:34:17 08/14/2015
// Design Name:   vga_sync
// Module Name:   C:/Users/Mahdi/Desktop/vga/hw/rtl/vga_sync_tb.v
// Project Name:  vga
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: vga_sync
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module vga_sync_tb;

	// Inputs
	reg clk;
	reg reset;

	// Outputs
	wire hsync;
	wire vsync;
	wire video_on;
	wire p_tick;
	wire [9:0] pixel_x;
	wire [9:0] pixel_y;

	// Instantiate the Unit Under Test (UUT)
	vga_sync uut (
		.clk(clk), 
		.reset(reset), 
		.hsync(hsync), 
		.vsync(vsync), 
		.video_on(video_on), 
		.p_tick(p_tick), 
		.pixel_x(pixel_x), 
		.pixel_y(pixel_y)
	);
	
	//parameter PERIOD = 42; //41.66ns -> 24 Mhz
	parameter PERIOD = 20;
   initial begin
      clk = 1'b0;
      #(PERIOD/2);
      forever
         #(PERIOD/2) clk = ~clk;
   end

	initial begin
		// Initialize Inputs
		reset = 1;

		// Wait 100 ns for global reset to finish
		#100;
		reset = 0;
        
		// Add stimulus here

	end
      
endmodule

