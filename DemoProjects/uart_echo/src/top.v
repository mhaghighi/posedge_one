`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:49:32 07/26/2015 
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
	input clk_in,
	input rst_n,
	output txd,
	input rxd
    );
	 
	wire 			clk;
	wire			rst;

	wire 		  	rx_fifo_rd_en;
	wire [7:0] 	rx_fifo_dout;
	wire 		  	rx_fifo_empty;
	
	wire 			tx_fifo_full;
	wire [7:0] 	tx_fifo_din;
	wire 			tx_fifo_wr_en;
		
	parameter BAUD_RATE    = 9_600;              // Baud rate
	parameter CLOCK_RATE   = 40_000_000;
	
	assign rst = !locked;
	
	clk_gen clk_gen_i0 (
    .CLK_IN1(clk_in),				// 24MHz input clock
    .CLK_OUT1(clk), 					// 40 MHz output clock
    .RESET(0),         		
    .LOCKED(locked)
	);      
	
	uart_rx_fifo #(	
	 .BAUD_RATE  				(BAUD_RATE),
	 .CLOCK_RATE 				(CLOCK_RATE)
	)
	uart_rx_fifo_i0 (
    .clk(clk), 
    .rst(rst), 
    .rxd_i(rxd), 
    .rx_fifo_rd_en(rx_fifo_rd_en), 
    .rx_fifo_dout(rx_fifo_dout), 
    .rx_fifo_empty(rx_fifo_empty)
   );

rx2tx rx2tx_i0 (
    .clk(clk), 
    .rst_n(!rst), 	 
    .rx_fifo_dout(rx_fifo_dout), 
    .rx_fifo_empty(rx_fifo_empty), 
    .rx_fifo_rd_en(rx_fifo_rd_en), 	 
    .tx_fifo_din(tx_fifo_din), 
    .tx_fifo_full(tx_fifo_full), 
    .tx_fifo_wr_en(tx_fifo_wr_en)
    );
	 
	uart_tx_fifo #(	
	.BAUD_RATE  				(BAUD_RATE),
	.CLOCK_RATE 				(CLOCK_RATE)
	)
	uart_tx_fifo_i0 (
    .clk(clk), 
    .rst_clk_tx(rst), 
    .tx_fifo_full(tx_fifo_full), 
    .tx_fifo_din(tx_fifo_din), 
    .tx_fifo_wr_en(tx_fifo_wr_en), 
    .tx_txd(txd)
   );
	 
endmodule
