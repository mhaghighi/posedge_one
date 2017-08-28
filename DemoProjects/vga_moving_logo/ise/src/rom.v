
module rom (
address , // Address input
data    , // Data output
read_en , // Read Enable 
ce        // Chip Enable
);
input [15:0] address;
output [7:0] data; 
input read_en; 
input ce; 
           
reg [7:0] mem [0:20000] ;  
      
assign data = (ce && read_en) ? mem[address] : 8'b0;

initial begin
  $readmemh("memory.list", mem); // memory_list is memory file
end

endmodule
