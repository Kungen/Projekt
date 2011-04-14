----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:23:59 02/24/2011 
-- Design Name: 
-- Module Name:    toggleButton1 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity toggleButton1 is
    Port ( button : in  STD_LOGIC;
           Clk : in  STD_LOGIC;
           toggle : out  STD_LOGIC := '0'
			  );
end toggleButton1;

architecture Behavioral of toggleButton1 is

begin

process( Clk)
 
	variable trykket : integer range 0 to 11 := 0;
	variable toggle_state : STD_LOGIC := '0';

begin
	if rising_edge(Clk) then
		if button = '1' and trykket < 11 then
			trykket := trykket+1;
			if trykket = 10 then
				toggle_state := toggle_state XOR '1';
				toggle <= toggle_state;
			end if;
		end if;
		if button = '0' then
			trykket := 1;
		end if;
	end if;
end process;

end Behavioral;

