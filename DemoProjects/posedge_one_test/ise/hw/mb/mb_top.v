//-----------------------------------------------------------------------------
// mb_top.v
//-----------------------------------------------------------------------------

module mb_top
  (
    UART_TX,
    UART_RX,
    RESET_N,
    SRAM_WE_N,
    Generic_Memory_reset,
    SRAM_OE_N,
    SRAM_DATA,
    SRAM_CE_N,
    SRAM_ADDR,
    CLOCK,
	 LED,
	 PB,
	 USER_LED
  );
  output UART_TX;
  input UART_RX;
  input RESET_N;
  output SRAM_WE_N;
  output Generic_Memory_reset;
  output SRAM_OE_N;
  inout [7:0] SRAM_DATA;
  output SRAM_CE_N;
  output [23:0] SRAM_ADDR;
  input CLOCK;
  output [23:0] LED;
  input  [23:0] PB;
  output USER_LED;
 
  reg [23:0] counter;

  (* BOX_TYPE = "user_black_box" *)
  mb
    mb_i (
      .RS232_Uart_1_sout ( UART_TX ),
      .RS232_Uart_1_sin ( UART_RX ),
      .RESET ( RESET_N ),
      .Generic_Memory_we_n ( SRAM_WE_N ),
      .Generic_Memory_reset ( Generic_Memory_reset ),
      .Generic_Memory_oe_n ( SRAM_OE_N ),
      .Generic_Memory_data ( SRAM_DATA ),
      .Generic_Memory_ce_n ( SRAM_CE_N ),
      .Generic_Memory_address ( SRAM_ADDR ),
      .CLK_P ( CLOCK )
    );

	 always @(posedge CLOCK) begin
		if (!RESET_N)
			counter <= 0;
		else
			counter <= counter + 1;
	end

	assign LED[23:0] = PB[23:0] & {24{counter[23]}};
	assign USER_LED = counter[23];
	
endmodule

