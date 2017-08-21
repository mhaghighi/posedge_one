//-----------------------------------------------------------------------------
//
// Title       : FT2232H Async FIFO Loopback teset
// Design      : afifo_fifoIf
// Author      : mahmoud
// Company     : posedge
//
//-----------------------------------------------------------------------------
//
// File        : d:\Projects\PosedgeOne\trunk\Samples\afifo\ahdl\afifo_fifoIF_loopback\afifo_fifoIf\compile\afifo_loopback.v
// Generated   : Sat Dec 12 12:20:59 2015
// From        : d:\Projects\PosedgeOne\trunk\Samples\afifo\ahdl\afifo_fifoIF_loopback\afifo_fifoIf\src\afifo_loopback.bde
// By          : Bde2Verilog ver. 2.01
//
//-----------------------------------------------------------------------------
//
// Description : 
//
//-----------------------------------------------------------------------------

`ifdef _VCP
`else
`define library(a,b)
`endif


// ---------- Design Unit Header ---------- //
`timescale 1ps / 1ps

module afifo_loopback (clk_24,ft_rxf_n,ft_txe_n,reset_i_n,ft_rd_n,ft_wr_n,ft_data) ;

// ------------ Port declarations --------- //
input clk_24;
wire clk_24;
input ft_rxf_n;
wire ft_rxf_n;
input ft_txe_n;
wire ft_txe_n;
input reset_i_n;
wire reset_i_n;
output ft_rd_n;
wire ft_rd_n;
output ft_wr_n;
wire ft_wr_n;
inout [7:0] ft_data;
wire [7:0] ft_data;

// ----------- Signal declarations -------- //
wire clk_pll;
wire reset;
wire reset_n;
wire rst_in;
wire rx_empty;
wire rx_rd;
wire tx_full;
wire tx_wr;
wire [7:0] rx_dout;
wire [7:0] tx_data;

// -------- Component instantiations -------//

pll U3
(
	.CLK_IN1(clk_24),
	.CLK_OUT1(clk_pll),
	.LOCKED(reset_n),
	.RESET(rst_in)
);



assign rst_in = ~(reset_i_n);


assign reset = ~(reset_n);


afifo afifo_i
(
	.clk(clk_pll),
	.data(ft_data),
	.fifo_read_dout(rx_dout),
	.fifo_read_empty(rx_empty),
	.fifo_read_rd_en(rx_rd),
	.fifo_write_din(tx_data),
	.fifo_write_full(tx_full),
	.fifo_write_wr_en(tx_wr),
	.rd_n(ft_rd_n),
	.rst(reset),
	.rxf_n(ft_rxf_n),
	.txe_n(ft_txe_n),
	.wr_n(ft_wr_n)
);



looper looper_i
(
	.clk_pll(clk_pll),
	.reset_n(reset_n),
	.rx_dout(rx_dout),
	.rx_empty(rx_empty),
	.rx_rd(rx_rd),
	.tx_data(tx_data),
	.tx_full(tx_full),
	.tx_wr(tx_wr)
);



endmodule 
