//-----------------------------------------------------------------------------
//
// Title       : 
// Design      : spiwb_adc
// Author      : 
// Company     : 
//
//-----------------------------------------------------------------------------
//
// File        : D:\Documents\my_designs\spi_wb_adc\spiwb_adc\compile\adc_spi_driver.v
// Generated   : 08/29/17 12:06:34
// From        : D:\Documents\my_designs\spi_wb_adc\spiwb_adc\src\adc_spi_driver.asf
// By          : FSM2VHDL ver. 5.0.7.2
//
//-----------------------------------------------------------------------------
//
// Description : 
//
//-----------------------------------------------------------------------------

`timescale 1ns / 1ps

module adc_spi_driver (CLK_48, adc_out, rst, sw_in, wb_ack, wb_adr, wb_cyc, wb_di, wb_do, wb_err, wb_int, wb_sel, wb_stb, wb_we);
input      	CLK_48;
input      	rst;
input      	[7:0] sw_in;
input      	wb_ack;
input      	[31:0] wb_do;
input      	wb_err;
input      	wb_int;
output     	[15:0] adc_out;
output     	[4:0] wb_adr;
output     	wb_cyc;
output     	[31:0] wb_di;
output     	[3:0] wb_sel;
output     	wb_stb;
output     	wb_we;

wire        CLK_48;
reg         [15:0] adc_out, next_adc_out;
wire        rst;
wire        [7:0] sw_in;
wire        wb_ack;
reg         [4:0] wb_adr, next_wb_adr;
reg         wb_cyc, next_wb_cyc;
reg         [31:0] wb_di, next_wb_di;
wire        [31:0] wb_do;
wire        wb_err;
wire        wb_int;
reg         [3:0] wb_sel, next_wb_sel;
reg         wb_stb, next_wb_stb;
reg         wb_we, next_wb_we;

// diagram signals declarations
reg  [7:0]ctrl_reg, next_ctrl_reg;
reg  [0:22]delay_counter_Sreg0, next_delay_counter_Sreg0;

// USER DEFINED ENCODED state machine: Sreg0
// State codes definitions:
`define rst_state 4'b0000
`define init_core_S1 4'b0001
`define init_core_S2 4'b0010
`define init_core_S3 4'b0011
`define init_core_S4 4'b0100
`define read_adc_S13 4'b1101
`define read_adc_S8 4'b1000
`define read_adc_S7 4'b0111
`define read_adc_S10 4'b1010
`define read_adc_S9 4'b1001
`define read_adc_S11 4'b1011
`define read_adc_S12 4'b1100
`define init_core_S5 4'b0101
`define init_core_S6 4'b0110
`define D1_DS1 4'b1111

reg [3:0] CurrState_Sreg0;
reg [3:0] NextState_Sreg0;


