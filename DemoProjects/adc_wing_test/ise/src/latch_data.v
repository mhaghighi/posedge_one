`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Mahdi Changani
// 
// Create Date:    15:00:01 11/05/2016 
// Design Name: 
// Module Name:    latch_data 
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
module latch_data(
	 input clk,
	 input rst,
	 input  [15:0] data_in,
	 output [15:0] data_out
    );

	 assign data_out = data_out_reg;
	 
	 reg [15:0] data_out_reg;
	 reg [15:0] data_out_next;
	 reg [N-1:0] count_reg;
	 wire [N-1:0] count_next;
	 
	 // latch data to 7segment: 1Mhz/2^20 = 1 Hz
	 localparam N = 20;
	 
	 
	 // 20-bit counter
	 always@(posedge clk)
		if (rst) begin
			count_reg <= 0;
			data_out_reg <= 0;
		end
		else begin
			count_reg    <= count_next;
			data_out_reg <= data_out_next;
		end
			
	//next state logic
	assign count_next = count_reg + 1;
	
	
	always@* begin
		if ( count_reg[N-1] == 1'b1 ) begin
			data_out_next = data_in;
		end
		else
			data_out_next = data_out_reg;
	end

endmodule
