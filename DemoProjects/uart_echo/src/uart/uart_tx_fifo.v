`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:22:41 07/11/2015 
// Design Name: 
// Module Name:    uart_tx_fifo 
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
module uart_tx_fifo(
  //input        clk_tx,          	// Clock input
  input        clk,             	// Clock input
  input        rst_clk_tx,      	// Active HIGH reset - synchronous to clk_tx

  output       tx_fifo_full, 		// Empty signal from char FIFO (FWFT)
  input  [7:0] tx_fifo_din,  		// Data from the char FIFO
  input        tx_fifo_wr_en, 	// Pop signal to the char FIFO

  output       tx_txd         	// The transmit serial signal
    );

//***************************************************************************
// Parameter definitions
//***************************************************************************

  parameter BAUD_RATE    = 9_600;              // Baud rate

  parameter CLOCK_RATE   = 40_000_000;

//***************************************************************************
// Reg declarations
//***************************************************************************

//***************************************************************************
// Wire declarations
//***************************************************************************
  
  wire 			char_fifo_empty;
  wire [7:0] 	char_fifo_dout;
  wire 			char_fifo_rd_en;
//***************************************************************************
// Code
//***************************************************************************
// Instantiate the module

char_fifo char_fifo_i0 (
	.rst							(rst_clk_tx), // input rst
	.wr_clk						(clk), // input wr_clk
	.rd_clk						(clk), // input clk_tx
	.din							(tx_fifo_din), // input [7 : 0] din
	.wr_en						(tx_fifo_wr_en), // input wr_en
	.rd_en						(char_fifo_rd_en), // input rd_en
	.dout							(char_fifo_dout), // output [7 : 0] dout
	.full							(tx_fifo_full), // output full
	.empty						(char_fifo_empty) // output empty
);

uart_tx  #(	
	.BAUD_RATE  				(BAUD_RATE),
	.CLOCK_RATE 				(CLOCK_RATE)
	)
	uart_tx_i0(
	.clk_tx						(clk), 
	.rst_clk_tx					(rst_clk_tx), 
	.char_fifo_empty			(char_fifo_empty), 
	.char_fifo_dout			(char_fifo_dout), 
	.char_fifo_rd_en			(char_fifo_rd_en), 
	.txd_tx						(tx_txd)
	);
	
endmodule