//--------------------------------------------------------------------
// Machine: Sreg0
//--------------------------------------------------------------------
//----------------------------------
// Next State Logic (combinatorial)
//----------------------------------
always @ (adc_out or ctrl_reg or delay_counter_Sreg0 or sw_in or wb_ack or wb_adr or wb_cyc or wb_di or wb_do or wb_int or wb_sel or wb_stb or wb_we or CurrState_Sreg0)
begin : Sreg0_NextState
	NextState_Sreg0 <= CurrState_Sreg0;
	// Set default values for outputs and signals
	next_wb_adr <= wb_adr;
	next_wb_di <= wb_di;
	next_wb_sel <= wb_sel;
	next_wb_we <= wb_we;
	next_wb_stb <= wb_stb;
	next_adc_out <= adc_out;
	next_wb_cyc <= wb_cyc;
	next_ctrl_reg <= ctrl_reg;
	next_delay_counter_Sreg0 <= delay_counter_Sreg0;
	case (CurrState_Sreg0) // synopsys parallel_case full_case
		`rst_state:
		begin
			next_wb_adr <= 0;
			next_wb_di <= 0;
			next_wb_sel <= 0;
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_adc_out <= 0;
			next_wb_cyc <= 0;
			next_ctrl_reg <= 0;
			NextState_Sreg0 <= `init_core_S1;
		end
		`init_core_S1:		// set CTRL_REG
		begin
			next_wb_adr <= 5'h10;
			next_wb_di <= {7'b1100100,7'b0010000};
			next_wb_we <= 1;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 0)	
				NextState_Sreg0 <= `init_core_S1;
			else if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `init_core_S2;
				next_wb_we <= 0;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
			end
		end
		`init_core_S2:
		begin
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			NextState_Sreg0 <= `init_core_S3;
		end
		`init_core_S3:		// set SS_REG
		begin
			next_wb_adr <= 5'h18;
			next_wb_di <= 1;
			next_wb_we <= 1;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 0)	
				NextState_Sreg0 <= `init_core_S3;
			else if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `init_core_S4;
				next_wb_we <= 0;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
			end
		end
		`init_core_S4:
		begin
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			NextState_Sreg0 <= `init_core_S5;
		end
		`init_core_S5:		// set SCK frequency
		begin
			next_wb_adr <= 5'h14;
			next_wb_di <= 16;
			//sck_freq=12MHz
			next_wb_we <= 1;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `init_core_S6;
				next_wb_we <= 0;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
			end
			else if (wb_ack == 0)	
				NextState_Sreg0 <= `init_core_S5;
		end
		`init_core_S6:
		begin
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			NextState_Sreg0 <= `read_adc_S7;
		end
		`read_adc_S13:
		begin
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			NextState_Sreg0 <= `D1_DS1;
			next_delay_counter_Sreg0 <= 5000000 - 1;
		end
		`read_adc_S8:		// Send command to spi_core
		begin
			next_wb_adr <= 5'h00;
			next_wb_di <= {(ctrl_reg<<3), 8'h00};
			next_wb_we <= 1;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 0)	
				NextState_Sreg0 <= `read_adc_S8;
			else if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `read_adc_S9;
				next_wb_we <= 0;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
			end
		end
		`read_adc_S7:		// Read SW
		begin
			next_ctrl_reg <= sw_in;
			NextState_Sreg0 <= `read_adc_S8;
		end
		`read_adc_S10:		// Start transfering command to ADC
		begin
			next_wb_adr <= 5'h10;
			next_wb_di <= {7'b1100110,7'h10};
			// Go-Busy=1
			next_wb_we <= 1;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `read_adc_S11;
				next_wb_we <= 0;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
			end
			else if (wb_ack == 0)	
				NextState_Sreg0 <= `read_adc_S10;
		end
		`read_adc_S9:
		begin
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			NextState_Sreg0 <= `read_adc_S10;
		end
		`read_adc_S11:		// Wait for spi_core to finish transfer
		begin
			next_wb_we <= 0;
			next_wb_stb <= 0;
			next_wb_cyc <= 0;
			if (wb_int == 1)	
				NextState_Sreg0 <= `read_adc_S12;
			else if (wb_int == 0)	
				NextState_Sreg0 <= `read_adc_S11;
		end
		`read_adc_S12:		// Read adc output from spi_core
		begin
			next_wb_adr <= 5'h00;
			next_wb_we <= 0;
			next_wb_stb <= 1;
			next_wb_cyc <= 1;
			next_wb_sel <= 4'hf;
			if (wb_ack == 0)	
				NextState_Sreg0 <= `read_adc_S12;
			else if (wb_ack == 1)	
			begin
				NextState_Sreg0 <= `read_adc_S13;
				next_wb_stb <= 0;
				next_wb_cyc <= 0;
				next_adc_out <= wb_do[15:0];
			end
		end
		`D1_DS1:
		// Delay between ADC reads for better visibility on 7-segment 
		//  (ADC refresh rate ~ 10 HZ)

			if (delay_counter_Sreg0 == 0)	
				NextState_Sreg0 <= `read_adc_S7;
			else
			begin
				NextState_Sreg0 <= `D1_DS1;
				if (delay_counter_Sreg0 != 0) next_delay_counter_Sreg0 <= delay_counter_Sreg0 - 1;
			end
	endcase
end

//----------------------------------
// Current State Logic (sequential)
//----------------------------------
always @ (posedge CLK_48)
begin : Sreg0_CurrentState
	if (rst)	
		CurrState_Sreg0 <= `rst_state;
	else
		CurrState_Sreg0 <= NextState_Sreg0;
end

//----------------------------------
// Registered outputs logic
//----------------------------------
always @ (posedge CLK_48)
begin : Sreg0_RegOutput
	if (rst)	
	begin
		ctrl_reg <= 0;
		wb_adr <= 0;
		wb_di <= 0;
		wb_sel <= 0;
		wb_we <= 0;
		wb_stb <= 0;
		adc_out <= 0;
		wb_cyc <= 0;
	end
	else 
	begin
		ctrl_reg <= next_ctrl_reg;
		delay_counter_Sreg0 <= next_delay_counter_Sreg0;
		wb_adr <= next_wb_adr;
		wb_di <= next_wb_di;
		wb_sel <= next_wb_sel;
		wb_we <= next_wb_we;
		wb_stb <= next_wb_stb;
		adc_out <= next_adc_out;
		wb_cyc <= next_wb_cyc;
	end
end

endmodule