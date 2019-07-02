`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:18:10 08/15/2015 
// Design Name: 
// Module Name:    vga_top 
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
module vga(
		input  wire clk_50MHz, rst,
		output wire hsync, vsync,
		output wire [5:0] rgb
    );
	  
	 reg  [5:0] rgb_reg;
	 wire video_on;
	 wire p_tick;
	 
	 wire [9:0] pixel_x;
	 wire [9:0] pixel_y;
	 
	 //reg [7:0] address;
	 wire [7:0] data;
	 reg [15:0] counter;
	 reg [9:0] counter2;
	 reg [9:0] counter3;
	 reg [9:0] counter4;
	 
	 wire vsync_t;
	 
	 assign vsync = vsync_t;
	 
	 assign in_windows = (pixel_x > counter3 && (pixel_x < counter3+201) && pixel_y > counter4 && (pixel_y < counter4+101));
	 //assign in_windows = (pixel_x > counter3 && (pixel_x < counter3+201) && pixel_y > 145 && (pixel_y < 145+101));
	 
vga_sync vga_sync_i0 (
    .clk(clk_50MHz), 
    .reset(rst), 
    .hsync(hsync), 
    .vsync(vsync_t), 
    .video_on(video_on), 
    .p_tick(p_tick), 
    .pixel_x(pixel_x), 
    .pixel_y(pixel_y)
    );

rom rom_i0 (
    .address(counter), 
    .data(data), 
    .read_en(1), 
    .ce(1)
    );

always @ (posedge vsync_t)
begin
	if (rst || counter3 == 600)
		counter3 <= 0;
	else //if (counter2 == 4)
		counter3 <= counter3 + 1;
end 

always @ (posedge vsync_t)
begin
	if (rst || counter4 > 380)
		counter4 <= 0;
	else if (counter3 == 599)
		counter4 <= counter4 + 50;
end
	 	
always @ (posedge p_tick)
begin
	if (rst || vsync_t)
		counter <= 0;
	else
	begin
		if(in_windows)
			counter <= counter + 1;
	end
end
	
always @ (posedge p_tick)
	begin
	if (rst)
		rgb_reg <= 0;
	else
		begin
		if(in_windows)
			rgb_reg <= data[5:0];			
		else
			rgb_reg <= 6'b111111;
		end
	end

assign rgb = (video_on) ? rgb_reg : 6'b0;

endmodule
