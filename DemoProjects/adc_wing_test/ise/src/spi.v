`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Mahdi Changani
// 
// Create Date: 10/31/2016 08:04:01 PM
// Design Name: 
// Module Name: spi
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module spi #(parameter CLK_DIV = 2)(
    input clk,
    input rst,
	
    input miso,
    output mosi,
    output sck,
    output ss,
    input start,
    
    input[15:0] data_in,  
    output[15:0] data_out,
    output busy,
    output new_data
  );
   
  localparam STATE_SIZE = 2;
  localparam IDLE = 2'd0,
    WAIT_HALF = 2'd1,
    TRANSFER = 2'd2;
   
  reg [STATE_SIZE-1:0] state_d, state_q;
   
  reg [15:0] data_d, data_q;
  reg [CLK_DIV-1:0] sck_d, sck_q;
  reg mosi_d, mosi_q;
  reg [3:0] ctr_d, ctr_q;
  reg new_data_d, new_data_q;
  reg [15:0] data_out_d, data_out_q;
  
  reg ss_d, ss_q;
   
  assign mosi = mosi_q;
  assign sck = (sck_q[CLK_DIV-1]) & (state_q == TRANSFER);
  assign busy = state_q != IDLE;
  assign data_out = data_out_q;
  assign new_data = new_data_q;
  
  assign ss = ss_q;
   
  always @(*) begin
    sck_d = sck_q;
    data_d = data_q;
    mosi_d = mosi_q;
    ctr_d = ctr_q;
    new_data_d = 1'b0;
    data_out_d = data_out_q;
    state_d = state_q;    
    ss_d = ss_q;
     
    case (state_q)
      IDLE: begin
        sck_d = 4'b0;              // reset clock counter
        ctr_d = 4'b0;              // reset bit counter
        if ( start == 1'b1 ) begin // if start command
          data_d = data_in;        // copy data to send          
          ss_d = 1'b0;
          state_d = WAIT_HALF;     // change state      
        end
		  else begin
			 ss_d  = 1'b1;
		  end
      end
      WAIT_HALF: begin
        sck_d = sck_q + 1'b1;                  // increment clock counter
        if (sck_q == {CLK_DIV-1{1'b1}}) begin  // if clock is half full (about to fall)
          sck_d = 1'b0;                        // reset to 0
          state_d = TRANSFER;                  // change state
        end
      end
      TRANSFER: begin
        sck_d = sck_q + 1'b1;                           // increment clock counter
        if (sck_q == 4'b0000) begin                     // if clock counter is 0
          mosi_d = data_q[15];                           // output the MSB of data
        end else if (sck_q == {CLK_DIV-1{1'b1}}) begin  // else if it's half full (about to fall)
          data_d = {data_q[14:0], miso};                 // read in data (shift in)
        end else if (sck_q == {CLK_DIV{1'b1}}) begin    // else if it's full (about to rise)
          ctr_d = ctr_q + 1'b1;                         // increment bit counter
          if (ctr_q == 4'b1111) begin                    // if we are on the last bit
            state_d = IDLE;                             // change state
            data_out_d = data_q;                        // output data
            new_data_d = 1'b1;                          // signal data is valid
            ss_d  = 1'b1;
          end
        end
      end
    endcase
  end
   
  always @(posedge clk) begin
    if (rst) begin
      ctr_q <= 4'b0;
      data_q <= 8'b0;
      sck_q <= 4'b0;
      mosi_q <= 1'b0;
      state_q <= IDLE;
      data_out_q <= 8'b0;
      new_data_q <= 1'b0;
    end else begin
      ctr_q <= ctr_d;
      data_q <= data_d;
      sck_q <= sck_d;
      mosi_q <= mosi_d;
      state_q <= state_d;
      data_out_q <= data_out_d;
      new_data_q <= new_data_d;
      ss_q <= ss_d;
    end
  end
   
endmodule