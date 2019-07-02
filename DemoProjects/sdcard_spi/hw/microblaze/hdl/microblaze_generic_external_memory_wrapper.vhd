-------------------------------------------------------------------------------
-- microblaze_generic_external_memory_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library axi_emc_v1_03_b;
use axi_emc_v1_03_b.all;

entity microblaze_generic_external_memory_wrapper is
  port (
    S_AXI_ACLK : in std_logic;
    S_AXI_ARESETN : in std_logic;
    S_AXI_REG_AWADDR : in std_logic_vector(4 downto 0);
    S_AXI_REG_AWVALID : in std_logic;
    S_AXI_REG_AWREADY : out std_logic;
    S_AXI_REG_WDATA : in std_logic_vector(31 downto 0);
    S_AXI_REG_WSTRB : in std_logic_vector(3 downto 0);
    S_AXI_REG_WVALID : in std_logic;
    S_AXI_REG_WREADY : out std_logic;
    S_AXI_REG_BRESP : out std_logic_vector(1 downto 0);
    S_AXI_REG_BVALID : out std_logic;
    S_AXI_REG_BREADY : in std_logic;
    S_AXI_REG_ARADDR : in std_logic_vector(4 downto 0);
    S_AXI_REG_ARVALID : in std_logic;
    S_AXI_REG_ARREADY : out std_logic;
    S_AXI_REG_RDATA : out std_logic_vector(31 downto 0);
    S_AXI_REG_RRESP : out std_logic_vector(1 downto 0);
    S_AXI_REG_RVALID : out std_logic;
    S_AXI_REG_RREADY : in std_logic;
    S_AXI_MEM_AWLEN : in std_logic_vector(7 downto 0);
    S_AXI_MEM_AWSIZE : in std_logic_vector(2 downto 0);
    S_AXI_MEM_AWBURST : in std_logic_vector(1 downto 0);
    S_AXI_MEM_AWLOCK : in std_logic;
    S_AXI_MEM_AWCACHE : in std_logic_vector(3 downto 0);
    S_AXI_MEM_AWPROT : in std_logic_vector(2 downto 0);
    S_AXI_MEM_WLAST : in std_logic;
    S_AXI_MEM_BID : out std_logic_vector(0 downto 0);
    S_AXI_MEM_ARID : in std_logic_vector(0 downto 0);
    S_AXI_MEM_ARLEN : in std_logic_vector(7 downto 0);
    S_AXI_MEM_ARSIZE : in std_logic_vector(2 downto 0);
    S_AXI_MEM_ARBURST : in std_logic_vector(1 downto 0);
    S_AXI_MEM_ARLOCK : in std_logic;
    S_AXI_MEM_ARCACHE : in std_logic_vector(3 downto 0);
    S_AXI_MEM_ARPROT : in std_logic_vector(2 downto 0);
    S_AXI_MEM_RID : out std_logic_vector(0 downto 0);
    S_AXI_MEM_RLAST : out std_logic;
    S_AXI_MEM_AWID : in std_logic_vector(0 downto 0);
    S_AXI_MEM_AWADDR : in std_logic_vector(31 downto 0);
    S_AXI_MEM_AWVALID : in std_logic;
    S_AXI_MEM_AWREADY : out std_logic;
    S_AXI_MEM_WDATA : in std_logic_vector(31 downto 0);
    S_AXI_MEM_WSTRB : in std_logic_vector(3 downto 0);
    S_AXI_MEM_WVALID : in std_logic;
    S_AXI_MEM_WREADY : out std_logic;
    S_AXI_MEM_BRESP : out std_logic_vector(1 downto 0);
    S_AXI_MEM_BVALID : out std_logic;
    S_AXI_MEM_BREADY : in std_logic;
    S_AXI_MEM_ARADDR : in std_logic_vector(31 downto 0);
    S_AXI_MEM_ARVALID : in std_logic;
    S_AXI_MEM_ARREADY : out std_logic;
    S_AXI_MEM_RDATA : out std_logic_vector(31 downto 0);
    S_AXI_MEM_RRESP : out std_logic_vector(1 downto 0);
    S_AXI_MEM_RVALID : out std_logic;
    S_AXI_MEM_RREADY : in std_logic;
    RdClk : in std_logic;
    Mem_A : out std_logic_vector(31 downto 0);
    Mem_RPN : out std_logic;
    Mem_CE : out std_logic_vector(0 downto 0);
    Mem_CEN : out std_logic_vector(0 downto 0);
    Mem_OEN : out std_logic_vector(0 downto 0);
    Mem_WEN : out std_logic;
    Mem_QWEN : out std_logic_vector(0 downto 0);
    Mem_BEN : out std_logic_vector(0 downto 0);
    Mem_ADV_LDN : out std_logic;
    Mem_LBON : out std_logic;
    Mem_CKEN : out std_logic;
    Mem_CRE : out std_logic;
    Mem_RNW : out std_logic;
    Mem_WAIT : in std_logic_vector(0 downto 0);
    Mem_DQ_I : in std_logic_vector(7 downto 0);
    Mem_DQ_O : out std_logic_vector(7 downto 0);
    Mem_DQ_T : out std_logic_vector(7 downto 0);
    MEM_DQ_PARITY_I : in std_logic_vector(0 downto 0);
    MEM_DQ_PARITY_O : out std_logic_vector(0 downto 0);
    MEM_DQ_PARITY_T : out std_logic_vector(0 downto 0)
  );

  attribute x_core_info : STRING;
  attribute x_core_info of microblaze_generic_external_memory_wrapper : entity is "axi_emc_v1_03_b";

