//-----------------------------------------------------------------------------
// microblaze_stub.v
//-----------------------------------------------------------------------------

module microblaze_stub
  (
    RS232_Uart_1_sout,
    RS232_Uart_1_sin,
    RESET_N,
    Linear_Flash_we_n,
    Linear_Flash_oe_n,
    Linear_Flash_data,
    Linear_Flash_ce_n,
    Linear_Flash_address,
    CLOCK,
    axi_spi_0_SPISEL_pin,
    axi_spi_0_SCK_pin,
    axi_spi_0_MISO_pin,
    axi_spi_0_MOSI_pin,
    axi_spi_0_SS_pin
  );
  output RS232_Uart_1_sout;
  input RS232_Uart_1_sin;
  input RESET_N;
  output Linear_Flash_we_n;
  output Linear_Flash_oe_n;
  inout [7:0] Linear_Flash_data;
  output Linear_Flash_ce_n;
  output [18:0] Linear_Flash_address;
  input CLOCK;
  input axi_spi_0_SPISEL_pin;
  inout axi_spi_0_SCK_pin;
  inout axi_spi_0_MISO_pin;
  inout axi_spi_0_MOSI_pin;
  inout axi_spi_0_SS_pin;

  (* BOX_TYPE = "user_black_box" *)
  microblaze
    microblaze_i (
      .RS232_Uart_1_sout ( RS232_Uart_1_sout ),
      .RS232_Uart_1_sin ( RS232_Uart_1_sin ),
      .RESET_N ( RESET_N ),
      .Linear_Flash_we_n ( Linear_Flash_we_n ),
      .Linear_Flash_oe_n ( Linear_Flash_oe_n ),
      .Linear_Flash_data ( Linear_Flash_data ),
      .Linear_Flash_ce_n ( Linear_Flash_ce_n ),
      .Linear_Flash_address ( Linear_Flash_address ),
      .CLOCK ( CLOCK ),
      .axi_spi_0_SPISEL_pin ( axi_spi_0_SPISEL_pin ),
      .axi_spi_0_SCK_pin ( axi_spi_0_SCK_pin ),
      .axi_spi_0_MISO_pin ( axi_spi_0_MISO_pin ),
      .axi_spi_0_MOSI_pin ( axi_spi_0_MOSI_pin ),
      .axi_spi_0_SS_pin ( axi_spi_0_SS_pin )
    );

endmodule

module microblaze
  (
    RS232_Uart_1_sout,
    RS232_Uart_1_sin,
    RESET_N,
    Linear_Flash_we_n,
    Linear_Flash_oe_n,
    Linear_Flash_data,
    Linear_Flash_ce_n,
    Linear_Flash_address,
    CLOCK,
    axi_spi_0_SPISEL_pin,
    axi_spi_0_SCK_pin,
    axi_spi_0_MISO_pin,
    axi_spi_0_MOSI_pin,
    axi_spi_0_SS_pin
  );
  output RS232_Uart_1_sout;
  input RS232_Uart_1_sin;
  input RESET_N;
  output Linear_Flash_we_n;
  output Linear_Flash_oe_n;
  inout [7:0] Linear_Flash_data;
  output Linear_Flash_ce_n;
  output [18:0] Linear_Flash_address;
  input CLOCK;
  input axi_spi_0_SPISEL_pin;
  inout axi_spi_0_SCK_pin;
  inout axi_spi_0_MISO_pin;
  inout axi_spi_0_MOSI_pin;
  inout axi_spi_0_SS_pin;
endmodule

