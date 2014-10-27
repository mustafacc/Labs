--------------------------------------------------------------
--------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;


entity lab7 is
  port( cond : in std_logic_vector(2 downto 0);   --into Branch_U     contents of status register from decoder
        status: in std_logic_vector(2 downto 0);  --into Branch_U     from datapath
        execb: in std_logic;                    --into Branch_U       from FSM
        sximm8: in std_logic_vector(7 downto 0);  --into Branch_U
        incp: in std_logic;                     --Select signal
        pc_input: in std_logic_vector(7 downto 0);  --input from PC ff
        
        loadpc: out std_logic;                  --Output select signal to loadpc mux
        pc_next: out std_logic_vector(7 downto 0) --Output to loadpc mux input
       );
    
end lab7;

architecture impl of lab7 is
  signal taken: std_logic;  
  signal pcrel: std_logic_vector(7 downto 0);
  signal pc1: std_logic_vector(7 downto 0); --mod for Bonus
begin
  process( all ) begin
    
    pc1 <= pc_input + 1;
    pcrel <= pc_input + sximm8;
  
    --Output to loadpc mux input
    case incp is
      when '0' =>   pc_next <= pc1;
      when '1' =>   pc_next <= pcrel; --mod for bonus
      when others => pc_next <= "--------";
    end case;
    
    
    --Branch Unit CL
    --to determine if a branch instruction should update PC to target branch
    /*
    case? status & "00" & cond is
      when "001" & "00" & "000"
      when "001" & "00" & "001"
      when "001" & "00" & "010"
      when "001" & "00" & "011"
      when "001" & "00" & "100"
    end case?;
    --/Branch Unit CL
    */
    
    loadpc <= '1' when (taken OR incp );  --output to loadpc mux select signal
    
    /*refrence
    B			<label> 0	0	1 0	0 0	0	0 imm8 PC=PC+sx(<imm8>)
    BEQ	<label> 0	0	1 0	0 0	0	1 imm8 if Z=1 then PC=PC+sx (<imm8>) 
    BNE	<label> 0	0	1 0	0 0	1	0 imm8 if Z=0 then PC=PC+sx (<imm8>)
    BLT	<label> 0	0	1 0	0 0	1	1 imm8 if N/=V then PC=PC+sx (<imm8>)
    BLE	<label> 0	0	1 0	0 1	0	0 imm8 if N/=V or Z=1 then PC=PC+sx (<imm8>)
    */
    
    
  end process;
  
end impl;


--------------------------------------------------
--------------------------------------------------