end microblaze_generic_external_memory_wrapper;

architecture STRUCTURE of microblaze_generic_external_memory_wrapper is

  component axi_emc is
    generic (
      C_FAMILY : STRING;
      C_INSTANCE : STRING;
      C_S_AXI_EN_REG : INTEGER;
      C_S_AXI_REG_ADDR_WIDTH : INTEGER;
      C_S_AXI_REG_DATA_WIDTH : INTEGER;
      C_S_AXI_MEM_ID_WIDTH : INTEGER;
      C_S_AXI_MEM_ADDR_WIDTH : INTEGER;
      C_S_AXI_MEM_DATA_WIDTH : INTEGER;
      C_AXI_CLK_PERIOD_PS : INTEGER;
      C_LFLASH_PERIOD_PS : INTEGER;
      C_LINEAR_FLASH_SYNC_BURST : INTEGER;
      C_NUM_BANKS_MEM : INTEGER;
      C_INCLUDE_NEGEDGE_IOREGS : INTEGER;
      C_MEM0_WIDTH : INTEGER;
      C_MEM1_WIDTH : INTEGER;
      C_MEM2_WIDTH : INTEGER;
      C_MEM3_WIDTH : INTEGER;
      C_INCLUDE_DATAWIDTH_MATCHING_0 : INTEGER;
      C_INCLUDE_DATAWIDTH_MATCHING_1 : INTEGER;
      C_INCLUDE_DATAWIDTH_MATCHING_2 : INTEGER;
      C_INCLUDE_DATAWIDTH_MATCHING_3 : INTEGER;
      C_MEM0_TYPE : INTEGER;
      C_SYNCH_PIPEDELAY_0 : INTEGER;
      C_PARITY_TYPE_MEM_0 : INTEGER;
      C_TCEDV_PS_MEM_0 : INTEGER;
      C_TAVDV_PS_MEM_0 : INTEGER;
      C_TPACC_PS_FLASH_0 : INTEGER;
      C_THZCE_PS_MEM_0 : INTEGER;
      C_THZOE_PS_MEM_0 : INTEGER;
      C_TWC_PS_MEM_0 : INTEGER;
      C_TWP_PS_MEM_0 : INTEGER;
      C_TWPH_PS_MEM_0 : INTEGER;
      C_TLZWE_PS_MEM_0 : INTEGER;
      C_WR_REC_TIME_MEM_0 : INTEGER;
      C_MEM1_TYPE : INTEGER;
      C_SYNCH_PIPEDELAY_1 : INTEGER;
      C_PARITY_TYPE_MEM_1 : INTEGER;
      C_TCEDV_PS_MEM_1 : INTEGER;
      C_TAVDV_PS_MEM_1 : INTEGER;
      C_TPACC_PS_FLASH_1 : INTEGER;
      C_THZCE_PS_MEM_1 : INTEGER;
      C_THZOE_PS_MEM_1 : INTEGER;
      C_TWC_PS_MEM_1 : INTEGER;
      C_TWP_PS_MEM_1 : INTEGER;
      C_TWPH_PS_MEM_1 : INTEGER;
      C_TLZWE_PS_MEM_1 : INTEGER;
      C_WR_REC_TIME_MEM_1 : INTEGER;
      C_MEM2_TYPE : INTEGER;
      C_SYNCH_PIPEDELAY_2 : INTEGER;
      C_PARITY_TYPE_MEM_2 : INTEGER;
      C_TCEDV_PS_MEM_2 : INTEGER;
      C_TAVDV_PS_MEM_2 : INTEGER;
      C_TPACC_PS_FLASH_2 : INTEGER;
      C_THZCE_PS_MEM_2 : INTEGER;
      C_THZOE_PS_MEM_2 : INTEGER;
      C_TWC_PS_MEM_2 : INTEGER;
      C_TWP_PS_MEM_2 : INTEGER;
      C_TWPH_PS_MEM_2 : INTEGER;
      C_TLZWE_PS_MEM_2 : INTEGER;
      C_WR_REC_TIME_MEM_2 : INTEGER;
      C_MEM3_TYPE : INTEGER;
      C_SYNCH_PIPEDELAY_3 : INTEGER;
      C_PARITY_TYPE_MEM_3 : INTEGER;
      C_TCEDV_PS_MEM_3 : INTEGER;
      C_TAVDV_PS_MEM_3 : INTEGER;
      C_TPACC_PS_FLASH_3 : INTEGER;
      C_THZCE_PS_MEM_3 : INTEGER;
      C_THZOE_PS_MEM_3 : INTEGER;
      C_TWC_PS_MEM_3 : INTEGER;
      C_TWP_PS_MEM_3 : INTEGER;
      C_TWPH_PS_MEM_3 : INTEGER;
      C_TLZWE_PS_MEM_3 : INTEGER;
      C_WR_REC_TIME_MEM_3 : INTEGER;
      C_MAX_MEM_WIDTH : INTEGER;
      C_S_AXI_MEM0_BASEADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM0_HIGHADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM1_BASEADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM1_HIGHADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM2_BASEADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM2_HIGHADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM3_BASEADDR : std_logic_vector(31 downto 0);
      C_S_AXI_MEM3_HIGHADDR : std_logic_vector(31 downto 0)
    );
    port (
      S_AXI_ACLK : in std_logic;
      S_AXI_ARESETN : in std_logic;
      S_AXI_REG_AWADDR : in std_logic_vector((C_S_AXI_REG_ADDR_WIDTH-1) downto 0);
      S_AXI_REG_AWVALID : in std_logic;
      S_AXI_REG_AWREADY : out std_logic;
      S_AXI_REG_WDATA : in std_logic_vector((C_S_AXI_REG_DATA_WIDTH-1) downto 0);
      S_AXI_REG_WSTRB : in std_logic_vector(((C_S_AXI_REG_DATA_WIDTH/8)-1) downto 0);
      S_AXI_REG_WVALID : in std_logic;
      S_AXI_REG_WREADY : out std_logic;
      S_AXI_REG_BRESP : out std_logic_vector(1 downto 0);
      S_AXI_REG_BVALID : out std_logic;
      S_AXI_REG_BREADY : in std_logic;
      S_AXI_REG_ARADDR : in std_logic_vector((C_S_AXI_REG_ADDR_WIDTH-1) downto 0);
      S_AXI_REG_ARVALID : in std_logic;
      S_AXI_REG_ARREADY : out std_logic;
      S_AXI_REG_RDATA : out std_logic_vector((C_S_AXI_REG_DATA_WIDTH-1) downto 0);
      S_AXI_REG_RRESP : out std_logic_vector(1 downto 0);
      S_AXI_REG_RVALID : out std_logic;
      S_AXI_REG_RREADY : in std_logic;
      S_AXI_MEM_AWLEN : in std_logic_vector(7 downto 0);
      S_AXI_MEM_AWSIZE : in std_logic_vector(2 downto 0);
      S_AXI_MEM_AWBURST : in std_logic_vector(1 downto 0);
      S_AXI_MEM_AWLOCK : in std_logic;
      S_AXI_MEM_AWCACHE : in std_logic_vector(3 downto 0);
      S_AXI_MEM_AWPROT : in std_logic_vector(2 downto 0);
      S_AXI_MEM_WLAST : in std_logic;
      S_AXI_MEM_BID : out std_logic_vector((C_S_AXI_MEM_ID_WIDTH-1) downto 0);
      S_AXI_MEM_ARID : in std_logic_vector((C_S_AXI_MEM_ID_WIDTH-1) downto 0);
      S_AXI_MEM_ARLEN : in std_logic_vector(7 downto 0);
      S_AXI_MEM_ARSIZE : in std_logic_vector(2 downto 0);
      S_AXI_MEM_ARBURST : in std_logic_vector(1 downto 0);
      S_AXI_MEM_ARLOCK : in std_logic;
      S_AXI_MEM_ARCACHE : in std_logic_vector(3 downto 0);
      S_AXI_MEM_ARPROT : in std_logic_vector(2 downto 0);
      S_AXI_MEM_RID : out std_logic_vector((C_S_AXI_MEM_ID_WIDTH-1) downto 0);
      S_AXI_MEM_RLAST : out std_logic;
      S_AXI_MEM_AWID : in std_logic_vector((C_S_AXI_MEM_ID_WIDTH-1) downto 0);
      S_AXI_MEM_AWADDR : in std_logic_vector((C_S_AXI_MEM_ADDR_WIDTH-1) downto 0);
      S_AXI_MEM_AWVALID : in std_logic;
      S_AXI_MEM_AWREADY : out std_logic;
      S_AXI_MEM_WDATA : in std_logic_vector((C_S_AXI_MEM_DATA_WIDTH-1) downto 0);
      S_AXI_MEM_WSTRB : in std_logic_vector(((C_S_AXI_MEM_DATA_WIDTH/8)-1) downto 0);
      S_AXI_MEM_WVALID : in std_logic;
      S_AXI_MEM_WREADY : out std_logic;
      S_AXI_MEM_BRESP : out std_logic_vector(1 downto 0);
      S_AXI_MEM_BVALID : out std_logic;
      S_AXI_MEM_BREADY : in std_logic;
      S_AXI_MEM_ARADDR : in std_logic_vector((C_S_AXI_MEM_ADDR_WIDTH-1) downto 0);
      S_AXI_MEM_ARVALID : in std_logic;
      S_AXI_MEM_ARREADY : out std_logic;
      S_AXI_MEM_RDATA : out std_logic_vector((C_S_AXI_MEM_DATA_WIDTH-1) downto 0);
      S_AXI_MEM_RRESP : out std_logic_vector(1 downto 0);
      S_AXI_MEM_RVALID : out std_logic;
      S_AXI_MEM_RREADY : in std_logic;
      RdClk : in std_logic;
      Mem_A : out std_logic_vector((C_S_AXI_MEM_ADDR_WIDTH-1) downto 0);
      Mem_RPN : out std_logic;
      Mem_CE : out std_logic_vector((C_NUM_BANKS_MEM-1) downto 0);
      Mem_CEN : out std_logic_vector((C_NUM_BANKS_MEM-1) downto 0);
      Mem_OEN : out std_logic_vector((C_NUM_BANKS_MEM-1) downto 0);
      Mem_WEN : out std_logic;
      Mem_QWEN : out std_logic_vector(((C_MAX_MEM_WIDTH/8)-1) downto 0);
      Mem_BEN : out std_logic_vector(((C_MAX_MEM_WIDTH/8)-1) downto 0);
      Mem_ADV_LDN : out std_logic;
      Mem_LBON : out std_logic;
      Mem_CKEN : out std_logic;
      Mem_CRE : out std_logic;
      Mem_RNW : out std_logic;
      Mem_WAIT : in std_logic_vector((C_NUM_BANKS_MEM-1) downto 0);
      Mem_DQ_I : in std_logic_vector((C_MAX_MEM_WIDTH-1) downto 0);
      Mem_DQ_O : out std_logic_vector((C_MAX_MEM_WIDTH-1) downto 0);
      Mem_DQ_T : out std_logic_vector((C_MAX_MEM_WIDTH-1) downto 0);
      MEM_DQ_PARITY_I : in std_logic_vector(((C_MAX_MEM_WIDTH/8)-1) downto 0);
      MEM_DQ_PARITY_O : out std_logic_vector(((C_MAX_MEM_WIDTH/8)-1) downto 0);
      MEM_DQ_PARITY_T : out std_logic_vector(((C_MAX_MEM_WIDTH/8)-1) downto 0)
    );
  end component;

