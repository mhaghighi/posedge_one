//-----------------------------------------------------------------------------
// microblaze_0_bram_block_elaborate.v
//-----------------------------------------------------------------------------

(* keep_hierarchy = "yes" *)
module microblaze_0_bram_block_elaborate
  (
    BRAM_Rst_A,
    BRAM_Clk_A,
    BRAM_EN_A,
    BRAM_WEN_A,
    BRAM_Addr_A,
    BRAM_Din_A,
    BRAM_Dout_A,
    BRAM_Rst_B,
    BRAM_Clk_B,
    BRAM_EN_B,
    BRAM_WEN_B,
    BRAM_Addr_B,
    BRAM_Din_B,
    BRAM_Dout_B
  );
  parameter
    C_MEMSIZE = 'h2000,
    C_PORT_DWIDTH = 32,
    C_PORT_AWIDTH = 32,
    C_NUM_WE = 4,
    C_FAMILY = "spartan6";
  input BRAM_Rst_A;
  input BRAM_Clk_A;
  input BRAM_EN_A;
  input [0:C_NUM_WE-1] BRAM_WEN_A;
  input [0:C_PORT_AWIDTH-1] BRAM_Addr_A;
  output [0:C_PORT_DWIDTH-1] BRAM_Din_A;
  input [0:C_PORT_DWIDTH-1] BRAM_Dout_A;
  input BRAM_Rst_B;
  input BRAM_Clk_B;
  input BRAM_EN_B;
  input [0:C_NUM_WE-1] BRAM_WEN_B;
  input [0:C_PORT_AWIDTH-1] BRAM_Addr_B;
  output [0:C_PORT_DWIDTH-1] BRAM_Din_B;
  input [0:C_PORT_DWIDTH-1] BRAM_Dout_B;

  // Internal signals

  wire net_gnd0;
  wire [3:0] net_gnd4;
  wire [0:2] pgassign1;
  wire [0:23] pgassign2;
  wire [13:0] pgassign3;
  wire [31:0] pgassign4;
  wire [31:0] pgassign5;
  wire [3:0] pgassign6;
  wire [13:0] pgassign7;
  wire [31:0] pgassign8;
  wire [31:0] pgassign9;
  wire [3:0] pgassign10;
  wire [13:0] pgassign11;
  wire [31:0] pgassign12;
  wire [31:0] pgassign13;
  wire [3:0] pgassign14;
  wire [13:0] pgassign15;
  wire [31:0] pgassign16;
  wire [31:0] pgassign17;
  wire [3:0] pgassign18;
  wire [13:0] pgassign19;
  wire [31:0] pgassign20;
  wire [31:0] pgassign21;
  wire [3:0] pgassign22;
  wire [13:0] pgassign23;
  wire [31:0] pgassign24;
  wire [31:0] pgassign25;
  wire [3:0] pgassign26;
  wire [13:0] pgassign27;
  wire [31:0] pgassign28;
  wire [31:0] pgassign29;
  wire [3:0] pgassign30;
  wire [13:0] pgassign31;
  wire [31:0] pgassign32;
  wire [31:0] pgassign33;
  wire [3:0] pgassign34;

  // Internal assignments

  assign pgassign1[0:2] = 3'b000;
  assign pgassign2[0:23] = 24'b000000000000000000000000;
  assign pgassign3[13:3] = BRAM_Addr_A[19:29];
  assign pgassign3[2:0] = 3'b000;
  assign pgassign4[31:8] = 24'b000000000000000000000000;
  assign pgassign4[7:0] = BRAM_Dout_A[0:7];
  assign BRAM_Din_A[0:7] = pgassign5[7:0];
  assign pgassign6[3:3] = BRAM_WEN_A[0:0];
  assign pgassign6[2:2] = BRAM_WEN_A[0:0];
  assign pgassign6[1:1] = BRAM_WEN_A[0:0];
  assign pgassign6[0:0] = BRAM_WEN_A[0:0];
  assign pgassign7[13:3] = BRAM_Addr_B[19:29];
  assign pgassign7[2:0] = 3'b000;
  assign pgassign8[31:8] = 24'b000000000000000000000000;
  assign pgassign8[7:0] = BRAM_Dout_B[0:7];
  assign BRAM_Din_B[0:7] = pgassign9[7:0];
  assign pgassign10[3:3] = BRAM_WEN_B[0:0];
  assign pgassign10[2:2] = BRAM_WEN_B[0:0];
  assign pgassign10[1:1] = BRAM_WEN_B[0:0];
  assign pgassign10[0:0] = BRAM_WEN_B[0:0];
  assign pgassign11[13:3] = BRAM_Addr_A[19:29];
  assign pgassign11[2:0] = 3'b000;
  assign pgassign12[31:8] = 24'b000000000000000000000000;
  assign pgassign12[7:0] = BRAM_Dout_A[8:15];
  assign BRAM_Din_A[8:15] = pgassign13[7:0];
  assign pgassign14[3:3] = BRAM_WEN_A[1:1];
  assign pgassign14[2:2] = BRAM_WEN_A[1:1];
  assign pgassign14[1:1] = BRAM_WEN_A[1:1];
  assign pgassign14[0:0] = BRAM_WEN_A[1:1];
  assign pgassign15[13:3] = BRAM_Addr_B[19:29];
  assign pgassign15[2:0] = 3'b000;
  assign pgassign16[31:8] = 24'b000000000000000000000000;
  assign pgassign16[7:0] = BRAM_Dout_B[8:15];
  assign BRAM_Din_B[8:15] = pgassign17[7:0];
  assign pgassign18[3:3] = BRAM_WEN_B[1:1];
  assign pgassign18[2:2] = BRAM_WEN_B[1:1];
  assign pgassign18[1:1] = BRAM_WEN_B[1:1];
  assign pgassign18[0:0] = BRAM_WEN_B[1:1];
  assign pgassign19[13:3] = BRAM_Addr_A[19:29];
  assign pgassign19[2:0] = 3'b000;
  assign pgassign20[31:8] = 24'b000000000000000000000000;
  assign pgassign20[7:0] = BRAM_Dout_A[16:23];
  assign BRAM_Din_A[16:23] = pgassign21[7:0];
  assign pgassign22[3:3] = BRAM_WEN_A[2:2];
  assign pgassign22[2:2] = BRAM_WEN_A[2:2];
  assign pgassign22[1:1] = BRAM_WEN_A[2:2];
  assign pgassign22[0:0] = BRAM_WEN_A[2:2];
  assign pgassign23[13:3] = BRAM_Addr_B[19:29];
  assign pgassign23[2:0] = 3'b000;
  assign pgassign24[31:8] = 24'b000000000000000000000000;
  assign pgassign24[7:0] = BRAM_Dout_B[16:23];
  assign BRAM_Din_B[16:23] = pgassign25[7:0];
  assign pgassign26[3:3] = BRAM_WEN_B[2:2];
  assign pgassign26[2:2] = BRAM_WEN_B[2:2];
  assign pgassign26[1:1] = BRAM_WEN_B[2:2];
  assign pgassign26[0:0] = BRAM_WEN_B[2:2];
  assign pgassign27[13:3] = BRAM_Addr_A[19:29];
  assign pgassign27[2:0] = 3'b000;
  assign pgassign28[31:8] = 24'b000000000000000000000000;
  assign pgassign28[7:0] = BRAM_Dout_A[24:31];
  assign BRAM_Din_A[24:31] = pgassign29[7:0];
  assign pgassign30[3:3] = BRAM_WEN_A[3:3];
  assign pgassign30[2:2] = BRAM_WEN_A[3:3];
  assign pgassign30[1:1] = BRAM_WEN_A[3:3];
  assign pgassign30[0:0] = BRAM_WEN_A[3:3];
  assign pgassign31[13:3] = BRAM_Addr_B[19:29];
  assign pgassign31[2:0] = 3'b000;
  assign pgassign32[31:8] = 24'b000000000000000000000000;
  assign pgassign32[7:0] = BRAM_Dout_B[24:31];
  assign BRAM_Din_B[24:31] = pgassign33[7:0];
  assign pgassign34[3:3] = BRAM_WEN_B[3:3];
  assign pgassign34[2:2] = BRAM_WEN_B[3:3];
  assign pgassign34[1:1] = BRAM_WEN_B[3:3];
  assign pgassign34[0:0] = BRAM_WEN_B[3:3];
  assign net_gnd0 = 1'b0;
  assign net_gnd4[3:0] = 4'b0000;

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_0.mem" ),
      .DATA_WIDTH_A ( 9 ),
      .DATA_WIDTH_B ( 9 )
    )
    ramb16bwer_0 (
      .ADDRA ( pgassign3 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign4 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign5 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign6 ),
      .ADDRB ( pgassign7 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign8 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign9 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign10 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_1.mem" ),
      .DATA_WIDTH_A ( 9 ),
      .DATA_WIDTH_B ( 9 )
    )
    ramb16bwer_1 (
      .ADDRA ( pgassign11 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign12 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign13 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign14 ),
      .ADDRB ( pgassign15 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign16 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign17 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign18 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_2.mem" ),
      .DATA_WIDTH_A ( 9 ),
      .DATA_WIDTH_B ( 9 )
    )
    ramb16bwer_2 (
      .ADDRA ( pgassign19 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign20 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign21 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign22 ),
      .ADDRB ( pgassign23 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign24 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign25 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign26 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_3.mem" ),
      .DATA_WIDTH_A ( 9 ),
      .DATA_WIDTH_B ( 9 )
    )
    ramb16bwer_3 (
      .ADDRA ( pgassign27 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign28 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign29 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign30 ),
      .ADDRB ( pgassign31 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign32 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign33 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign34 )
    );

endmodule

