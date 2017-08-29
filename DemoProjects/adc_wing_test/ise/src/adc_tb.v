`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:21:04 08/29/2017
// Design Name:   adc_spi_top
// Module Name:   D:/Projects/Posedge/DemoProjects/adc/adc_demo_hdl/adc_tb.v
// Project Name:  adc_demo_hdl
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: adc_spi_top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module adc_tb;

	// Inputs
	reg CLK_IN1;
	reg RESET_N;
	reg miso_pad_i;
	reg [7:0] sw_in;

	// Outputs
	wire mosi_pad_o;
	wire sclk_pad_o;
	wire [3:0] an;
	wire [7:0] leds;
	wire [7:0] ss_pad_o;
	wire [7:0] sseg;

	// Instantiate the Unit Under Test (UUT)
	adc_spi_top uut (
		.CLK_IN1(CLK_IN1), 
		.RESET_N(RESET_N), 
		.miso_pad_i(miso_pad_i), 
		.sw_in(sw_in), 
		.mosi_pad_o(mosi_pad_o), 
		.sclk_pad_o(sclk_pad_o), 
		.an(an), 
		.leds(leds), 
		.ss_pad_o(ss_pad_o), 
		.sseg(sseg)
	);

	initial begin
		// Initialize Inputs
		CLK_IN1 = 0;
		RESET_N = 0;
		miso_pad_i = 0;
		sw_in = 2;

		// Wait 100 ns for global reset to finish
		#100;
		RESET_N = 1;
		#1000
		sw_in = 2;
		#1000
      sw_in = 5;
		#1000
		sw_in = 6;
		// Add stimulus here

	end
	
	always #5 CLK_IN1 = ~CLK_IN1;
      
endmodule

