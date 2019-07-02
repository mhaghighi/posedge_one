`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:21:32 09/06/2015 
// Design Name: 
// Module Name:    clk_rst_gen 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clk_rst_gen(
    input clk_i,
    input rst_n_i,
    output clk,
    output rst
    );
	 
	 wire LOCKED;

clk_gen clk_gen_i0
   (// Clock in ports
    .CLK_IN1(clk_i),       // IN
    // Clock out ports
    .CLK_OUT1(clk),        // OUT
    // Status and control signals
    .RESET(!rst_n_i),      // IN
    .LOCKED(LOCKED));      // OUT
	 
rst_gen rst_gen_i0 (
    .clk(clk), 
    .rst_i(rst_n_i), 
    .clock_locked(LOCKED), 
    .rst(rst)
    );

endmodule
