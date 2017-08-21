// ==============================================================
// Simple fifo loop-back
// Mahmoud Haghighi 

module rx2tx (
        clk,
        rst_n,
        rx_fifo_dout,
        rx_fifo_empty,
        rx_fifo_rd_en,
        tx_fifo_din,
        tx_fifo_full,
        tx_fifo_wr_en
);

input   clk;
input   rst_n;

input   	[7:0] rx_fifo_dout;
input   	rx_fifo_empty;
output 		rx_fifo_rd_en;
output  	[7:0] tx_fifo_din;
input   	tx_fifo_full;
output  	tx_fifo_wr_en;

assign rx_fifo_rd_en = (!rx_fifo_empty & !tx_fifo_full)? 1'b1: 1'b0;
assign tx_fifo_wr_en = (!rx_fifo_empty & !tx_fifo_full)? 1'b1: 1'b0;
assign tx_fifo_din = (!rx_fifo_empty & !tx_fifo_full)? rx_fifo_dout: 8'h00;

endmodule //rx_to_tx