begin

  Generic_External_Memory : axi_emc
    generic map (
      C_FAMILY => "spartan6",
      C_INSTANCE => "Generic_External_Memory",
      C_S_AXI_EN_REG => 0,
      C_S_AXI_REG_ADDR_WIDTH => 5,
      C_S_AXI_REG_DATA_WIDTH => 32,
      C_S_AXI_MEM_ID_WIDTH => 1,
      C_S_AXI_MEM_ADDR_WIDTH => 32,
      C_S_AXI_MEM_DATA_WIDTH => 32,
      C_AXI_CLK_PERIOD_PS => 10000,
      C_LFLASH_PERIOD_PS => 20000,
      C_LINEAR_FLASH_SYNC_BURST => 0,
      C_NUM_BANKS_MEM => 1,
      C_INCLUDE_NEGEDGE_IOREGS => 0,
      C_MEM0_WIDTH => 8,
      C_MEM1_WIDTH => 32,
      C_MEM2_WIDTH => 32,
      C_MEM3_WIDTH => 32,
      C_INCLUDE_DATAWIDTH_MATCHING_0 => 1,
      C_INCLUDE_DATAWIDTH_MATCHING_1 => 0,
      C_INCLUDE_DATAWIDTH_MATCHING_2 => 0,
      C_INCLUDE_DATAWIDTH_MATCHING_3 => 0,
      C_MEM0_TYPE => 2,
      C_SYNCH_PIPEDELAY_0 => 2,
      C_PARITY_TYPE_MEM_0 => 0,
      C_TCEDV_PS_MEM_0 => 15000,
      C_TAVDV_PS_MEM_0 => 15000,
      C_TPACC_PS_FLASH_0 => 25000,
      C_THZCE_PS_MEM_0 => 7000,
      C_THZOE_PS_MEM_0 => 7000,
      C_TWC_PS_MEM_0 => 15000,
      C_TWP_PS_MEM_0 => 12000,
      C_TWPH_PS_MEM_0 => 12000,
      C_TLZWE_PS_MEM_0 => 0,
      C_WR_REC_TIME_MEM_0 => 100000,
      C_MEM1_TYPE => 0,
      C_SYNCH_PIPEDELAY_1 => 2,
      C_PARITY_TYPE_MEM_1 => 0,
      C_TCEDV_PS_MEM_1 => 15000,
      C_TAVDV_PS_MEM_1 => 15000,
      C_TPACC_PS_FLASH_1 => 25000,
      C_THZCE_PS_MEM_1 => 7000,
      C_THZOE_PS_MEM_1 => 7000,
      C_TWC_PS_MEM_1 => 15000,
      C_TWP_PS_MEM_1 => 12000,
      C_TWPH_PS_MEM_1 => 12000,
      C_TLZWE_PS_MEM_1 => 0,
      C_WR_REC_TIME_MEM_1 => 100000,
      C_MEM2_TYPE => 0,
      C_SYNCH_PIPEDELAY_2 => 2,
      C_PARITY_TYPE_MEM_2 => 0,
      C_TCEDV_PS_MEM_2 => 15000,
      C_TAVDV_PS_MEM_2 => 15000,
      C_TPACC_PS_FLASH_2 => 25000,
      C_THZCE_PS_MEM_2 => 7000,
      C_THZOE_PS_MEM_2 => 7000,
      C_TWC_PS_MEM_2 => 15000,
      C_TWP_PS_MEM_2 => 12000,
      C_TWPH_PS_MEM_2 => 12000,
      C_TLZWE_PS_MEM_2 => 0,
      C_WR_REC_TIME_MEM_2 => 100000,
      C_MEM3_TYPE => 0,
      C_SYNCH_PIPEDELAY_3 => 2,
      C_PARITY_TYPE_MEM_3 => 0,
      C_TCEDV_PS_MEM_3 => 15000,
      C_TAVDV_PS_MEM_3 => 15000,
      C_TPACC_PS_FLASH_3 => 25000,
      C_THZCE_PS_MEM_3 => 7000,
      C_THZOE_PS_MEM_3 => 7000,
      C_TWC_PS_MEM_3 => 15000,
      C_TWP_PS_MEM_3 => 12000,
      C_TWPH_PS_MEM_3 => 12000,
      C_TLZWE_PS_MEM_3 => 0,
      C_WR_REC_TIME_MEM_3 => 100000,
      C_MAX_MEM_WIDTH => 8,
      C_S_AXI_MEM0_BASEADDR => X"41280000",
      C_S_AXI_MEM0_HIGHADDR => X"412fffff",
      C_S_AXI_MEM1_BASEADDR => X"ffffffff",
      C_S_AXI_MEM1_HIGHADDR => X"00000000",
      C_S_AXI_MEM2_BASEADDR => X"ffffffff",
      C_S_AXI_MEM2_HIGHADDR => X"00000000",
      C_S_AXI_MEM3_BASEADDR => X"ffffffff",
      C_S_AXI_MEM3_HIGHADDR => X"00000000"
    )
    port map (
      S_AXI_ACLK => S_AXI_ACLK,
      S_AXI_ARESETN => S_AXI_ARESETN,
      S_AXI_REG_AWADDR => S_AXI_REG_AWADDR,
      S_AXI_REG_AWVALID => S_AXI_REG_AWVALID,
      S_AXI_REG_AWREADY => S_AXI_REG_AWREADY,
      S_AXI_REG_WDATA => S_AXI_REG_WDATA,
      S_AXI_REG_WSTRB => S_AXI_REG_WSTRB,
      S_AXI_REG_WVALID => S_AXI_REG_WVALID,
      S_AXI_REG_WREADY => S_AXI_REG_WREADY,
      S_AXI_REG_BRESP => S_AXI_REG_BRESP,
      S_AXI_REG_BVALID => S_AXI_REG_BVALID,
      S_AXI_REG_BREADY => S_AXI_REG_BREADY,
      S_AXI_REG_ARADDR => S_AXI_REG_ARADDR,
      S_AXI_REG_ARVALID => S_AXI_REG_ARVALID,
      S_AXI_REG_ARREADY => S_AXI_REG_ARREADY,
      S_AXI_REG_RDATA => S_AXI_REG_RDATA,
      S_AXI_REG_RRESP => S_AXI_REG_RRESP,
      S_AXI_REG_RVALID => S_AXI_REG_RVALID,
      S_AXI_REG_RREADY => S_AXI_REG_RREADY,
      S_AXI_MEM_AWLEN => S_AXI_MEM_AWLEN,
      S_AXI_MEM_AWSIZE => S_AXI_MEM_AWSIZE,
      S_AXI_MEM_AWBURST => S_AXI_MEM_AWBURST,
      S_AXI_MEM_AWLOCK => S_AXI_MEM_AWLOCK,
      S_AXI_MEM_AWCACHE => S_AXI_MEM_AWCACHE,
      S_AXI_MEM_AWPROT => S_AXI_MEM_AWPROT,
      S_AXI_MEM_WLAST => S_AXI_MEM_WLAST,
      S_AXI_MEM_BID => S_AXI_MEM_BID,
      S_AXI_MEM_ARID => S_AXI_MEM_ARID,
      S_AXI_MEM_ARLEN => S_AXI_MEM_ARLEN,
      S_AXI_MEM_ARSIZE => S_AXI_MEM_ARSIZE,
      S_AXI_MEM_ARBURST => S_AXI_MEM_ARBURST,
      S_AXI_MEM_ARLOCK => S_AXI_MEM_ARLOCK,
      S_AXI_MEM_ARCACHE => S_AXI_MEM_ARCACHE,
      S_AXI_MEM_ARPROT => S_AXI_MEM_ARPROT,
      S_AXI_MEM_RID => S_AXI_MEM_RID,
      S_AXI_MEM_RLAST => S_AXI_MEM_RLAST,
      S_AXI_MEM_AWID => S_AXI_MEM_AWID,
      S_AXI_MEM_AWADDR => S_AXI_MEM_AWADDR,
      S_AXI_MEM_AWVALID => S_AXI_MEM_AWVALID,
      S_AXI_MEM_AWREADY => S_AXI_MEM_AWREADY,
      S_AXI_MEM_WDATA => S_AXI_MEM_WDATA,
      S_AXI_MEM_WSTRB => S_AXI_MEM_WSTRB,
      S_AXI_MEM_WVALID => S_AXI_MEM_WVALID,
      S_AXI_MEM_WREADY => S_AXI_MEM_WREADY,
      S_AXI_MEM_BRESP => S_AXI_MEM_BRESP,
      S_AXI_MEM_BVALID => S_AXI_MEM_BVALID,
      S_AXI_MEM_BREADY => S_AXI_MEM_BREADY,
      S_AXI_MEM_ARADDR => S_AXI_MEM_ARADDR,
      S_AXI_MEM_ARVALID => S_AXI_MEM_ARVALID,
      S_AXI_MEM_ARREADY => S_AXI_MEM_ARREADY,
      S_AXI_MEM_RDATA => S_AXI_MEM_RDATA,
      S_AXI_MEM_RRESP => S_AXI_MEM_RRESP,
      S_AXI_MEM_RVALID => S_AXI_MEM_RVALID,
      S_AXI_MEM_RREADY => S_AXI_MEM_RREADY,
      RdClk => RdClk,
      Mem_A => Mem_A,
      Mem_RPN => Mem_RPN,
      Mem_CE => Mem_CE,
      Mem_CEN => Mem_CEN,
      Mem_OEN => Mem_OEN,
      Mem_WEN => Mem_WEN,
      Mem_QWEN => Mem_QWEN,
      Mem_BEN => Mem_BEN,
      Mem_ADV_LDN => Mem_ADV_LDN,
      Mem_LBON => Mem_LBON,
      Mem_CKEN => Mem_CKEN,
      Mem_CRE => Mem_CRE,
      Mem_RNW => Mem_RNW,
      Mem_WAIT => Mem_WAIT,
      Mem_DQ_I => Mem_DQ_I,
      Mem_DQ_O => Mem_DQ_O,
      Mem_DQ_T => Mem_DQ_T,
      MEM_DQ_PARITY_I => MEM_DQ_PARITY_I,
      MEM_DQ_PARITY_O => MEM_DQ_PARITY_O,
      MEM_DQ_PARITY_T => MEM_DQ_PARITY_T
    );

end architecture STRUCTURE;

