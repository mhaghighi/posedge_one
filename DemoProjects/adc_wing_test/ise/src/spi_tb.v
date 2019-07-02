`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   09:32:48 11/05/2016
// Design Name:   spi
// Module Name:   C:/Users/Mahdi/Desktop/adc-spi/rtl/spi_tb.v
// Project Name:  adc-spi
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: spi
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module spi_tb;

	// Inputs
	reg clk;
	reg rst;
	reg miso;
	reg start;
	reg [15:0] data_in;

	// Outputs
	wire mosi;
	wire sck;
	wire ss;
	wire [15:0] data_out;
	wire busy;
	wire new_data;

	// Instantiate the Unit Under Test (UUT)
	spi uut (
		.clk(clk), 
		.rst(rst), 
		.miso(miso), 
		.mosi(mosi), 
		.sck(sck), 
		.ss(ss), 
		.start(start), 
		.data_in(data_in), 
		.data_out(data_out), 
		.busy(busy), 
		.new_data(new_data)
	);
	
	always begin
		clk = 1'b0;
		#10 clk = 1'b1;
		#10;
	end

	initial begin
		// Initialize Inputs
		rst = 1;
		miso = 0;
		start = 0;
		data_in = 16'h1234;

		// Wait 100 ns for global reset to finish
		#100;
		rst = 1'b0;
		#100;
		start = 1'b1;
		#20;
		start = 1'b0;
        
		// Add stimulus here

	end
      
endmodule

