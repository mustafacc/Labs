-- synthesis VHDL_INPUT_VERSION VHDL_2008
library ieee;
use ieee.std_logic_1164.all;

package FSM_codes is  
  -- define state assignment - binary
  component FSM is
  port ( clk :    in std_logic;
        reset :   in std_logic;
        opcode :  in std_logic_vector( 2 downto 0 );
        op :      in std_logic_vector( 1 downto 0 );
        loadir :  out std_logic;
        loadpc :  out std_logic;
        nsel :    out std_logic_vector(1 downto 0);
        write :   out std_logic;
        vsel :    out std_logic_vector( 1 downto 0 );
        loada :   out std_logic;
        loadb :   out std_logic;
        asel  :   out std_logic;
        bsel  :   out std_logic;
        loadc :   out std_logic;
        loads :   out std_logic;
        msel  :   out std_logic;
        mwrite :  out std_logic
        );
end component;

  constant SWIDTH: integer := 4;
  subtype state_type is 
    std_logic_vector( SWIDTH-1 downto 0 );
  
  constant	LOAD_IR:	state_type := "0000";
  constant	UPDATE_PC:	state_type := "0001";
  constant	DECODE_RN:	state_type := "0010";
  constant	READ_RM:	state_type := "0100";
  constant ALU_ST: state_type := "1000";
  constant WRITE_RDRN: state_type := "0011";
  
  --LAB7 states
  constant EX_BR1: state_type := "0111";
  constant EX_BR2: state_type := "1111";
  --/LAB7 states

  
end package;

----------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;
use work.datapath_declarations.all;
use work.ff.all;
use work.FSM_codes.all;

entity FSM is
  port ( clk :    in std_logic;
        reset :   in std_logic;
        opcode :  in std_logic_vector( 2 downto 0 );
        op :      in std_logic_vector( 1 downto 0 );
        loadir :  out std_logic;
        loadpc :  out std_logic;
        nsel :    out std_logic_vector(1 downto 0);
        write :   out std_logic;
        vsel :    out std_logic_vector( 1 downto 0 );
        loada :   buffer std_logic;
        loadb :   buffer std_logic;
        asel  :   out std_logic;
        bsel  :   out std_logic;
        loadc :   out std_logic;
        loads :   out std_logic;
        msel  :   out std_logic;
        mwrite :  out std_logic;
        execb: out std_logic;
        incp: out std_logic
        );
end FSM;

architecture impl of FSM is
  signal	current_state, next_state, next1:	std_logic_vector(SWIDTH-1	downto	0);
begin
  
  
  asel <= '0';
  bsel <= '0';
  msel <= '0';
  mwrite <= '0';
  
  loadir <= '1' when current_state = LOAD_IR else '0';
  loadpc <= '1' when current_state = UPDATE_PC else '0';
  loada <= '1' when current_state = DECODE_RN else '0';
  loadb <= '1' when current_state = READ_RM else '0';
           
  loads <= '1' when current_state = ALU_ST else '0';
  write <= '1' when current_state = WRITE_RDRN else '0';
  loadc <= '1' when current_state = WRITE_RDRN else
           '1' when current_state = READ_RM and op = "01" else
           '1' when current_state = ALU_ST else '0';


  --LAB7
  execb <= '1' when current_state = EX_BR1 else
           '1' when current_state = EX_BR2 else '0';
           
  incp <= '0' when current_state = EX_BR1 else
          '0' when current_state = EX_BR2 else '1';
  --/LAB7
    
-- vsel <= (loada or loadb or loads or opCode(1)) & (loada or loadb or loads);
  
 nsel <= ((loada or opCode(1)) and not loadb) & (not opCode(1) and not loadb and not loada);
  
  state_reg: vDFF generic map(SWIDTH) port map(clk, next_state, current_state);
    
  
   
  -- next state logic
  process(all) begin
    case? opCode & op & current_state is
     when "---" & "--" & LOAD_IR => next1 <= UPDATE_PC;     vsel<="11";
     when "---" & "--" & UPDATE_PC => next1 <= DECODE_RN;   vsel<="11";
     when "101" & "--" & DECODE_RN => next1 <= READ_RM;     vsel<="11";
     when "110" & "10" & DECODE_RN => next1 <= WRITE_RDRN;  vsel<="11";
     when "---" & "--" & READ_RM => next1 <= ALU_ST;      	 vsel<="11";
     when "101" & "01" & ALU_ST => next1 <= LOAD_IR;        vsel<="11";
     when "101" & "00" & ALU_ST => next1 <= WRITE_RDRN;     vsel<="11";
     when "101" & "1-" & ALU_ST => next1 <= WRITE_RDRN; 	   vsel<="11";
     when "---" & "--" & WRITE_RDRN => next1 <= LOAD_IR;    vsel<= opCode(1) & '0';
--LAB7

--/LAB7
     when others => next1 <= std_logic_vector'(SWIDTH-1 downto 0 => '-'); vsel <= "11";
       
    end case?;
  end process;
  
  next_state <= LOAD_IR when reset else next1;
end impl;

----------------------------------------------------------------------
----------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;
use work.datapath_declarations.all;
use work.ff.all;
use work.FSM_codes.all;

entity CPUentity is
  port( clk :   in std_logic;
        reset:  in std_logic;
        readNumOutput: out std_logic_vector(2 downto 0);
        writeNumOutput: out std_logic_vector(2 downto 0);
        writeValueOutput: out std_logic_vector(15 downto 0);
        writeEnableOutput: out std_logic;
        readValueOutput: out std_logic_vector(15 downto 0);
        pcOut: out std_logic_vector( 7 downto 0 );
        irOut: out std_logic_vector(15 downto 0);
        mdataOut: out std_logic_vector(15 downto 0);
        datapathOutput: out std_logic_vector(15 downto 0));
 

--  datapath_insta : datapath generic map(16, 8) port map( );
--  FSM_insta: FSM generic map( ) port map( );
end CPUentity;

architecture impl of CPUentity is

 signal opCode: std_logic_vector(2 downto 0);
 signal op: std_logic_vector(1 downto 0);
 signal loadir: std_logic;
 signal loadpc: std_logic;
 signal nsel: std_logic_vector(1 downto 0);
 signal write: std_logic;
 signal vsel: std_logic_vector(1 downto 0);
 signal loada: std_logic;
 signal loadb: std_logic;
 signal asel: std_logic;
 signal bsel: std_logic;
 signal loadc: std_logic;
 signal loads: std_logic;
 signal msel: std_logic;
 signal mwrite: std_logic;
 
 
begin
  
FSM_INSTAN: FSM port map( clk, reset, opCode, op, loadir, loadpc, nsel, write, vsel, 
                       loada, loadb, asel, bsel, loadc, loads, msel, mwrite );

DATAPATH_INSTAN: datapath generic map(16,8) port map( clk, reset, write, vsel, loada, loadb, asel, bsel, 
                                             loadc, loads, msel, mwrite, loadir, loadpc, nsel,
                                             opCode, op, readNumOutput, writeNumOutput, writeValueOutput, writeEnableOutput,
                                              readValueOutput, pcOut, irOut, mdataout, datapathOutput);
      
end impl;