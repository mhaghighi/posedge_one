`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:18:04 11/11/2015 
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
		input  wire clk_i, rst_n_i,
		output wire hsync, vsync,
		output wire [5:0] rgb,
		
		output [7:0] sseg,
      output [0:3] an,

		input  [7:0] dip_switch,
		input  [3:0] push_button,
		output [7:0] leds	
    );

	 wire clk_50MHz;
	 wire	rst;
	 
	 reg [3:0] hex0;
	 reg [3:0] hex1;
	 reg [3:0] hex2;
	 reg [3:0] hex3;
	 
	 wire [3:0] dp;
	
	assign leds = ~dip_switch;
	assign dp   = dip_switch[7:4];
	


clk_rst_gen clk_rst_gen_i0 (
    .clk_i(clk_i), 
    .rst_n_i(rst_n_i), 
    .clk(clk_50MHz), 
    .rst(rst)
    );

always @ (posedge clk_50MHz)
begin
	if(push_button[0]==0)
		hex0 = ~dip_switch[3:0];		
	if(push_button[1]==0)
		hex1 = ~dip_switch[3:0];		
	if(push_button[2]==0)
		hex2 = ~dip_switch[3:0];		
	if(push_button[3]==0)
		hex3 = ~dip_switch[3:0];	
end	

	
 	 
dis_mux dis_mux_i0 (
    .clk(clk_50MHz), 
    .reset(rst), 
    .hex0(hex0), 
    .hex1(hex1), 
    .hex2(hex2), 
    .hex3(hex3), 
    .dp(dp), 
    .an(an), 
    .sseg(sseg)
    );
	 
vga vga_i0 (
    .clk_50MHz(clk_50MHz), 
    .rst(rst), 
    .hsync(hsync), 
    .vsync(vsync), 
    .rgb(rgb)
    );

endmodule
