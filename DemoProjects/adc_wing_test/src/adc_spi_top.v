//-----------------------------------------------------------------------------
//
// Title       : No Title
// Design      : spiwb_adc
// Author      : mahmoud
// Company     : TORANJ
//
//-----------------------------------------------------------------------------
//
// File        : d:\Documents\my_designs\spi_wb_adc\spiwb_adc\compile\adc_spi_top.v
// Generated   : Thu Nov  3 14:57:15 2016
// From        : d:\Documents\my_designs\spi_wb_adc\spiwb_adc\src\adc_spi_top.bde
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

module adc_spi_top (CLK_IN1,RESET_N,miso_pad_i,sw_in,mosi_pad_o,sclk_pad_o,an,leds,ss_pad_o,sseg) ;

// ------------ Port declarations --------- //
input CLK_IN1;
wire CLK_IN1;
input RESET_N;
wire RESET_N;
input miso_pad_i;
wire miso_pad_i;
input [7:0] sw_in;
wire [7:0] sw_in;
output mosi_pad_o;
wire mosi_pad_o;
output sclk_pad_o;
wire sclk_pad_o;
output [3:0] an;
wire [3:0] an;
output [7:0] leds;
wire [7:0] leds;
output [7:0] ss_pad_o;
wire [7:0] ss_pad_o;
output [7:0] sseg;
wire [7:0] sseg;

// ----------- Signal declarations -------- //
wire CLK_48;
wire locked;
wire RESET;
wire rst;
supply1 VCC;
wire wb_ack;
wire wb_cyc;
wire wb_err;
wire wb_int;
wire wb_stb;
wire wb_we;
wire [15:0] adc_out;
wire [7:0] BUS1146;
wire [3:0] sseg_dp;
wire [4:0] wb_adr;
wire [31:0] wb_di;
wire [31:0] wb_do;
wire [3:0] wb_sel;

// ----------- Continuous assignments -------//

assign leds = sw_in;
// -------- Component instantiations -------//

spi_top U1
(
	.miso_pad_i(miso_pad_i),
	.mosi_pad_o(mosi_pad_o),
	.sclk_pad_o(sclk_pad_o),
	.ss_pad_o(ss_pad_o),
	.wb_ack_o(wb_ack),
	.wb_adr_i(wb_adr),
	.wb_clk_i(CLK_48),
	.wb_cyc_i(wb_cyc),
	.wb_dat_i(wb_di),
	.wb_dat_o(wb_do),
	.wb_err_o(wb_err),
	.wb_int_o(wb_int),
	.wb_rst_i(rst),
	.wb_sel_i(wb_sel),
	.wb_stb_i(wb_stb),
	.wb_we_i(wb_we)
);



clkgen U3
(
	.CLK_IN1(CLK_IN1),
	.CLK_OUT1(CLK_48),
	.LOCKED(locked),
	.RESET(RESET)
);



dis_mux U4
(
	.an(an),
	.clk(CLK_48),
	.dp(sseg_dp),
	.hex0(adc_out[15:12]),
	.hex1(adc_out[11:8]),
	.hex2(adc_out[7:4]),
	.hex3(adc_out[3:0]),
	.reset(rst),
	.sseg(sseg)
);



assign RESET = ~(RESET_N);


assign rst = ~(locked);


adc_spi_driver U7
(
	.CLK_48(CLK_48),
	.adc_out(adc_out),
	.rst(rst),
	.sw_in(sw_in),
	.wb_ack(wb_ack),
	.wb_adr(wb_adr),
	.wb_cyc(wb_cyc),
	.wb_di(wb_di),
	.wb_do(wb_do),
	.wb_err(wb_err),
	.wb_int(wb_int),
	.wb_sel(wb_sel),
	.wb_stb(wb_stb),
	.wb_we(wb_we)
);



// ------------- Power assignment ----------//
assign sseg_dp[0] = VCC;
assign sseg_dp[1] = VCC;
assign sseg_dp[2] = VCC;
assign sseg_dp[3] = VCC;

endmodule 
