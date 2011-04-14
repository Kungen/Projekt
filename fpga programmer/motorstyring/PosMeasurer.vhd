----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:22:11 03/11/2011 
-- Design Name: 
-- Module Name:    PosMeasurer - Behavioral 
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

--Hall1 ligger på JB1
--Hall2 ligger på JB2
--Clk er signalet fra clk1

entity PosMeasurer is
	port( Hall1 : in std_logic;
			Hall2 : in std_logic;
			Clk	: in std_logic;
			
			pos_out 	: out std_logic_vector (13 downto 0)
			);
	
end PosMeasurer;

architecture Behavioral of PosMeasurer is
	
	signal pos : integer range 0 to 10000 := 180;

begin

	pos_out <= conv_std_logic_vector(pos,14);
	
	process(Clk)
	
--	variable pos : integer range 0 to 360 := 180;
	variable state : std_logic_vector (1 downto 0) := "11";
	variable scale_count2 : integer range 0 to 5001 := 1;
	
	begin
		if rising_edge(Clk) then
			scale_count2 := scale_count2 + 1;
			if scale_count2 = 5001 then
				scale_count2 := 1;
				if Hall1 = '1' and Hall2 = '0' then
					if state = "11" then
						pos <= pos + 1;
					elsif state = "00" then
						pos <= pos - 1;
					end if;
					state := "10";
				elsif Hall1 = '0' and Hall2 = '1' then
					if state = "11" then
						pos <= pos - 1;
					elsif state = "00" then
						pos <= pos + 1;
					end if;
					state := "01";
				elsif Hall1 = '0' and Hall2 = '0' then 
					if state = "10" then
						pos <= pos + 1;
					elsif state = "01" then
						pos <= pos - 1;
					end if;
					state := "00";
				elsif Hall1 = '1' and Hall2 = '1' then 
					if state = "10" then
						pos <= pos - 1;
					elsif state = "01" then
						pos <= pos + 1;
					end if;
					state := "11";
				end if;
			end if;
		end if;
	end process;

end Behavioral;

