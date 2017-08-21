`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:08:36 07/13/2015 
// Design Name: 
// Module Name:    uart_rx_fifo 
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
module uart_rx_fifo(
	//input							clk_rx,
	input							clk,
	input							rst,
	input							rxd_i,
	input							rx_fifo_rd_en,
	output		[7:0]			rx_fifo_dout,
	output						rx_fifo_empty	
	);

//***************************************************************************
// Parameter definitions
//***************************************************************************

  parameter BAUD_RATE    = 9_600;              // Baud rate
  parameter CLOCK_RATE   = 40_000_000;
 
//***************************************************************************
// Wire declarations
//***************************************************************************
 	
	wire		[7:0]				rx_data;
	wire							rx_data_rdy;
	
	wire		[7:0]				rx_fifo_din;
	wire							rx_fifo_full;
	wire							rx_fifo_wr_en;
	reg 							rx_fifo_wr_en_reg;
	reg							rx_data_rdy_prev_reg;
//***************************************************************************
// Code
//***************************************************************************
// Instantiate the module	

uart_rx  #(	
	.BAUD_RATE  				(BAUD_RATE),
	.CLOCK_RATE 				(CLOCK_RATE)
	)
	uart_rx_i0 (
	.clk_rx						(clk), 
	.rst_clk_rx					(rst), 
	.rxd_i						(rxd_i), 
	.rx_data						(rx_data), 
	.rx_data_rdy				(rx_data_rdy), 
	.frm_err						()
	);
	 

assign rx_fifo_din = (rx_data_rdy)?rx_data:8'h00; 
assign rx_fifo_wr_en = rx_fifo_wr_en_reg;

always @(posedge clk) begin
	if (rst) begin
		rx_data_rdy_prev_reg <= 0;
		rx_fifo_wr_en_reg <= 0;
	end
	else if (rx_data_rdy == 1'b1 && rx_data_rdy_prev_reg == 1'b0) begin
		rx_fifo_wr_en_reg <= 1'b1;
		rx_data_rdy_prev_reg <= rx_data_rdy;
	end 
	else begin
		rx_fifo_wr_en_reg <= 1'b0;
		rx_data_rdy_prev_reg <= rx_data_rdy;
	end
end
		

char_fifo char_fifo_i0 (
	.rst							(rst), // input rst
	.wr_clk						(clk), // input wr_clk
	.rd_clk						(clk), // input rd_clk
	.din							(rx_fifo_din), // input [7 : 0] din
	.wr_en						(rx_fifo_wr_en), // input wr_en
	.rd_en						(rx_fifo_rd_en), // input rd_en
	.dout							(rx_fifo_dout), // output [7 : 0] dout
	.full							(rx_fifo_full), // output full
	.empty						(rx_fifo_empty) // output empty
	);

endmodule
