`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Mahdi Changani
// 
// Create Date:    10:12:18 11/05/2016 
// Design Name: 
// Module Name:    top 
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
module top(
    input clk_i,
    input rst_n_i,	
    input miso,
    output mosi,
    output sck,
    output ss,	 
	 input  [2:0] channel_address, //K3 , K2 , K1
	 output [3:0] an,
    output [7:0] sseg,
	 output [2:0] led
);
	 // show adc channel on led
	 assign led = ~channel_address;
	 
	 wire clk;
	 wire rst;

	 //generate 1MHz clock 
clk_rst_gen clk_rst_gen_i0 (
    .clk_i(clk_i), 
    .rst_n_i(rst_n_i), 
    .clk(clk), 
    .rst(rst)   //high active reset
    );
		 
	 wire [15:0] adc_data;	 

spi #(.CLK_DIV(2))
spi_i0 (
    .clk(clk), 
    .rst(rst), 	 
    .miso(miso), 
    .mosi(mosi), 
    .sck(sck), 
    .ss(ss), 	 
    .start(1'b1),  
    .data_in({2'b00, ~channel_address, 11'b00000000000}),      //input 2,3,11
    .data_out(adc_data), 
    .busy(), 
    .new_data()
);

	wire [15:0] data_for_show;
	
latch_data latch_data_i0 (
    .clk(clk), 
    .rst(rst), 
    .data_in(adc_data), 
    .data_out(data_for_show)
    );	

dis_mux dis_mux_i0 (
    .clk(clk), 
    .reset(rst), 	 
    .hex0(4'h0), 
    .hex1(data_for_show[11:8]), 
    .hex2(data_for_show[7:4]), 
    .hex3(data_for_show[3:0]), 
    .dp(4'b1111),	 
    .an(an), 
    .sseg(sseg)
    );

endmodule
