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
    C_MEMSIZE = 'h4000,
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
  wire [0:1] pgassign1;
  wire [0:27] pgassign2;
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
  wire [13:0] pgassign35;
  wire [31:0] pgassign36;
  wire [31:0] pgassign37;
  wire [3:0] pgassign38;
  wire [13:0] pgassign39;
  wire [31:0] pgassign40;
  wire [31:0] pgassign41;
  wire [3:0] pgassign42;
  wire [13:0] pgassign43;
  wire [31:0] pgassign44;
  wire [31:0] pgassign45;
  wire [3:0] pgassign46;
  wire [13:0] pgassign47;
  wire [31:0] pgassign48;
  wire [31:0] pgassign49;
  wire [3:0] pgassign50;
  wire [13:0] pgassign51;
  wire [31:0] pgassign52;
  wire [31:0] pgassign53;
  wire [3:0] pgassign54;
  wire [13:0] pgassign55;
  wire [31:0] pgassign56;
  wire [31:0] pgassign57;
  wire [3:0] pgassign58;
  wire [13:0] pgassign59;
  wire [31:0] pgassign60;
  wire [31:0] pgassign61;
  wire [3:0] pgassign62;
  wire [13:0] pgassign63;
  wire [31:0] pgassign64;
  wire [31:0] pgassign65;
  wire [3:0] pgassign66;

  // Internal assignments

  assign pgassign1[0:1] = 2'b00;
  assign pgassign2[0:27] = 28'b0000000000000000000000000000;
  assign pgassign3[13:2] = BRAM_Addr_A[18:29];
  assign pgassign3[1:0] = 2'b00;
  assign pgassign4[31:4] = 28'b0000000000000000000000000000;
  assign pgassign4[3:0] = BRAM_Dout_A[0:3];
  assign BRAM_Din_A[0:3] = pgassign5[3:0];
  assign pgassign6[3:3] = BRAM_WEN_A[0:0];
  assign pgassign6[2:2] = BRAM_WEN_A[0:0];
  assign pgassign6[1:1] = BRAM_WEN_A[0:0];
  assign pgassign6[0:0] = BRAM_WEN_A[0:0];
  assign pgassign7[13:2] = BRAM_Addr_B[18:29];
  assign pgassign7[1:0] = 2'b00;
  assign pgassign8[31:4] = 28'b0000000000000000000000000000;
  assign pgassign8[3:0] = BRAM_Dout_B[0:3];
  assign BRAM_Din_B[0:3] = pgassign9[3:0];
  assign pgassign10[3:3] = BRAM_WEN_B[0:0];
  assign pgassign10[2:2] = BRAM_WEN_B[0:0];
  assign pgassign10[1:1] = BRAM_WEN_B[0:0];
  assign pgassign10[0:0] = BRAM_WEN_B[0:0];
  assign pgassign11[13:2] = BRAM_Addr_A[18:29];
  assign pgassign11[1:0] = 2'b00;
  assign pgassign12[31:4] = 28'b0000000000000000000000000000;
  assign pgassign12[3:0] = BRAM_Dout_A[4:7];
  assign BRAM_Din_A[4:7] = pgassign13[3:0];
  assign pgassign14[3:3] = BRAM_WEN_A[0:0];
  assign pgassign14[2:2] = BRAM_WEN_A[0:0];
  assign pgassign14[1:1] = BRAM_WEN_A[0:0];
  assign pgassign14[0:0] = BRAM_WEN_A[0:0];
  assign pgassign15[13:2] = BRAM_Addr_B[18:29];
  assign pgassign15[1:0] = 2'b00;
  assign pgassign16[31:4] = 28'b0000000000000000000000000000;
  assign pgassign16[3:0] = BRAM_Dout_B[4:7];
  assign BRAM_Din_B[4:7] = pgassign17[3:0];
  assign pgassign18[3:3] = BRAM_WEN_B[0:0];
  assign pgassign18[2:2] = BRAM_WEN_B[0:0];
  assign pgassign18[1:1] = BRAM_WEN_B[0:0];
  assign pgassign18[0:0] = BRAM_WEN_B[0:0];
  assign pgassign19[13:2] = BRAM_Addr_A[18:29];
  assign pgassign19[1:0] = 2'b00;
  assign pgassign20[31:4] = 28'b0000000000000000000000000000;
  assign pgassign20[3:0] = BRAM_Dout_A[8:11];
  assign BRAM_Din_A[8:11] = pgassign21[3:0];
  assign pgassign22[3:3] = BRAM_WEN_A[1:1];
  assign pgassign22[2:2] = BRAM_WEN_A[1:1];
  assign pgassign22[1:1] = BRAM_WEN_A[1:1];
  assign pgassign22[0:0] = BRAM_WEN_A[1:1];
  assign pgassign23[13:2] = BRAM_Addr_B[18:29];
  assign pgassign23[1:0] = 2'b00;
  assign pgassign24[31:4] = 28'b0000000000000000000000000000;
  assign pgassign24[3:0] = BRAM_Dout_B[8:11];
  assign BRAM_Din_B[8:11] = pgassign25[3:0];
  assign pgassign26[3:3] = BRAM_WEN_B[1:1];
  assign pgassign26[2:2] = BRAM_WEN_B[1:1];
  assign pgassign26[1:1] = BRAM_WEN_B[1:1];
  assign pgassign26[0:0] = BRAM_WEN_B[1:1];
  assign pgassign27[13:2] = BRAM_Addr_A[18:29];
  assign pgassign27[1:0] = 2'b00;
  assign pgassign28[31:4] = 28'b0000000000000000000000000000;
  assign pgassign28[3:0] = BRAM_Dout_A[12:15];
  assign BRAM_Din_A[12:15] = pgassign29[3:0];
  assign pgassign30[3:3] = BRAM_WEN_A[1:1];
  assign pgassign30[2:2] = BRAM_WEN_A[1:1];
  assign pgassign30[1:1] = BRAM_WEN_A[1:1];
  assign pgassign30[0:0] = BRAM_WEN_A[1:1];
  assign pgassign31[13:2] = BRAM_Addr_B[18:29];
  assign pgassign31[1:0] = 2'b00;
  assign pgassign32[31:4] = 28'b0000000000000000000000000000;
  assign pgassign32[3:0] = BRAM_Dout_B[12:15];
  assign BRAM_Din_B[12:15] = pgassign33[3:0];
  assign pgassign34[3:3] = BRAM_WEN_B[1:1];
  assign pgassign34[2:2] = BRAM_WEN_B[1:1];
  assign pgassign34[1:1] = BRAM_WEN_B[1:1];
  assign pgassign34[0:0] = BRAM_WEN_B[1:1];
  assign pgassign35[13:2] = BRAM_Addr_A[18:29];
  assign pgassign35[1:0] = 2'b00;
  assign pgassign36[31:4] = 28'b0000000000000000000000000000;
  assign pgassign36[3:0] = BRAM_Dout_A[16:19];
  assign BRAM_Din_A[16:19] = pgassign37[3:0];
  assign pgassign38[3:3] = BRAM_WEN_A[2:2];
  assign pgassign38[2:2] = BRAM_WEN_A[2:2];
  assign pgassign38[1:1] = BRAM_WEN_A[2:2];
  assign pgassign38[0:0] = BRAM_WEN_A[2:2];
  assign pgassign39[13:2] = BRAM_Addr_B[18:29];
  assign pgassign39[1:0] = 2'b00;
  assign pgassign40[31:4] = 28'b0000000000000000000000000000;
  assign pgassign40[3:0] = BRAM_Dout_B[16:19];
  assign BRAM_Din_B[16:19] = pgassign41[3:0];
  assign pgassign42[3:3] = BRAM_WEN_B[2:2];
  assign pgassign42[2:2] = BRAM_WEN_B[2:2];
  assign pgassign42[1:1] = BRAM_WEN_B[2:2];
  assign pgassign42[0:0] = BRAM_WEN_B[2:2];
  assign pgassign43[13:2] = BRAM_Addr_A[18:29];
  assign pgassign43[1:0] = 2'b00;
  assign pgassign44[31:4] = 28'b0000000000000000000000000000;
  assign pgassign44[3:0] = BRAM_Dout_A[20:23];
  assign BRAM_Din_A[20:23] = pgassign45[3:0];
  assign pgassign46[3:3] = BRAM_WEN_A[2:2];
  assign pgassign46[2:2] = BRAM_WEN_A[2:2];
  assign pgassign46[1:1] = BRAM_WEN_A[2:2];
  assign pgassign46[0:0] = BRAM_WEN_A[2:2];
  assign pgassign47[13:2] = BRAM_Addr_B[18:29];
  assign pgassign47[1:0] = 2'b00;
  assign pgassign48[31:4] = 28'b0000000000000000000000000000;
  assign pgassign48[3:0] = BRAM_Dout_B[20:23];
  assign BRAM_Din_B[20:23] = pgassign49[3:0];
  assign pgassign50[3:3] = BRAM_WEN_B[2:2];
  assign pgassign50[2:2] = BRAM_WEN_B[2:2];
  assign pgassign50[1:1] = BRAM_WEN_B[2:2];
  assign pgassign50[0:0] = BRAM_WEN_B[2:2];
  assign pgassign51[13:2] = BRAM_Addr_A[18:29];
  assign pgassign51[1:0] = 2'b00;
  assign pgassign52[31:4] = 28'b0000000000000000000000000000;
  assign pgassign52[3:0] = BRAM_Dout_A[24:27];
  assign BRAM_Din_A[24:27] = pgassign53[3:0];
  assign pgassign54[3:3] = BRAM_WEN_A[3:3];
  assign pgassign54[2:2] = BRAM_WEN_A[3:3];
  assign pgassign54[1:1] = BRAM_WEN_A[3:3];
  assign pgassign54[0:0] = BRAM_WEN_A[3:3];
  assign pgassign55[13:2] = BRAM_Addr_B[18:29];
  assign pgassign55[1:0] = 2'b00;
  assign pgassign56[31:4] = 28'b0000000000000000000000000000;
  assign pgassign56[3:0] = BRAM_Dout_B[24:27];
  assign BRAM_Din_B[24:27] = pgassign57[3:0];
  assign pgassign58[3:3] = BRAM_WEN_B[3:3];
  assign pgassign58[2:2] = BRAM_WEN_B[3:3];
  assign pgassign58[1:1] = BRAM_WEN_B[3:3];
  assign pgassign58[0:0] = BRAM_WEN_B[3:3];
  assign pgassign59[13:2] = BRAM_Addr_A[18:29];
  assign pgassign59[1:0] = 2'b00;
  assign pgassign60[31:4] = 28'b0000000000000000000000000000;
  assign pgassign60[3:0] = BRAM_Dout_A[28:31];
  assign BRAM_Din_A[28:31] = pgassign61[3:0];
  assign pgassign62[3:3] = BRAM_WEN_A[3:3];
  assign pgassign62[2:2] = BRAM_WEN_A[3:3];
  assign pgassign62[1:1] = BRAM_WEN_A[3:3];
  assign pgassign62[0:0] = BRAM_WEN_A[3:3];
  assign pgassign63[13:2] = BRAM_Addr_B[18:29];
  assign pgassign63[1:0] = 2'b00;
  assign pgassign64[31:4] = 28'b0000000000000000000000000000;
  assign pgassign64[3:0] = BRAM_Dout_B[28:31];
  assign BRAM_Din_B[28:31] = pgassign65[3:0];
  assign pgassign66[3:3] = BRAM_WEN_B[3:3];
  assign pgassign66[2:2] = BRAM_WEN_B[3:3];
  assign pgassign66[1:1] = BRAM_WEN_B[3:3];
  assign pgassign66[0:0] = BRAM_WEN_B[3:3];
  assign net_gnd0 = 1'b0;
  assign net_gnd4[3:0] = 4'b0000;

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_0.mem" ),
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
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
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
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
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
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
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
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

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_4.mem" ),
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
    )
    ramb16bwer_4 (
      .ADDRA ( pgassign35 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign36 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign37 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign38 ),
      .ADDRB ( pgassign39 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign40 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign41 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign42 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_5.mem" ),
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
    )
    ramb16bwer_5 (
      .ADDRA ( pgassign43 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign44 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign45 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign46 ),
      .ADDRB ( pgassign47 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign48 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign49 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign50 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_6.mem" ),
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
    )
    ramb16bwer_6 (
      .ADDRA ( pgassign51 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign52 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign53 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign54 ),
      .ADDRB ( pgassign55 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign56 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign57 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign58 )
    );

  (* BMM_INFO = " " *)

  RAMB16BWER
    #(
      .INIT_FILE ( "microblaze_0_bram_block_combined_7.mem" ),
      .DATA_WIDTH_A ( 4 ),
      .DATA_WIDTH_B ( 4 )
    )
    ramb16bwer_7 (
      .ADDRA ( pgassign59 ),
      .CLKA ( BRAM_Clk_A ),
      .DIA ( pgassign60 ),
      .DIPA ( net_gnd4 ),
      .DOA ( pgassign61 ),
      .DOPA (  ),
      .ENA ( BRAM_EN_A ),
      .REGCEA ( net_gnd0 ),
      .RSTA ( BRAM_Rst_A ),
      .WEA ( pgassign62 ),
      .ADDRB ( pgassign63 ),
      .CLKB ( BRAM_Clk_B ),
      .DIB ( pgassign64 ),
      .DIPB ( net_gnd4 ),
      .DOB ( pgassign65 ),
      .DOPB (  ),
      .ENB ( BRAM_EN_B ),
      .REGCEB ( net_gnd0 ),
      .RSTB ( BRAM_Rst_B ),
      .WEB ( pgassign66 )
    );

endmodule

