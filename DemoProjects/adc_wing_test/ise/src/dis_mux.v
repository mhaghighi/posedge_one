`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:01:39 09/02/2015 
// Design Name: 
// Module Name:    dis_mux 
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
module dis_mux(
    input clk,
    input reset,
    input [3:0] hex0,
	 input [3:0] hex1,
	 input [3:0] hex2,
	 input [3:0] hex3,
	 input [3:0] dp,
    output reg [3:0] an,
    output reg [7:0] sseg
    );
	 
	 // refreshing time: 50Mhz/2^16 = 763 Hz
	 localparam N = 18;
	 
	 //signal declaration
	 reg [N-1:0] q_reg;
	 wire [N-1:0] q_next;
	 reg [3:0] hex_in;
	 reg dp_in;
	 
	 //register
	 // N-bit counter
	 always@(posedge clk, posedge reset)
		if (reset)
			q_reg <= 0;
		else
			q_reg <= q_next;
	
	//next state logic
	assign q_next = q_reg + 1;
	
	//2 MSBs of q_reg control of multiplexr
	always@*
		case (q_reg[N-1:N-2])
			2'b00:
				begin
					an = 4'b1110;
					hex_in = hex0;
					dp_in = dp[0];
				end
			2'b01:
				begin
					an = 4'b1101;
					hex_in = hex1;
					dp_in = dp[1];
				end
			2'b10:
				begin
					an = 4'b1011;
					hex_in = hex2;
					dp_in = dp[2];
				end
			default:
				begin
					an = 4'b0111;
					hex_in = hex3;
					dp_in = dp[3];
				end								
		endcase
		
	always@*
	 begin
		case(hex_in)
			4'h0: sseg[6:0] = 7'b1000000;			
			4'h1: sseg[6:0] = 7'b1111001;			
			4'h2: sseg[6:0] = 7'b0100100;
			4'h3: sseg[6:0] = 7'b0110000; // 0000110;
			4'h4: sseg[6:0] = 7'b0011001; // 1001100;
			4'h5: sseg[6:0] = 7'b0010010; // 0100100;
			4'h6: sseg[6:0] = 7'b0000010; // 0100000;
			4'h7: sseg[6:0] = 7'b1111000; // 0001111;
			4'h8: sseg[6:0] = 7'b0000000;
			4'h9: sseg[6:0] = 7'b0010000; // 0000100;
			4'ha: sseg[6:0] = 7'b0001000; // 0001000;
			4'hb: sseg[6:0] = 7'b0000011; // 1100000;
			4'hc: sseg[6:0] = 7'b1000110; // 0110001;
			4'hd: sseg[6:0] = 7'b0100001; // 1000010;
			4'he: sseg[6:0] = 7'b0000110; // 0110000;
			default: sseg[6:0] = 7'b0001110; // 0111000; //4'hf
		endcase
		
		sseg[7] = dp_in;
	 end


endmodule
